/************************************************************************
    PROGRAM:    srch_all

    FILE:       srch_all.c
                          
    PURPOSE:    Change the "category" field of all docs with category   
                initially "p" to  "q" and set the category of all docs  
                with category initially "q" to "r".                     
                                                                        
    SYNTAX:     srch_all  <database name>                                
                                                                        
    DESCRIPTION:                                                        
        Demonstrates how to use NSFSearch to process all documents in   
        a database without the risk of processing the same note more    
        once.  This ensures that each document gets processed once and  
        only once by building an ID table that is guaranteed to contain 
        exactly one instance of each note ID. Once the search is        
        complete and the ID table is full, then this iterates over IDs
        in the table and processes each note once.
                                                                        
        Opens the specified discussion database and searches for all    
        data notes. Opens each data note and, if the "categories" field 
        contains "p", then this sets the categories field to "q". Else, 
        if the field contains "q", then this sets it to "r".

*************************************************************************/

/* OS/2 and C include files */

#include <stdio.h>
#include <string.h>
#if defined(NT) || defined (OS2_2x) || defined (UNIX) || defined(MAC)
   #include <ctype.h>
#endif

/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <osmem.h>
#include <nsferr.h>
#include <idtable.h>            /* IDCreateTable */


#define     ITEM_NAME_CATEGORIES    "Categories"
#define     CATEGORIES_VALUE_P      "p"
#define     CATEGORIES_VALUE_Q      "q"
#define     CATEGORIES_VALUE_R      "r"


/* Function prototypes */

STATUS LNPUBLIC AddIDUnique (void far *, SEARCH_MATCH far *, ITEM_TABLE far *);
STATUS LNPUBLIC ChangeCategory (void far *, DWORD);


/************************************************************************

   FUNCTION:   NotesMain

   PURPOSE:    Main Notes Lotus C API for Domino and Notes routine

   DESCRIPTION:
         Search the database using NSFSearch with an action routine 
         that inserts each note ID into an ID table. The action routine 
         does not itself open or modify the document. This avoids the 
         possibility of NSFSearch finding the same note again later in 
         the search and calling the action routine a second time to 
         process the same note.

         This technique is valuable when the algorithm requires each 
         note to be processed once and only once.
                                                               
*************************************************************************/
STATUS LNPUBLIC NotesMain (int argc, char *argv[])
{
    char      * szDBName;
    DBHANDLE    hDB;
    STATUS      error;
    HANDLE      hNoteIDTable;

    /*  Get the command line parameters that the user entered. */


    if (argc != 2)
    {
        printf ("\nUsage:  %s  <db filename>  \n", argv[0]);
        return (NOERROR);
    }
    
    szDBName = argv[1];


    /*  Open the database. */

    if (error = NSFDbOpen (szDBName, &hDB))
    {
        printf ("Error: unable to open database '%s'.\n", szDBName);
           return (ERR(error));
    }

    /*  Create ID table then call to NSFSearch.  NSFSearch will find 
        all data notes and call the action routine, AddIDUnique, on each.
        AddIDUnique adds the ID of the data note to the ID table if and
        only if the ID is not already in the table.  The result is a table
        of Note IDs where each ID is guaranteed to appear only once.
     */

    if (error = IDCreateTable(sizeof(NOTEID), &hNoteIDTable))
    {
        printf ("Error: unable to create ID table.\n");
        NSFDbClose (hDB);
        return (ERR(error));
    }

    if (error = NSFSearch (
        hDB,            /* database handle */
        NULLHANDLE,     /* selection formula (select all notes) */
        NULL,           /* title of view in selection formula */
        0,              /* search flags */
        NOTE_CLASS_DATA,/* note class to find */
        NULL,           /* starting date (unused) */
        AddIDUnique,    /* call for each note found */
        &hNoteIDTable,  /* argument to AddIDUnique */
        NULL))          /* returned ending date (unused) */

    {
        printf ("Error: unable to search database.\n");
        IDDestroyTable(hNoteIDTable);
        NSFDbClose (hDB);
        return (ERR(error));
    }

    /*  Loop over note IDs in the table. Call ChangeCategory on each. */
    if (error = IDEnumerate(hNoteIDTable, 
                            ChangeCategory, /* called for each ID */
                            &hDB))          /* arg passed to func */
    {
        printf ("Error: unable to enumerate documents in ID table.\n");
    }

    IDDestroyTable(hNoteIDTable);

    NSFDbClose (hDB);

    if (error == NOERROR)
       printf("\nProgram completed successfully.\n");

    return (ERR(error));
}

