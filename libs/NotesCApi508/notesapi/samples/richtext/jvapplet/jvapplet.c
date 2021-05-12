/***********************************************************************

   File:        jvapplet.c

   Program:     jvapplet

   Purpose:     shows how to embed a Java Applet in the document.

   Description:

       This sample creates a document in the database specified 
       in the input parameter.  This document will contain a local 
       applet which prints the title of the current database.  The 
       server name and database name of the current database are 
       passed to the local applet through the @dbName formula.

       First, this program opens the specified database, and creates 
       a new note. It then allocates a buffer in which to construct 
       the rich text item. In this buffer, it creates the following 
       sequence of data structures to provide information for the 
       Java Applet:

       CDRECORDBEING
       CDV4HOTSPOTBEGIN
       CDACTIVEOBJECT
       CDACTIVEOBJECTPARAM  (this structure is used to pass a parameter
                             to the Java Applet.  In this sample,
                             we will use 2 CDACTIVEOBJECTPARAM
                             structures, one for passing the servername
                             and one for passing the db name.)
       CDACTIVEOBJECTSTORAGELINK
       CDV4HOTSPOTEND
       CDRECORDEND

 
       The buffer thus created is then appended to the note's rich text
       field. 
       
       The program then attachs the Java Applet class file to the note.
       
       The note is then updated and closed, the database is closed, and 
       the program exits.



************************************************************************/

/*
 *  OS includes
 */

#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

/*
 *  Lotus C API for Domino and Notes includes
 */

#include <lapicinc.h>

#include <global.h>
#include <nsf.h>
#include <osmem.h>
#include <names.h>
#include <editods.h>
#include <nsfnote.h>
#include <osmisc.h>
#include <oserr.h>
#include <stdnames.h>

#include <lapiplat.h>

#define FORMNAME                "Simple Form"
#define APPLET_PARM_NAME_SERVER "serverName"
#define APPLET_PARM_NAME_DB     "dbName"
#define SERVERNAME_VALUE_FORMULA "@Subset(@DbName;1)"
#define DBNAME_VALUE_FORMULA "@Subset(@DbName;-1)"

#define STRING_LENGTH  256
#define APPLET_WIDTH   462
#define APPLET_HEIGHT  120

char AppletCodeBase[]  = "notes:///./$FILE";
char CodeString[]      = "IntroLocalApplet.class";

char server_name[80];
char db_name[MAXPATH];

#if defined(UNIX)
char CodeStringFullPath[] = "/opt/lotus/notesapi/samples/richtext/jvapplet/IntroLocalApplet.class";
#else
char CodeStringFullPath[] = "c:\\notesapi\\samples\\richtext\\jvapplet\\IntroLocalApplet.class";
#endif


/*
 *  Forward Declaration
 */ 

void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                             char *db_filename); 

STATUS InsertRichText(NOTEHANDLE hNote);

         
STATUS InsertJavaAppletLink(NOTEHANDLE hNote,
                               char FAR * FAR *ppCDBuffer,
                               WORD FAR *pwItemSize,
                               WORD wBufferSize);  
                         
STATUS InsertJavaAppletAttachment(NOTEHANDLE hNote,
                               char FAR * FAR *ppCDBuffer,
                               WORD FAR *pwItemSize,
                               WORD wBufferSize);

/*
 *  Body of main program
 */

