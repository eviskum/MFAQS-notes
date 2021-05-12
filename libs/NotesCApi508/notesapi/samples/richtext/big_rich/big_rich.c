/****************************************************************************

    PROGRAM:    big_rich

    FILE:       big_rich.c

    SYNTAX:     big_rich  <server>  <dest. database>  <source directory> 

    FUNCTION:   Reads all the ASCII .TXT files in the source directory
                and stores them in consecutive documents created in the
                destination database.

    PURPOSE:    Demonstrates an API program reading ASCII text files
                into a Domino database, where the text files may be of
                any size. Also shows creation of rich text fields using 
                Compound Text functions.

    DESCRIPTION:

    <server> must specify the Lotus Domino Server where the destination database 
    resides. You may specify "" for <server> to indicate the database is 
    in the local Domino or Notes data directory.

    <destination database> must specify the file name of a Domino discussion 
    database. An example database big_rich.nsf is included with the Lotus C API 
	for Domino and Notes toolkit. The database must exist and the user must have at least
    author access. The design of the destination database must be the same
    as big_rich.nsf, based on the discussion DB template provided with Domino and Notes.
    
    <source directory> must specify a source directory. The source 
    directory may contain any number of ASCII files. ASCII files must 
    have a filename ending in .txt. These ASCII files may be of
    arbitrary length.

    EXAMPLE:    big_rich  ""  big_rich  c:\temp

    BIG_RICH reads all the files ending in .txt found in the source 
    directory, and creates a Domino and Notes document in the destination database 
    for each file. 

    The "From" field of each document gets the name of the user who
    is running this program (obtained from the ID file).  The "Category" 
    field gets the directory name specified. The "Body" field gets the 
    complete text from the file, converted to rich text format. The 
    "Subject" field of each document gets the file name. 

****************************************************************************/

#if defined (OS2_2x)
#define INCL_DOSFILEMGR
#define INCL_DOSERRORS                                                                
#include <os2.h>
#elif defined (W32)
#include <windows.h>
#else
	#error "Only supported on OS/2 and 32-bit Windows systems."
#endif

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <memory.h>                     /* _fmemset() */
#include <stdlib.h>                     /* atol() */

/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <ods.h>
#include <names.h>                      /* MAXUSERNAME */
#include <stdnames.h>                   /* FIELD_FORM */
#include <osmem.h>
#include <osfile.h>
#include <ostime.h>
#include <editods.h>
#include <editdflt.h>
#include <easycd.h>
#include <fontid.h>
#include <misc.h>
#include <kfm.h>
#include <acl.h>
 
/* Function prototypes */
STATUS LNPUBLIC OpenNotesDB          (char *, char *, DBHANDLE *);
STATUS LNPUBLIC ProcessOneFile       (DBHANDLE, char *, char *);
STATUS LNPUBLIC AppendFormItem       (NOTEHANDLE);
STATUS LNPUBLIC AppendFromItem       (NOTEHANDLE);
STATUS LNPUBLIC AppendCategoriesItem (NOTEHANDLE, char *);
STATUS LNPUBLIC AppendBodyItem       (NOTEHANDLE, char *);
STATUS LNPUBLIC AppendSubjectItem    (NOTEHANDLE, char *);

/* Local Defines */
/* #define FILENAME_EXTENSION      ".txt" */
#define FILENAME_EXTENSION      ".txt"
#define ERR_BIGRICH_DBOPEN      (PKG_ADDIN + 1)

/* Item names. These depend on the design of the forms in the target
 * database.
 */
#define BIGRICH_ITEM_FROM       "From"
#define BIGRICH_ITEM_CATEGORIES "Categories"
#define BIGRICH_ITEM_BODY       "Body"
#define BIGRICH_ITEM_SUBJECT    "Subject"


/************************************************************************
                                                                        
    FUNCTION:   NotesMain                                               
                                                                        
*************************************************************************/

