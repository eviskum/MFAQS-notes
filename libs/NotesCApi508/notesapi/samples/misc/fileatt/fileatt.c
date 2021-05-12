/*************************************************************************
 *
 *    FILEATT - Sample program that inserts file attachments into a
 *              document.
 *
 *
 *************************************************************************/

/* Platform specific Header files.  */
#if defined(OS400)
#include <global.h>           /* global.h must be first for AS/400 */
#endif

#ifdef UNIX         /* UNIX */
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#elif defined (MAC) /* MAC */
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#else               /* Wintel */
#include <windows.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <stdio.h>
#endif


 /* Lotus C API for Domino and Notes Header files.  */
#include <lapicinc.h>
#if !defined(OS400)
#include <global.h>
#endif
#include <nsfdata.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <editods.h>
#include <stdnames.h>
#include <osmem.h>
#include <osmisc.h>
#include <ostime.h>
#include <oserr.h>
#include <nsfobjec.h>
#include <misc.h>
#include <osfile.h>
#include <lapiplat.h>

STATUS LNPUBLIC AttachFile1(  /* using NSFNoteAttachFile */
    NOTEHANDLE hNote);

STATUS LNPUBLIC AttachFile2(  /* using low-level FILEOBJECT routines */
    DBHANDLE hDB,
    NOTEHANDLE hNote);

void GetFileT(
    time_t *systime,
    TIMEDATE *pTime);

#if defined(MAC)
extern FSSpec  gSpec;

OSErr GetFileInfo(
    short vRefNum,
    long dirID,
    ConstStr255Param fileName,
    long *dataSize,
    long *crtTime);

OSErr FSpGetFileInfo(
    const FSSpec *spec,
    long *dataSize,
    long *crtTime);

#define LAPI_OpenFile _OpenFile
short _OpenFile ( char * fileName, int permission );
#define READPERM fsRdPerm
#define LAPI_FILE short
#define LAPI_CloseFile(f) FSClose(f)

#elif defined(UNIX)
#define LAPI_OpenFile(f,m) open(f, O_RDONLY, 0777)
#define LAPI_FILE short
#define LAPI_CloseFile(f) close(f)
#define READPERM (_O_RDONLY | _O_BINARY)

#else
#define LAPI_OpenFile(f,m) _open(f,m)
#define LAPI_FILE HFILE
#define LAPI_CloseFile(f) _close(f)
#define READPERM (_O_RDONLY | _O_BINARY)
#endif

/*
 * Global variables
 */

#if defined(MAC) || defined(OS400)
char szSourceFileName[] = "readme.txt";
#elif defined(UNIX)
char szSourceFileName[] = "/opt/lotus/notesapi/samples/misc/fileatt/readme.txt";
#else
char szSourceFileName[] = "c:\\notesapi\\samples\\misc\\fileatt\\readme.txt";
#endif
char szDbName[]         = "embedole.nsf";
char szFormName[]       = "Simple Form";

/*
 *     Main Program
 */

LAPI_MAIN
{
    DBHANDLE hDB;
    NOTEHANDLE hNote;
    WORD ClassDocument = NOTE_CLASS_DOCUMENT;
    STATUS sError = NOERROR;

    LAPI_INIT(sError);
    if (sError)
        LAPI_INIT_ERROR;

    /*
     * Open database
     */

    if (sError = NSFDbOpen(szDbName, &hDB))
    {
        LAPI_RETURN (ERR(sError));
    }

    /*
     * Now create a note in database
     */

    if (sError = NSFNoteCreate(hDB, &hNote))
    {
        NSFDbClose(hDB);
        LAPI_RETURN (ERR(sError));
    }

    NSFNoteSetInfo(hNote, _NOTE_CLASS, &ClassDocument);

    /*
     *  Set the form name. ('Form' field)
     */

    if (sError = NSFItemSetText(hNote,
                                "Form",
                                szFormName,
                                (WORD)strlen(szFormName)))
    {
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN (ERR(sError));
    }

    if (sError = AttachFile1(hNote))
    {
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN (ERR(sError));
    }

    if (sError = AttachFile2(hDB, hNote))
    {
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN (ERR(sError));
    }

    /*
     *  Save the changes
     */

    if (sError = NSFNoteUpdate(hNote, 0))
    {
        NSFNoteClose(hNote);
        NSFDbClose(hDB);
        LAPI_RETURN (ERR(sError));
    }

    /*
     * Close the note
     */

    if (sError = NSFNoteClose(hNote))
    {
        NSFDbClose(hDB);
        LAPI_RETURN (ERR(sError));
    }

    /*
     * Close the database
     */

    if (sError = NSFDbClose(hDB))
    {
        LAPI_RETURN (ERR(sError));
    }

   printf ("\nProgram completed successfully.\n");

    LAPI_RETURN(NOERROR);
}