LAPI_MAIN
{
    char       *db_filename;
    HANDLE      hNewNote;
    DBHANDLE    hDbNSFFile;
    STATUS      sError = NOERROR;
    char        database_name[STRING_LENGTH];

    /*   Read in the database name.  */
    db_filename = database_name;
    ProcessArgs(argc, argv, db_filename);

    /*   Start by calling Notes Init.  */

    LAPI_INIT(sError);
    if (sError)
       LAPI_INIT_ERROR;


    /* Open the Database which we're going to create a new */
    /* document to host the local applet.                  */
    
    if (sError = NSFDbOpen(db_filename, &hDbNSFFile))
        LAPI_RETURN (ERR(sError));


    /* Create a Note */
    
    if (sError = NSFNoteCreate(hDbNSFFile, &hNewNote))
    {
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }

    /* Fill in the Form name  */
    
    if (sError = NSFItemSetText(hNewNote,
                                 "Form",
                                 FORMNAME,
                                 (WORD) strlen(FORMNAME)))
    {
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }


    /*
     *  Create the richtext item, which will contain inf. about the
     *  applet.
     */

    if (sError = InsertRichText(hNewNote))
    
    {
        NSFNoteClose(hNewNote);    /* Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }

    /*
     *  Attach the Java class file to the note.
     */

    if (sError = NSFNoteAttachFile(hNewNote,
                                ITEM_NAME_ATTACHMENT,
                                (WORD) strlen(ITEM_NAME_ATTACHMENT),
                                CodeStringFullPath,
                                CodeString,
                                HOST_STREAM))

     {
        printf("Couldn't find the class file at : %s\n",CodeStringFullPath);
        NSFNoteClose(hNewNote);    /* Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* Close database before exit.*/
        LAPI_RETURN (ERR(sError));
     }

    /* write the note */

    if (sError = NSFNoteUpdate(hNewNote, 0))
    {
        NSFNoteClose(hNewNote);    /* ERROR - Close note before exit.    */
        NSFDbClose(hDbNSFFile);    /* ERROR - Close database before exit.*/
        LAPI_RETURN (ERR(sError));
    }

    /* Start cleaning up.  First, Close the Note */
    
    NSFNoteClose(hNewNote);

    /* Now close the database.              */
    
    if (sError = NSFDbClose(hDbNSFFile))
        LAPI_RETURN (ERR(sError));


    printf ("\nProgram completed successfully.\n");

    LAPI_RETURN (NOERROR);            /* Return normally.  */
}


/***********************************************************************
 *
 * InsertRichText
 *
 *      Allocate a buffer in which to build the rich text item. Insert
 *      inf. about the Java Applet. Then append the buffer to the note.
 *
 * Inputs:   hNote   - handle to the new note being created.
 *
 * Outputs:  None.
 *
 ************************************************************************/


STATUS InsertRichText(NOTEHANDLE hNote)

{
    HANDLE    hMem;
    STATUS    sError;         /* Domino and Notes error status        */
    char FAR  *pCDBuffer;
    char FAR  *pCDBufferStart;
    WORD      wItemSize = 0, wBufferSize = MAXONESEGSIZE;

/*
 *  Allocate a buffer.
 */

    if (sError = OSMemAlloc(0, wBufferSize, &hMem))
        return (ERR_MEMORY);
        
    if ((pCDBuffer = (char far *) OSLockObject(hMem)) == NULL)
        return (ERR_MEMORY);
        
    memset(pCDBuffer, '\0', wBufferSize);
    pCDBufferStart = pCDBuffer;


/*
 *  Insert inf. about the Applet.
 */
    if (sError = InsertJavaAppletLink(hNote, &pCDBuffer, &wItemSize, 
                                      wBufferSize))
    {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
        return (ERR(sError));
    }


/*
 *  All done creating the richtext field.  Now append it to the note.
 */

     if (sError = NSFItemAppend(hNote,
                                0,
                                "Body",
                                (WORD) strlen("Body"),
                                TYPE_COMPOSITE,
                                pCDBufferStart,
                                pCDBuffer-pCDBufferStart))

     {
        OSUnlockObject(hMem);
        OSMemFree(hMem);
         return (ERR(sError));
     }

    OSUnlockObject(hMem);
    OSMemFree(hMem);
    
    return (NOERROR);
}


/***********************************************************************
 * InsertJavaAppletLink
 *                The steps needed to do this are:
 **
 *                - Create an CDBEGINRECORD, append it to the buffer. 
 *
 *                - Create an appropriate CDV4HOTSPOTBEGIN record
 *                  and append it to the buffer.  CDV4HOTSPOTBEGIN structure
 *                  is followed by the following structures:
 *                  
 *                      CDACTIVEOBJECT
 *                      CDACTIVEOBJECTPARAM
 *                      CDACTIVEOBJECTSTORAGELINK
 *
 *                - Add a CDV4HOTSPOTEND record to the buffer.
 *
 *                - Add a CDRECORDEND record to mark the end of the buffer.
 *
 *
 *
 * Inputs:     hNote       - handle to the new note being created.
 *             ppCDBuffer  - Handle to buffer containing CD records being 
 *                           created.
 *             pwItemSize  - current length of item.
 *             wBufferSize - total size of CD buffer.
 *             
 * Outputs:    None.
 *************************************************************************/


STATUS InsertJavaAppletLink(NOTEHANDLE hNote,
                 char FAR * FAR *ppCDBuffer,
                 WORD FAR *pwItemSize,
                 WORD wBufferSize)

{
    STATUS sError = NOERROR;
    CDBEGINRECORD           BeginRecord;
    CDHOTSPOTBEGIN          V4HotSpotBegin;
    ACTIVEOBJECT            ao;
    ACTIVEOBJECTPARAM       aoParam;
    ACTIVEOBJECTSTORAGELINK aoStorageLink;
    CDENDRECORD             EndRecord;
    CDHOTSPOTEND            V4HotSpotEnd;
  
    FORMULAHANDLE hFormula1;
    FORMULAHANDLE hFormula2;
    char * pFormula1;
    char * pFormula2;
    WORD   wFormulaLen1;
    WORD   wFormulaLen2;
    WORD   wdc;


/*
 *  Compile Java Applet's parameter.
 */
    if (sError = NSFFormulaCompile(NULL,0,SERVERNAME_VALUE_FORMULA,
                                   (WORD)strlen(SERVERNAME_VALUE_FORMULA),
                                   &hFormula1,
                                   &wFormulaLen1,
                                   &wdc, &wdc, &wdc,
                                   &wdc, &wdc))
    {
        OSUnlockObject(hFormula1);
        OSMemFree(hFormula1);
        return(sError);
    }

    pFormula1 = (char *) OSLockObject(hFormula1);

    if (sError = NSFFormulaCompile(NULL,0,DBNAME_VALUE_FORMULA,
                                   (WORD)strlen(DBNAME_VALUE_FORMULA),
                                   &hFormula2,
                                   &wFormulaLen2,
                                   &wdc, &wdc, &wdc,
                                   &wdc, &wdc))
    {
        OSUnlockObject(hFormula2);
        OSMemFree(hFormula2);
        OSUnlockObject(hFormula1);
        OSMemFree(hFormula1);
        return(sError);
    }

    pFormula2 = (char *) OSLockObject(hFormula2);

    
/*  ***********************************************
    Fill up structure "Begin - V4HotspoBegin
    *********************************************** 
*/

    BeginRecord.Signature = SIG_CD_V4HOTSPOTBEGIN;
    BeginRecord.Version   = 0;

    
    BeginRecord.Header.Signature = SIG_CD_BEGIN;
    BeginRecord.Header.Length    = (BYTE)ODSLength(_CDBEGINRECORD);

    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _CDBEGINRECORD, &BeginRecord, 1);

    *pwItemSize += BeginRecord.Header.Length;

    if (*pwItemSize %2)
        *pwItemSize +=1;


/*  ************************************************
    Fill up structure "V4HotspotBegin - ActiveObject
    ************************************************
*/

/*
 *  Set various flags 
 */
    
    V4HotSpotBegin.Type  = HOTSPOTREC_TYPE_ACTIVEOBJECT;
    V4HotSpotBegin.Flags = HOTSPOTREC_RUNFLAG_NOBORDER;

/*
 *  Set data length
 */

    V4HotSpotBegin.DataLength = ODSLength(_ACTIVEOBJECT) +
                                ODSLength(_ACTIVEOBJECTSTORAGELINK) + 
                                strlen(AppletCodeBase) +
                                strlen(CodeString) +
                                ODSLength(_ACTIVEOBJECTPARAM) + 
                                strlen(APPLET_PARM_NAME_SERVER) +
                                wFormulaLen1 +
                                ODSLength(_ACTIVEOBJECTPARAM) + 
                                strlen(APPLET_PARM_NAME_DB) +
                                wFormulaLen2 +
                                strlen(CodeString);


/*
 *  Set the header info.
 */
    
    V4HotSpotBegin.Header.Signature = SIG_CD_V4HOTSPOTBEGIN;
    V4HotSpotBegin.Header.Length    = ODSLength(_CDHOTSPOTBEGIN) +
                                ODSLength(_ACTIVEOBJECT) +
                                ODSLength(_ACTIVEOBJECTSTORAGELINK) + 
                                strlen(AppletCodeBase) +
                                strlen(CodeString) +
                                ODSLength(_ACTIVEOBJECTPARAM) + 
                                strlen(APPLET_PARM_NAME_SERVER) +
                                wFormulaLen1 +
                                ODSLength(_ACTIVEOBJECTPARAM) + 
                                strlen(APPLET_PARM_NAME_DB) +
                                wFormulaLen2 +
                                strlen(CodeString);


    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _CDHOTSPOTBEGIN, &V4HotSpotBegin, 1);