STATUS LNPUBLIC NotesMain (int argc, char *argv[])
{
    char       * szServerName;    /* name of Lotus Domino Server where DB resides */
    char       * szDbPathName;    /* pathname of database, e.g. "big_rich" */
    char       * szDirectory;     /* directory containing ASCII files */
    DBHANDLE     hDb;             /* handle to database specified */
    char         szFileSpec[MAXPATH]; /* filespec = path\*.txt */
#if defined (OS2)
    HDIR         hDir = HDIR_SYSTEM; /* handle to dir containing files */
    FILEFINDBUF3 FileFind = {0};  /* see OS/2 doc on DosFindFirst */
    ULONG        ulFindCount = 1;
#elif defined (W32)
	HANDLE		hFind;				/* File search handle */
	WIN32_FIND_DATA	FileFindData = {0};	/* File search data */
#endif
    USHORT       usFileCount;
    STATUS       error = NOERROR; /* return code from API calls */

    /*  Process arguments. */
    if (argc != 4)
    {
        printf ("Usage: %s <server> <dest database> <src directory>\n",
                argv[0]);
        goto Exit0;
    }
    szServerName = argv[1];
    szDbPathName = argv[2];
    szDirectory  = argv[3];

    /* Open Domino DB. Sets hDb */
    if (error = OpenNotesDB (szServerName, szDbPathName, &hDb))
    {
        goto Exit0;
    }

/*  Loop over ASCII files in the directory. Add a new note for each.*/
    strcpy (szFileSpec, szDirectory);
    strcat (szFileSpec, "\\*");
    strcat (szFileSpec, FILENAME_EXTENSION); /*.TXT*/
#if defined (OS2)
    if (DosFindFirst(szFileSpec,
                     &hDir,
                     FILE_NORMAL,
                     &FileFind,
                     sizeof(FILEFINDBUF3),
                     &ulFindCount,
                     FIL_STANDARD))
#elif defined (W32)
	hFind = FindFirstFile (szFileSpec, &FileFindData);
	if (INVALID_HANDLE_VALUE == hFind)
#endif
    {
        printf ("Error: no files found matching '%s'\n", szFileSpec);
        goto Exit1;
    }

    usFileCount=0; 
    do
    {
#if defined (OS2)
        if (error = ProcessOneFile (hDb, FileFind.achName, szDirectory))
#elif defined (W32)
		if (error = ProcessOneFile (hDb, FileFindData.cFileName, szDirectory))
#endif
        {
            goto Exit1;
        }
        usFileCount++;

#if defined (OS2)
    }   while (DosFindNext(hDir, &FileFind, sizeof(FILEFINDBUF),
                        &ulFindCount) == 0);
#elif defined (W32)
	}  while (FindNextFile (hFind, &FileFindData));
#endif

    printf ("%s: successfully processed %d files.\n", argv[0], usFileCount);
                        
Exit1:
    NSFDbClose (hDb);

Exit0:
    return (ERR(error));
}                     

/************************************************************************
                                                                        
     FUNCTION:  OpenNotesDB()                                           
                                                                        
     PURPOSE:   Open the Domino Db (nsf file) on the specified server.   
                                                                        
*************************************************************************/

STATUS LNPUBLIC   OpenNotesDB (char * pServer, char * pNsfName, 
                                DBHANDLE * phDb)
{
    STATUS  error ;
    char    fullpath_name[MAXPATH];

    if (strlen (pServer) != 0) /* remote server specified */
    {
        error = OSPathNetConstruct (NULL, pServer, pNsfName, fullpath_name);
        if (error != NOERROR)
        {
            printf ("Error: unable to construct network path to database.\n");
            return (error);
        }
    }
    else                                /* DB is LOCAL: just use nsf name */
        strcpy (fullpath_name, pNsfName);               

    /* Check user input in case DB full path name too long */

    if (strlen (fullpath_name) > MAXPATH)
    {
        printf ("Error: Database full path name: '%s'\n is longer than %i\n",
                fullpath_name, MAXPATH);
        return (ERR_BIGRICH_DBOPEN);
    }

    if (error = NSFDbOpen (fullpath_name, phDb))
    {
        printf ("Error: unable to open database '%s'.\n", fullpath_name);
        return (error);
    }                    
    return (NOERROR);
}