STATUS LNPUBLIC AttachFile1(  /* using NSFNoteAttachFile */
    NOTEHANDLE hNote)
{
    char szAttachFileName[] = "attach1.txt"; /* UI-visible attachment name */
    STATUS sError;

    if (sError = NSFNoteAttachFile( hNote,
                                    ITEM_NAME_ATTACHMENT,
                                    (WORD) strlen(ITEM_NAME_ATTACHMENT),
                                    szSourceFileName,
                                    szAttachFileName,
                                    HOST_LOCAL | COMPRESS_NONE))
    {
        return(ERR(sError));
    }

    return(NOERROR);
}

STATUS LNPUBLIC AttachFile2(  /* using low-level FILEOBJECT routines */
    DBHANDLE hDB,
    NOTEHANDLE hNote)
{
    char szAttachFileName[] = "attach2.txt"; /* UI-visible attachment name */
    BYTE   *pObjectItemBuffer;
    HANDLE hObjectItemBuffer;
    DWORD  dwObjectID;
    LAPI_FILE hAttachFile;
    WORD *pw;
    char *pchar;
    DWORD dwItemSize;
    FILEOBJECT objFile;
    BLOCKID    bidFile;
    int        i;

#if defined(MAC)
    long crtTime;
#elif defined(UNIX)
    struct  stat AttachStatBuf;
#else
    struct  _stat AttachStatBuf;
#endif

    TIMEDATE MyTimeDate;
    STATUS sError;

    hAttachFile = LAPI_OpenFile(szSourceFileName, READPERM);

    if (hAttachFile == -1)
        return (ERR_NOEXIST);

#if defined(MAC)
    i = FSpGetFileInfo(&gSpec, (long *)&objFile.FileSize, &crtTime);
#elif defined(UNIX)
    i = fstat(hAttachFile, &AttachStatBuf);
    if (i == -1)
        return (ERR_FD);
    objFile.FileSize = AttachStatBuf.st_size;
#else
    i = _fstat(hAttachFile, &AttachStatBuf);
    if (i == -1)
        return (ERR_FD);
    objFile.FileSize = AttachStatBuf.st_size;
#endif

/*
 *  Allocate memory for the object item.
 */

    OSMemAlloc(0, objFile.FileSize, &hObjectItemBuffer);
    pObjectItemBuffer = (BYTE *) OSLockObject(hObjectItemBuffer);

    if (sError = NSFDbAllocObject(hDB,
                                  objFile.FileSize,
                                  NOTE_CLASS_DOCUMENT,
                                  0,
                                  &dwObjectID))

    {
        return (ERR(sError));
    }

    objFile.Header.ObjectType = OBJECT_FILE;
    objFile.Header.RRV = dwObjectID;
    objFile.FileNameLength = strlen(szAttachFileName);
    objFile.HostType = HOST_LOCAL;
    objFile.CompressionType = COMPRESS_NONE;
    objFile.FileAttributes = 0;
    objFile.Flags = 0;

#if !defined(MAC)
    GetFileT(&AttachStatBuf.st_mtime, &MyTimeDate);
#else
    GetFileT((unsigned long *)&crtTime, &MyTimeDate);
#endif

    objFile.FileCreated = MyTimeDate;
    objFile.FileModified = MyTimeDate;

    dwItemSize = (DWORD)(sizeof(WORD) + ODSLength(_FILEOBJECT) + strlen(szAttachFileName));

    if (sError = OSMemAlloc(0, dwItemSize, &bidFile.pool))
    {
      NSFDbFreeObject(hDB, dwObjectID);
        return (ERR(sError));
    }

    bidFile.block = NULLBLOCK;

    pw = OSLockBlock(WORD, bidFile);
    *pw = TYPE_OBJECT;
    pw++;

    pchar = (char *) pw;
   ODSWriteMemory (&pw, _FILEOBJECT, &objFile, 1);
    pchar += ODSLength(_FILEOBJECT);
    memcpy(pchar, szAttachFileName, strlen(szAttachFileName)); 

    OSUnlockBlock(bidFile);

    if (sError = NSFItemAppendObject(hNote,
                                     ITEM_SIGN | ITEM_SEAL | ITEM_SUMMARY,
                                     ITEM_NAME_ATTACHMENT,
                                     (WORD)strlen(ITEM_NAME_ATTACHMENT),
                                     bidFile,
                                     dwItemSize,
                                     TRUE))
    {
      OSMemFree(bidFile.pool);
        return (ERR(sError));
    }

    OSUnlockObject(hObjectItemBuffer);

    pchar = OSLock(char, hObjectItemBuffer);

#if defined(MAC)
    FSRead(hAttachFile, (long *) &objFile.FileSize, pchar);
#elif defined (UNIX)
    read(hAttachFile, pchar, (UINT)objFile.FileSize);
#else
    _read(hAttachFile, pchar, (UINT)objFile.FileSize);
#endif

    OSUnlockObject(hObjectItemBuffer);
    sError = NSFDbWriteObject(hDB,
                              dwObjectID,
                              hObjectItemBuffer,
                              0,
                              objFile.FileSize);

    OSMemFree(hObjectItemBuffer);

    if (sError = NSFNoteUpdate(hNote, 0))
    {
        return (ERR(sError));
    }
    LAPI_CloseFile(hAttachFile);

    return(NOERROR);
}


