/****************************************************************************

    PROGRAM:    msimple

    FILE:       msimple.c

    SYNTAX:     msimple  <db filename>
                        or
                msimple

    PURPOSE:    Find all the documents in a database that have a certain
                numeric field available, and add one to the value in the 
                field.

    DESCRIPTION:
        This program demonstrates how to search a Domino database for all
        the documents that have a certain field. This searches for all 
        documents that have a field named NUMBER available. For each
        documents this finds, it opens the document, adds one to the value 
        stored in that field, then updates and closes that document.

        This modifies the value of a TYPE_NUMBER field, but text and 
        time/date fields can be modified by the same general method.

****************************************************************************/

/* OS/2 and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <osmem.h>
#include <nsferr.h>
#include <idtable.h>            /* IDCreateTable */

#include <lapiplat.h>

              
void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                         char *db_filename); 
                         
#define  STRING_LENGTH  256
              

/* Function prototypes */

STATUS LNPUBLIC AddIDUnique (void far *, SEARCH_MATCH far *, ITEM_TABLE far *);
STATUS LNPUBLIC modify_field (void far *, DWORD);


/************************************************************************

    FUNCTION:   main / NotesMain

    PURPOSE:    Main Lotus C API for Domino and Notes subroutine

*************************************************************************/

LAPI_MAIN
{
   char       *db_filename;    /* pathname of source database */
   DBHANDLE    db_handle;      /* handle of source database */
   char       *formula;        /* an ASCII selection formula */
   FORMULAHANDLE    formula_handle;    /* a compiled selection formula */
   WORD        wdc;            /* a word we don't care about */
   STATUS      error = NOERROR;         /* return status from API calls */
   HANDLE      hNoteIDTable;   /* table of Note IDs to modify */
   char        database_name[STRING_LENGTH];
   
   db_filename = database_name;
   ProcessArgs(argc, argv, db_filename); 
   
   LAPI_INIT(error);
   if (error)
     LAPI_INIT_ERROR;
   
/* Open the database. */

   if (error = NSFDbOpen (db_filename, &db_handle))
      LAPI_RETURN (ERR(error));

   /*  Create ID table. Later we will call NSFSearch to find all the
       data notes. The action routine, AddIDUnique, will add the ID of 
       each data note to this ID table.
    */

   if (error = IDCreateTable(sizeof(NOTEID), &hNoteIDTable))
   {
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

   /* Write the ASCII selection formula that we need. */

   formula = "@IsAvailable(NUMBER)";

   /* Compile the selection formula. */

   if (error = NSFFormulaCompile (
       NULL,               /* name of formula (none) */
       0,                  /* length of name */
       formula,            /* the ASCII formula */
       (WORD) strlen(formula),    /* length of ASCII formula */
       &formula_handle,    /* handle to compiled formula */
       &wdc,               /* compiled formula length (don't care) */
       &wdc,               /* return code from compile (don't care) */
       &wdc, &wdc, &wdc, &wdc)) /* compile error info (don't care) */
        
      {
         IDDestroyTable(hNoteIDTable);
         NSFDbClose (db_handle);
         LAPI_RETURN (ERR(error));
      }

   /* Call NSFSearch to find the notes that match the selection criteria. 
      For each note found, the routine AddIdUnique is called. */

   if (error = NSFSearch (
       db_handle,          /* database handle */
       formula_handle,     /* selection formula */
       NULL,               /* title of view in selection formula */
       0,                  /* search flags */
       NOTE_CLASS_DATA,    /* note class to find */
       NULL,               /* starting date (unused) */
       AddIDUnique,        /* call for each note found */
       &hNoteIDTable,      /* argument to AddIDUnique */
       NULL))              /* returned ending date (unused) */

   {
      IDDestroyTable(hNoteIDTable);
      NSFDbClose (db_handle);
      LAPI_RETURN (ERR(error));
   }

   /* Free the memory allocated to the compiled formula. */

   OSMemFree (formula_handle);

   /* Loop over note IDs in the table. Call modify_field on each. */

   error = IDEnumerate(hNoteIDTable, modify_field, &db_handle);

   /* Free the memory containing the ID table */

   IDDestroyTable(hNoteIDTable);

   /* Close the database. */

   NSFDbClose (db_handle) ;

   /* End of main routine. */

   if (error == NOERROR)
     printf("\nProgram completed successfully\n");

   LAPI_RETURN (ERR(error));
}

/************************************************************************
                                                                        
    FUNCTION:   AddIDUnique                                             
                                                                        
*************************************************************************/

STATUS LNPUBLIC AddIDUnique    
            (void far * phNoteIDTable,
            SEARCH_MATCH far *pSearchMatch,
            ITEM_TABLE far *summary_info)
{
   SEARCH_MATCH SearchMatch;
   HANDLE       hNoteIDTable;
   STATUS       error;
   BOOL         flagOK;

    memcpy( (char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH) );

   /*  if (SearchMatch.MatchesFormula != SE_FMATCH)      V3 */
   if (!(SearchMatch.SERetFlags & SE_FMATCH))     /* V4 */
      return (NOERROR);

   hNoteIDTable = *((HANDLE far *)phNoteIDTable);

   error = IDInsert(hNoteIDTable, SearchMatch.ID.NoteID, &flagOK);

   return (ERR(error));
}


/************************************************************************

    FUNCTION:   modify_field

    PURPOSE:    finds the numeric field named NUMBER, and adds one to it.

*************************************************************************/

STATUS LNPUBLIC modify_field (void far * phDB, DWORD NoteID)
{
   DBHANDLE    hDB;
   NOTEHANDLE  note_handle;
   BOOL        field_found;
   NUMBER      number_field;
   STATUS      error;
    
   hDB = *( (DBHANDLE far *)phDB );

   /* Print the note ID. */

   printf ("\nNote ID is: %lX.\n", NoteID);

   /* Open the note. */

   if (error = NSFNoteOpen (
            hDB,                    /* database handle */
            NoteID,                 /* note ID */
            0,                      /* open flags */
            &note_handle))          /* note handle (return) */
   {        
      return (ERR(error));
   }

   /* Look for (and get if it's there) the NUMBER field within this note.*/

   field_found = NSFItemGetNumber ( 
               note_handle, 
               "NUMBER",
               &number_field);

   /* If the NUMBER field was not found, we have nothing to do -- return. */

   if (!field_found)
   { 
      printf ("NUMBER field not found in this document.\n");
      return (NOERROR);
   } 
    
   /* Display what the field is now. */

   printf ("NUMBER field is currently: %f\n", number_field);

   /* Add one to the field and display that value. */

   ++number_field;
   printf ("NUMBER field being changed to: %f\n", number_field);

   /* Write the new field value into the document. */

   if (error = NSFItemSetNumber(note_handle, "NUMBER", &number_field))
   {
      NSFNoteClose (note_handle);
      return (ERR(error));
   }

   /* Write the modified document back to the disk. */

   if (error = NSFNoteUpdate (note_handle, 0))
   {
      NSFNoteClose (note_handle);
      return (ERR(error));
   }

   /* Close the note. */

   if (error = NSFNoteClose (note_handle))
      return (ERR(error));

   /* End of subroutine. */

   return (NOERROR);

}





/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    db_filename get data from the command line or from what 
                the user types at a prompt 

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], char *db_filename)
{ 
#ifndef MAC
    if (argc != 2)  
    {
#endif

      printf("Enter name of database: ");      
      fflush (stdout);
      gets(db_filename);
      
#ifndef MAC
    }    
    else
    {
         strcpy(db_filename, argv[1]);    
      } /* end if */
#endif
} /* ProcessArgs */