/************************************************************************
                                                                        
   FUNCTION:   AddIDUnique

   PURPOSE:    This is the action routine called for each note found
               by NSFSearch.

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

    if (!(SearchMatch.SERetFlags & SE_FMATCH))
        return (NOERROR);


    hNoteIDTable = *((HANDLE far *)phNoteIDTable);

    if (error = IDInsert(hNoteIDTable, SearchMatch.ID.NoteID, &flagOK))
    {
        printf ("Error: unable to insert note ID into table.\n");
        return (ERR(error));
    }
    if (flagOK == TRUE)
    {
        printf ("\tInserted note %lX into table.\n", SearchMatch.ID.NoteID);
    }
    else
    {
        printf ("\tNote %lX is already in table.\n", SearchMatch.ID.NoteID);
    }

    return (NOERROR);
}

/************************************************************************
                                                                        
    FUNCTION:   ChangeCategory                                          
                                                                        
*************************************************************************/

STATUS LNPUBLIC ChangeCategory (void far * phDB, DWORD NoteID)
{
    DBHANDLE    hDB;
    STATUS      error;
    NOTEHANDLE  hNote;
    BOOL        field_found;
    WORD        field_len;
    char        field_text[500];


    printf ("\tProcessing note %lX.\n", NoteID);

    hDB = *( (DBHANDLE far *)phDB );

    if (error = NSFNoteOpen (
            hDB,
            NoteID,
            0,
            &hNote))
    {
        printf ("Error: unable to open note.\n");
        return (ERR(error));
    }

    /*  Look for the "Categories" field within this note. */

    field_found = NSFItemIsPresent ( 
                hNote,
                ITEM_NAME_CATEGORIES,       /* "Categories" */
                (WORD) strlen (ITEM_NAME_CATEGORIES));

    /* If the Categories field is there, get the contents of the field and 
        check to see if it equals "p".  */

    if (!field_found)
    {
        printf ("%s field not found in this note.\n",ITEM_NAME_CATEGORIES);
        NSFNoteClose (hNote);
        return (NOERROR);
    }

    field_len = NSFItemGetText ( 
                hNote, 
                ITEM_NAME_CATEGORIES,
                field_text,
                sizeof (field_text));

    /* Category names are case insensitive.  Do a case insensitive 
           comparison. Since we are just interested in categories that 
           have names of one letter, just ensure that field names
           of only one letter is in lower case. */
   
    if (field_len == 1)
        field_text[1] = tolower (field_text[1]);
  

    if (strcmp(field_text, CATEGORIES_VALUE_P) == 0)
    {
        /* Change "p" to "q" */

        if (error = NSFItemDelete(hNote, 
                        ITEM_NAME_CATEGORIES, 
                        (WORD) strlen(ITEM_NAME_CATEGORIES)))
        {
            printf ("Error: unable to delete item '%s' from note.\n",ITEM_NAME_CATEGORIES);
            NSFNoteClose (hNote);
            return (ERR(error));
        }
        if (error = NSFItemSetText(hNote,
                        ITEM_NAME_CATEGORIES,
                        CATEGORIES_VALUE_Q, 
                        (WORD) strlen(CATEGORIES_VALUE_Q)))
        {
            printf ("Error: unable to set item '%s' to value '%s' in note.\n",
                    ITEM_NAME_CATEGORIES, CATEGORIES_VALUE_Q);
            NSFNoteClose (hNote);
            return (ERR(error));
        }
    }
    else if (strcmp(field_text, CATEGORIES_VALUE_Q) == 0)
    {
        /* Change "q" to "r" */

        if (error = NSFItemDelete(hNote, 
                        ITEM_NAME_CATEGORIES, 
                        (WORD) strlen(ITEM_NAME_CATEGORIES)))
        {
            printf ("Error: unable to delete item '%s' from note.\n",ITEM_NAME_CATEGORIES);
            NSFNoteClose (hNote);
            return (ERR(error));
        }
        if (error = NSFItemSetText(hNote,
                        ITEM_NAME_CATEGORIES,
                        CATEGORIES_VALUE_R, 
                        (WORD) strlen(CATEGORIES_VALUE_R)))
        {
            printf ("Error: unable to set item '%s' to value '%s' in note.\n",
                    ITEM_NAME_CATEGORIES, CATEGORIES_VALUE_R);
            NSFNoteClose (hNote);
            return (ERR(error));
        }
    }

    if (error = NSFNoteUpdate (hNote, 0))
    {
        printf ("Error: unable to update note.\n");
        NSFNoteClose (hNote);
        return (ERR(error));
    }

    if (error = NSFNoteClose (hNote))
    {
        printf ("Error: unable to close.\n");
        return (ERR(error));
    }

    return (NOERROR);
}