/***************************************************************************
 *
 *  GetFileT( time_t *systime, TIMEDATE *pTime)
 *
 *  Convert a time stored in a time_t variable to a Domino and Notes TIMEDATE
 *  variable.
 *
 *  Inputs:   systime   - a pointer to a time_t variable containing the
 *                        time to be converted.
 *            pTimeDate - a pointer to a Domino and Notes TIMEDATE variable
 *                        in which to store the converted time.
 *
 *  Outputs:  None
 *
 ****************************************************************************/

void GetFileT(time_t *systime, TIMEDATE *pTime)
{
   
    TIME   NotesTime;
    struct tm *newtime;

    newtime = localtime(&(*systime)); /* Convert time_t to tm structure,    */
                                      /* corrected for the local time zone. */
/*
 * Convert time from the tm structure to a Domino and Notes TIME structure.
 */

    NotesTime.year = (newtime->tm_year) + 1900; /* newtime->tm_year is current year - 1900 */
    NotesTime.month = (newtime->tm_mon) + 1;
    NotesTime.day = newtime->tm_mday;
    NotesTime.weekday = newtime->tm_wday + 1;
    NotesTime.hour = newtime->tm_hour;
    NotesTime.minute = newtime->tm_min;
    NotesTime.second = newtime->tm_sec;
    NotesTime.hundredth = 0;

/*
 *  Set time zone and Daylight Savings Time indicator.
 */

    OSCurrentTimeZone((int *)&NotesTime.zone, (int *) &NotesTime.dst);

/*
 * Use the integer members of the TIME structure to construct the TIMEDATE
 * member of the TIME structure.
 */

    TimeLocalToGM(&NotesTime);
    *pTime = NotesTime.GM;
    return;
}

#if defined(MAC)
/*****************************************************************************/

/* ¦ Get the logical sizes of a file's forks.
   The GetFileInfo function returns the logical size of a file's
   data and resource fork.
   
   vRefNum     input:   Volume specification.
   dirID    input:   Directory ID.
   name     input:   The name of the file.
   dataSize output:  The number of bytes in the file's data fork.
   rsrcSize output:  The number of bytes in the file's resource fork.

   __________
   
   See also:   FSpGetFileSize
*/
/*****************************************************************************/

OSErr GetFileInfo(short vRefNum,
                     long dirID,
                     ConstStr255Param fileName,
                     long *dataSize,
                     long *crtTime)
{
   HParamBlockRec pb;
   OSErr error;
   
   pb.fileParam.ioNamePtr = (StringPtr)fileName;
   pb.fileParam.ioVRefNum = vRefNum;
   pb.fileParam.ioFVersNum = 0;
   pb.fileParam.ioDirID = dirID;
   pb.fileParam.ioFDirIndex = 0;
   error = PBHGetFInfoSync(&pb);
   if ( error == noErr )
   {
      *dataSize = pb.fileParam.ioFlLgLen;
      *crtTime = pb.fileParam.ioFlMdDat;
   }
   return ( error );
}

/*****************************************************************************/

/* ¦ Get the logical sizes of a file's forks.
   The FSpGetFileSize function returns the logical size of a file's
   data and resource fork.
   
   spec     input:   An FSSpec record specifying the file.
   dataSize output:  The number of bytes in the file's data fork.
   crtTime     output:  The time the file was created.

   __________
   
   See also:   GetFileSize
*/

/*****************************************************************************/

OSErr FSpGetFileInfo(const FSSpec *spec,
                        long *dataSize,
                        long *crtTime)
{
   return ( GetFileInfo(spec->vRefNum, spec->parID, spec->name, dataSize, crtTime) );
}

#endif