/*
 *  Set ACTIVEOBJECT inf.
 */
    (void) memset(&ao,0,sizeof(ACTIVEOBJECT));
    ao.ObjectType       = ACTIVEOBJECT_TYPE_JAVA;
    ao.WidthUnitType    = ACTIVEOBJECT_UNIT_PIXELS;
    ao.HeightUnitType   = ACTIVEOBJECT_UNIT_PIXELS;
    ao.Width            = APPLET_WIDTH;
    ao.Height           = APPLET_HEIGHT;
    ao.CodebaseLength   = strlen(AppletCodeBase);
    ao.CodeLength       = strlen(CodeString);
    ao.ObjectNameLength = 0;
    ao.StorageLinkCount = 1;
    ao.ParamCount       = 2;    /* one for serverName, one for dbName */
    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _ACTIVEOBJECT, &ao, 1 );

/*
 *  Set variable data after ACTIVEOBJECT
 */
    memcpy(*ppCDBuffer, AppletCodeBase, ao.CodebaseLength);
    *ppCDBuffer += ao.CodebaseLength;

    memcpy(*ppCDBuffer, CodeString, ao.CodeLength);
    *ppCDBuffer += ao.CodeLength;


/*
 *  Set ActiveObjectParam - this structure is used to pass the server
 *  name to the Java Applet.
 */
    (void) memset(&aoParam,0,sizeof(ACTIVEOBJECTPARAM));
    aoParam.Length        = strlen(APPLET_PARM_NAME_SERVER);
    aoParam.FormulaLength =wFormulaLen1;
    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _ACTIVEOBJECTPARAM, &aoParam,1);

