/****************************************************************************
    PROGRAM:    copydb

    FILE:       copydb.c

    PURPOSE:    Create a replica copy of a Domino database.

    SYNTAX:     copydb  <input db>  <output db>  <output title>
                                  or
                copydb

****************************************************************************/

/* C and OS include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <stdnames.h>
#include <nsfdb.h>
#include <nsferr.h>
#include <nsfnote.h>
#include <misc.h>  
#include <idtable.h>  
#include <osmem.h>  

#include <lapiplat.h>

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                         char *input_path, 
                         char *output_path, 
                         char *output_title); 
                         
#define  STRING_LENGTH  256


/************************************************************************

    FUNCTION:   Main / NotesMain 

    PURPOSE:    Lotus C API for Domino and Notes subroutine

*************************************************************************/

LAPI_MAIN
{
    char        input_path[STRING_LENGTH];   /* pathname of input database */
    char        output_path[STRING_LENGTH];  /* pathname of output database */
    char        output_title[NSF_INFO_SIZE]; /* title of output database */
    char        output_db_info[NSF_INFO_SIZE];  /* database info buffer */
    DBHANDLE    input_handle;       /* handle of input database */
    DBHANDLE    output_handle;      /* handle of output database */
    DBID        input_dbid;         /* dbid of input database */
    DBID        output_dbid;        /* dbid of output database */
    DBREPLICAINFO    replica_info;  /* replication info for the databases */
    TIMEDATE    start_time;         /* time and date used to control what
                                        notes we copy */
    TIMEDATE    last_time;          /* returned from 
                                        NSFDbGetModifiedNoteTable */
    HANDLE      idtable_p;          /* handle to id table */
    DWORD       num_scanned, num_entries;
    NOTEID      note_id;
    NOTEHANDLE  hIconNote;          /* handle to the icon note */
    STATUS      error = NOERROR;    /* return status from API calls */

    ProcessArgs (argc, argv, 
                 input_path, output_path, output_title);

    LAPI_INIT(error);
    if (error)
        LAPI_INIT_ERROR;

/* Open the input database. */

    if (error = NSFDbOpen (input_path, &input_handle))
        LAPI_RETURN (ERR(error));

    printf("\nOpened \"%s\" as the input database", input_path); 
    fflush(stdout);
   
/* Create and open the output database. */

    if (error = NSFDbCreate (output_path, DBCLASS_NOTEFILE, FALSE))
    {
        NSFDbClose (input_handle);
        LAPI_RETURN (ERR(error));
    }

    if (error = NSFDbOpen (output_path, &output_handle))
    {
        NSFDbClose (input_handle);
        LAPI_RETURN (ERR(error));
    }
 
    printf("\nCreated \"%s\" as the output database", output_path); 
    fflush(stdout);

/* Copy the replication settings (not the replication history) from
the input database to the output database. The replication settings
include the database replica ID. This makes the destination database
a replica copy of the source database. */

    if (error = NSFDbReplicaInfoGet (input_handle, &replica_info))
    {
        NSFDbClose (input_handle);
        NSFDbClose (output_handle);
        LAPI_RETURN (ERR(error));
    }

    if (error = NSFDbReplicaInfoSet (output_handle, &replica_info))
    {
        NSFDbClose (input_handle);
        NSFDbClose (output_handle);
        LAPI_RETURN (ERR(error));
    }

/* Copy the ACL from the input database to the output database. */

    if (error = NSFDbCopyACL (input_handle, output_handle))
    {
        NSFDbClose (input_handle);
        NSFDbClose (output_handle);
        LAPI_RETURN (ERR(error));
    }

/* Set a time/date structure that will determine the date of the earliest
note copied in the next call.  Use TimeConstant with TIMEDATE_WILDCARD
specified to indicate that we do not want any cutoff date.  */

    TimeConstant (TIMEDATE_WILDCARD, &start_time);

/* Do not use NSFDbCopy to copy all notes in the input database to the 
   output database. Such copies are not guaranteed to be replicas of 
   the original notes.  Instead get an IDTABLE of all notes in the 
   database, use IDScan to obtain each NOTEID, and then call 
   NSFDbCopyNote to copy each note from one database to the other.
*/

    NSFDbIDGet (input_handle, &input_dbid);
    NSFDbIDGet (output_handle, &output_dbid);

/* Get the NoteID table for all notes in the input database */
    if (error = NSFDbGetModifiedNoteTable (input_handle,
                                           NOTE_CLASS_ALL,
                                           start_time, &last_time,
                                           &idtable_p) )
        if (error == ERR_NO_MODIFIED_NOTES)
            printf ("There are no documents in the Database.\n");
        else
        {
            NSFDbClose (input_handle);
            NSFDbClose (output_handle);
            LAPI_RETURN (ERR(error));
        }
    num_scanned = 0L;
    num_entries = IDEntries (idtable_p);
    if (num_entries)
        while (IDScan (idtable_p, (FLAG)(num_scanned++ == 0), &note_id) )
            if (error = NSFDbCopyNote (input_handle, &input_dbid,
                                       &replica_info.ID, note_id,
                                       output_handle, &output_dbid,
                                       &replica_info.ID, NULL,
                                       NULL) )
            {
                IDDestroyTable (idtable_p);
                NSFDbClose (input_handle);
                NSFDbClose (output_handle);
                LAPI_RETURN (ERR(error));
            }
    IDDestroyTable (idtable_p);
                       

    printf("\nDatabase documents copied"); 
    fflush(stdout);


/* Now we can change the title of the output database
   by following these steps:

   - Get the info buffer of the database (NSFDbInfoGet);
   - Modify the title information in the buffer (NSFDbInfoModify);
   - Write the modified info buffer into the database (NSFDbInfoSet);
   - If necessary, update the ICON note with the updated database
     information buffer.  This is required for databases created from 
     a template.
*/

/* Clear out the database information buffer */
    output_db_info[0] = '\0';

/* Get the output database information buffer. */
   
    if (error = NSFDbInfoGet (output_handle, output_db_info))
    {
        NSFDbClose (input_handle);
        NSFDbClose (output_handle);
        LAPI_RETURN (ERR(error));
    }

/* Add the database title to the database information buffer */
    
    NSFDbInfoModify (output_db_info, INFOPARSE_TITLE, output_title);
    if (error = NSFDbInfoSet (output_handle, output_db_info))
    {
        NSFDbClose (input_handle);
        NSFDbClose (output_handle);
        LAPI_RETURN (ERR(error));
    }

/* If creating a new database from a template, in order to change
   the database title or any other component of the database information
   buffer, you also need to update this information in the ICON
   note after updating it in the database information buffer. */ 

    if (!NSFNoteOpen(output_handle, NOTE_ID_SPECIAL+NOTE_CLASS_ICON, 
                     0, &hIconNote))
    {
        
        /* Update the FIELD_TITLE ("$TITLE") field if present */
        if (NSFItemIsPresent (hIconNote, FIELD_TITLE, (WORD) strlen (FIELD_TITLE)) )
        {
            NSFItemSetText(hIconNote, FIELD_TITLE, output_db_info, MAXWORD);
            NSFNoteUpdate(hIconNote, 0);
        }
        NSFNoteClose(hIconNote);
    }

/* if there was no ICON note, do nothing. */

    printf("\nSet the title of \"%s\" to \"%s\"", output_path, output_title); 
    fflush(stdout);

/* Close the databases. */

    if (error = NSFDbClose (input_handle))
        {
        NSFDbClose (output_handle);
        LAPI_RETURN (ERR(error));
        }

    if (error = NSFDbClose (output_handle))
        LAPI_RETURN (ERR(error));

   printf("\n Done.\n"); 
   fflush(stdout);

/* End of program. */
    printf("\nProgram completed successfully.\n");
    LAPI_RETURN (NOERROR);
}



/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    input_path, output_path, output_title get data
                from the command line or from what the user types
                at a prompt 

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                         char *input_path, 
                         char *output_path, 
                         char *output_title)
{ 
#ifndef MAC
    if (argc != 4)
    {       
#endif
      
      printf("Enter name of input database: ");   
      fflush(stdout);
      gets(input_path);
           
      printf("\n");
      printf("Enter name of output database: ");
      fflush(stdout);
      gets(output_path);

      printf("\n");
      printf("Enter title of output database: ");      
      fflush(stdout);
      gets(output_title);

#ifndef MAC
   }  
   else
    {
      strcpy(input_path, argv[1]);
      strcpy(output_path, argv[2]);
      strcpy(output_title, argv[3]);      
    } /* end if */
#endif
} /* ProcessArgs */