/************************************************************************
                                                                        
     FUNCTION:  ProcessOneFile()                                        
                                                                        
     PURPOSE:   Create a new note in the specified DB. Store text from
                the specified file in the body of the new note.
                                                                        
*************************************************************************/
   
STATUS  LNPUBLIC  ProcessOneFile(DBHANDLE    hDb, char * szAsciiFileName, 
                                                 char * szDirectory)
{
    char        szFullFilePath[MAXPATH]; /* path and file name */
    NOTEHANDLE  hNote;
    STATUS        error;      /* return code from API calls */
    STATUS        error2;     /* return code from API calls in exit path */

    /* Format the qualified input file name. */

    strcpy (szFullFilePath, szDirectory);
    strcat (szFullFilePath, "\\"); 
    strcat (szFullFilePath, szAsciiFileName); 

    /* Create a new data note. */

    if (error = NSFNoteCreate (hDb, &hNote))
    {
        printf ("Error: unable to create note.\n");
        goto Exit0;
    }

    /* Append Form item to the note: "MainTopic" */
    if (error = AppendFormItem (hNote))  goto Exit1;

    /* Append From item to note = name of user. Author Names data type. */
    if (error = AppendFromItem (hNote)) goto Exit1;

    /* Append Categories Item to note = the directory name specified */
    if (error = AppendCategoriesItem (hNote, szDirectory)) goto Exit1;

    /* Append Body Item to note containing text from the file */
    if (error = AppendBodyItem (hNote, szFullFilePath)) goto Exit1;

    /* Append Subject item to note = name of ascii file */
    if (error = AppendSubjectItem (hNote, szAsciiFileName))  goto Exit1;

    /* Add the entire new note (with all items) to the database. */

    if (error = NSFNoteUpdate (hNote, 0))
    {
        printf ("Error: unable to update note to disk.\n");
    }
    else
    {
        printf ("big_rich: created note from file '%s'.\n", szAsciiFileName);
    }

Exit1:
    /*  Close the new note. */
    if (error2 = NSFNoteClose (hNote))
    {
        printf ("Error: unable to close note.\n");
        if (error == NOERROR) error = error2;
    }
Exit0:
    return (ERR(error));
}

/************************************************************************
                                                                        
    FUNCTION:   AppendFormItem                                          
                                                                        
*************************************************************************/

STATUS  LNPUBLIC  AppendFormItem (NOTEHANDLE  hNote)
{
    STATUS  error;

    if (error = NSFItemSetText ( hNote, 
                    FIELD_FORM,         /* "Form" */
                    "Main Topic", 
                    MAXWORD))
    {
        printf ("Error: unable to set text in Form field.\n");
    }
    return (error);
}

/************************************************************************
                                                                        
    FUNCTION:   AppendFromItem                                          
                                                                        
*************************************************************************/

STATUS LNPUBLIC AppendFromItem (NOTEHANDLE  hNote)
{
    STATUS      error;
    char        szDocAuthor[MAXUSERNAME+1];

    /* Get Current User name */
    if (error = SECKFMGetUserName (szDocAuthor))
    {
        printf ("Error: unable to get current user name.\n");
        return (error);
    }
                
    if (error = NSFItemAppend (  
                    hNote,
                    ITEM_SUMMARY | ITEM_NAMES | ITEM_READWRITERS,
                    BIGRICH_ITEM_FROM,      /* "From" */
                    (WORD) strlen(BIGRICH_ITEM_FROM),
                    TYPE_TEXT, 
                    szDocAuthor,
                    (DWORD) strlen (szDocAuthor)))
    {
        printf ("Error: unable to set From item in note.\n");
    }
    return (error);
}