/*
 *  Set variable data after ActiveObjectParam
 */
    memcpy(*ppCDBuffer, APPLET_PARM_NAME_SERVER, aoParam.Length);
    *ppCDBuffer += aoParam.Length;

    memcpy(*ppCDBuffer, pFormula1, aoParam.FormulaLength);
    *ppCDBuffer += aoParam.FormulaLength;

/*
 *  Set ActiveObjectParam - this structure is used to pass the Db
 *  name to the Java Applet.
 */
    (void) memset(&aoParam,0,sizeof(ACTIVEOBJECTPARAM));
    aoParam.Length        = strlen(APPLET_PARM_NAME_DB);
    aoParam.FormulaLength =wFormulaLen2;
    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _ACTIVEOBJECTPARAM, &aoParam,1);

/*
 *  Set variable data after ActiveObjectParam
 */
    memcpy(*ppCDBuffer, APPLET_PARM_NAME_DB, aoParam.Length);
    *ppCDBuffer += aoParam.Length;

    memcpy(*ppCDBuffer, pFormula2, aoParam.FormulaLength);
    *ppCDBuffer += aoParam.FormulaLength;

    OSUnlockObject(hFormula1);
    OSUnlockObject(hFormula2);
    OSMemFree(hFormula1);
    OSMemFree(hFormula2);


/*
 *  Set ACTIVEOBJECTSTORAGELINK
 */
    (void) memset(&aoStorageLink,0,sizeof(ACTIVEOBJECTSTORAGELINK));
    aoStorageLink.Length = strlen(CodeString); 
    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _ACTIVEOBJECTSTORAGELINK, &aoStorageLink, 1);    

/*
 *  Set variable data after ACTIVEOBJECTSTORAGELINK
 */
    memcpy(*ppCDBuffer, CodeString, aoStorageLink.Length);
    *ppCDBuffer += aoStorageLink.Length;

    *pwItemSize += V4HotSpotBegin.Header.Length;
    if (*pwItemSize %2)
        *pwItemSize +=1;



/*  ************************************************
    Fill up structure "V4HotspotEnd"
    ************************************************
*/

    V4HotSpotEnd.Header.Length    = (BYTE)ODSLength(_CDHOTSPOTEND);
    V4HotSpotEnd.Header.Signature = SIG_CD_V4HOTSPOTEND;
    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _CDHOTSPOTEND, &V4HotSpotEnd, 1);    

  
    *pwItemSize += V4HotSpotEnd.Header.Length;
    if (*pwItemSize %2)
        *pwItemSize +=1;

/*  ************************************************
    Fill up structure "End - V4HotspotEnd"
    ************************************************
*/

    EndRecord.Signature = SIG_CD_V4HOTSPOTEND;
    EndRecord.Version   = 0;

    
    EndRecord.Header.Signature = SIG_CD_END;
    EndRecord.Header.Length    = (BYTE)ODSLength(_CDENDRECORD);

    ODSWriteMemory( (void far * far *) ppCDBuffer, 
                   _CDENDRECORD, &EndRecord, 1);    

  
    *pwItemSize += EndRecord.Header.Length;
    if (*pwItemSize %2)
        *pwItemSize +=1;
    
/*
 *  Done.
 */
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

    if (argc != 2)  
    {
      printf("Enter name of database: ");      
      fflush (stdout);
      gets(db_filename);
    }    
    else
    {
         strcpy(db_filename, argv[1]);    
      } /* end if */

} /* ProcessArgs */