/************************************************************************
                                                                        
    FUNCTION:   AppendCategoriesItem                                    
                                                                        
*************************************************************************/

STATUS  LNPUBLIC  AppendCategoriesItem (NOTEHANDLE hNote, char * szFullPath)
{
    STATUS      error;
    char      * szCategories;

    /* parse the last dir from the path and use it as the category */

    if (szCategories = strrchr (szFullPath, '\\'))
    {
        /* step over the backslash to first char of file name */
        szCategories++;
    }
    else
        szCategories = szFullPath;

    if (error = NSFItemSetText (hNote, 
                    BIGRICH_ITEM_CATEGORIES,/* "Categories" */
                    szCategories, 
                    MAXWORD))
    {
        printf ("Error: unable to set text in Categories field.\n");
    }
    return (error);
}

/************************************************************************

    FUNCTION:   AppendBodyItem

    PURPOSE:    Appends a compound (rich) text item "Body" to a note
                containing the text from the specified file.

    INPUTS:      
        NOTEHANDLE  hNote;            open note to append Body field to
        char        *szFullFilePath;  path and file name of ASCII text file

    RETURNS:   
        NOERROR or status returned from a Lotus C API for Domino and 
		Notes function call.

*************************************************************************/

STATUS  LNPUBLIC  AppendBodyItem (NOTEHANDLE hNote, char * szFullFilePath)
{
    STATUS          error;
    HANDLE          hCompound;      /* Compound Text context */
    COMPOUNDSTYLE   Style;
    DWORD           dwStyleID;

    /* Create compound text context. This initializes hCompound. */
    if (error = CompoundTextCreate (
                        hNote, 
                        BIGRICH_ITEM_BODY,  /* "Body" */
                        &hCompound)) 
    {
        printf ("Error: unable to create Compound Text context.\n");
        return (error);
    }

    /* Initialize Style */
    CompoundTextInitStyle (&Style);

    /*  Define a default compound text style. */
    if (error = CompoundTextDefineStyle (hCompound, "", &Style, 
                                         &dwStyleID))
    {
        printf ("Error: unable to define Compound Text style.\n");
        CompoundTextDiscard (hCompound);
        return (error);
    }
 
    /* Add text from the file to the compound text context */
    if (error = CompoundTextAddTextExt (
                        hCompound,              /* context */
                        dwStyleID,              /* style  */
                        DEFAULT_FONT_ID,        /* font ID */
                        szFullFilePath,         /* text file name */
                        (DWORD) strlen (szFullFilePath),/* name length */
                        "\r\n",                 /* newline delimiter */
                        COMP_FROM_FILE |        /* take input from file */
                        COMP_PRESERVE_LINES,    /* preserve line breaks */
                        /* don't specify any paragraph directive: 1K each */
                        NULLHANDLE))            /* CLS translation table */
    {
        printf("Error: unable to add text from file '%s' to Compound Text.\n",
                                 szFullFilePath);
        CompoundTextDiscard (hCompound);
        return (error);
    }

    /* Close the compound text context. This adds the CD text to the note. */
    if (error = CompoundTextClose (hCompound, 0, 0L, NULL, 0))
    {
        printf ("Error: unable to add Compound Text to document.\n");
        CompoundTextDiscard (hCompound);
    }

    return (error);
}
/************************************************************************
                                                                        
    FUNCTION:   AppendSubjectItem                                       
                                                                        
*************************************************************************/

STATUS LNPUBLIC AppendSubjectItem( NOTEHANDLE hNote, char * szAsciiFileName)
{
    STATUS  error;

    if (error = NSFItemSetText (hNote, 
                    BIGRICH_ITEM_SUBJECT,   /* "Subject" */
                    szAsciiFileName, 
                    MAXWORD))
    {
        printf ("Error: unable to set Subject field in note.\n");
    }
    return (error);
}


