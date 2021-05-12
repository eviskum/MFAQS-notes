#include <ole2.h>
#include <ole2ver.h>
#include "initguid.h"

/* C header files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes Header files */

#include <lapicinc.h>
#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsferr.h>
#include <nsfsearc.h>
#include <osmem.h>
#include <nsfole.h>
#include <lapiplat.h>


/* Forward declarations */

STATUS LNPUBLIC ProcessOneNote(
  void far *phDB, 
  SEARCH_MATCH far *pSearchMatch,
  ITEM_TABLE far *Unused);

STATUS LNPUBLIC ProcessOneCDRecord(
  char far *pRecord,
  WORD wRecordType,
  DWORD dwRecordLength,
  void far *phNote);

/*
 *  Main Program
 */

LAPI_MAIN
{

  DBHANDLE hDb;
  char * formula= "@IsAvailable($OLEOBJINFO)";
  FORMULAHANDLE hFormula;
  WORD wdc;  /* "we don't care" return args for NSFFormulaCompile */
  STATUS error=0;

  LAPI_INIT(error);
  if (error)
    LAPI_INIT_ERROR;
   
  if (error = NSFDbOpen("embedole.nsf", &hDb))
  {
    printf("NSFDbOpen failed...\n");
    LAPI_RETURN(ERR(error));
  }

  /* Compile the selection formula. */

  if (error = NSFFormulaCompile(NULL,
                                0,
                                formula,
                                (WORD)strlen(formula),
                                &hFormula,
                                &wdc,
                                &wdc,
                                &wdc,
                                &wdc,
                                &wdc,
                                &wdc))
  {
    NSFDbClose(hDb);
    LAPI_RETURN(ERR(error));
  }

  /* Call ProcessOneNote for each note containing an embedded OLE2 object. */

  if (error = NSFSearch(hDb,
                        hFormula,
                        NULL,
                        0,
                        NOTE_CLASS_DATA,
                        NULL,
                        ProcessOneNote,
                        &hDb,
                        NULL))
  {
    NSFDbClose(hDb);
    LAPI_RETURN(ERR(error));
  }

  /* Free the memory allocated to the compiled formula. */

  OSMemFree(hFormula);

  /* Close the database. */

  NSFDbClose(hDb) ;

  /* End of main routine. */

  LAPI_RETURN(ERR(error));

}


/************************************************************************

    FUNCTION:   ProcessOneNote

    PURPOSE:    Action routine called for each note containing an embedded
	            OLE2 object.  In turn, calls action routine for each CD
				record in the $OLEOBJINFO item.

*************************************************************************/

STATUS LNPUBLIC ProcessOneNote(
  void far *phDB, 
  SEARCH_MATCH far *pSearchMatch,
  ITEM_TABLE far *Unused )
{   

  SEARCH_MATCH SearchMatch;    
  DBHANDLE hDB;
  NOTEHANDLE hNote;
  WORD wDataType;
  BLOCKID bidValue;
  DWORD dwValueLen;
  STATUS error;

  memcpy((char *)&SearchMatch, (char *)pSearchMatch, sizeof(SEARCH_MATCH));

  if (!(SearchMatch.SERetFlags & SE_FMATCH))
    return (NOERROR);

  hDB = *((DBHANDLE far *)phDB);
  
  if (error = NSFNoteOpen(hDB, SearchMatch.ID.NoteID, 0, &hNote))
  {
    printf("NSFNoteOpen failed...\n");
    return (ERR(error));
  }
    
  /*
   * Find the first $OLEOBJINFO item
   */

  if (error = NSFItemInfo(hNote,
                          OLE_OBJECT_ITEM,
                          (WORD)strlen(OLE_OBJECT_ITEM),
                          NULL,
                          &wDataType,
                          &bidValue,
                          &dwValueLen))
  {
    NSFNoteClose(hNote);
    printf("NSFItemInfo failed...\n");
    return (ERR(error));
  }

  if (wDataType != TYPE_COMPOSITE)
  {
    printf("$OLEOBJINFO item is not Rich Text...\n");
    return (NOERROR);
  }
    
  EnumCompositeBuffer(bidValue, dwValueLen, ProcessOneCDRecord, &hNote);

  NSFNoteClose(hNote);

  return (ERR(error));

}


/************************************************************************

    FUNCTION:   ProcessOneCDRecord

    PURPOSE:    Action routine called for each embedded OLE2 object.
	            Extracts OLE2 object to Structured Storage file.

*************************************************************************/

STATUS LNPUBLIC ProcessOneCDRecord(
  char far *pRecord,
  WORD wRecordType,
  DWORD dwRecordLength,
  void far *phNote)
{   

  char far *pData = pRecord;
  NOTEHANDLE hNote;
  CDOLEOBJ_INFO cdOleObjInfo;
  ENCRYPTION_KEY EncryptKey;
  ENCRYPTION_KEY *pEncryptKey;
  char szFileName[MAXPATH];
  char szObjectName[MAXPATH];
  STATUS error = NOERROR;

  LPMALLOC lpMalloc    = NULL;
  LPSTORAGE lpRootStg  = NULL;
  LPSTORAGE lpSubStg   = NULL;
  LPSTREAM lpStream    = NULL;
	WCHAR wcsStgFile[MAXPATH_OLE];
  WCHAR wcsStream[]    = L"Contents";
  LPOLESTR lpProgID;
  DWORD dwMode         = STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
  char szProgID[MAXPATH_OLE];
  char szContents[1024];
  ULONG cbRead;

  if (wRecordType != SIG_CD_OLEOBJINFO)
    goto exit1;

  ODSReadMemory(&pData, _CDOLEOBJ_INFO, &cdOleObjInfo, 1);

  strncpy(szObjectName, pData, cdOleObjInfo.FileObjNameLength);
  szObjectName[cdOleObjInfo.FileObjNameLength] = '\0';

  strcpy(szFileName, szObjectName);
  strcat(szFileName, ".OLE");

  hNote = *((NOTEHANDLE far *)phNote);

  error = NSFNoteDecrypt(hNote, 0, &EncryptKey);
  if(error)
  {
    if(ERR(error) == ERR_NOTE_NOT_SEALED)
      pEncryptKey = NULL;
    else
    {
      printf("NSFNoteDecrypt failed...\n");
      goto exit1;
    }
  }

  if (error = NSFNoteExtractOLE2Object(hNote,
                                       szObjectName,
                                       szFileName,
                                       pEncryptKey,
                                       TRUE,
                                       0))
  {
    printf("NSFNoteExtractOLE2Object failed...\n");
    goto exit1;
  }

  printf("Extracted OLE object to file %s\n",szFileName);

  /* Initialize OLE */

  if (HIWORD(OleBuildVersion()) != rmm)
    goto exit1;

  if (FAILED(OleInitialize(NULL)))
    goto exit1;
   
  /* Obtain OLE allocator */

  CoGetMalloc(MEMCTX_TASK, &lpMalloc);

  /* Open storage */

  if (!MultiByteToWideChar(CP_ACP,0,szFileName,-1,wcsStgFile,MAXPATH_OLE))
    goto exit2;
  if (FAILED(StgOpenStorage(wcsStgFile,NULL,dwMode,NULL,0,&lpRootStg)))
    goto exit2;
  printf("Opened root storage from file %s\n",szFileName);

  /* Get ProgID */

  if(FAILED(ProgIDFromCLSID((REFCLSID)&cdOleObjInfo.OleObjClass, &lpProgID)))
    goto exit3;
  if(!(WideCharToMultiByte(CP_ACP,0,lpProgID,-1,szProgID,MAXPATH_OLE,NULL,NULL)))
    goto exit3;

  /* Open substorage */

  if(FAILED(lpRootStg->lpVtbl->OpenStorage(lpRootStg,lpProgID,NULL,dwMode,NULL,0,&lpSubStg)))
    goto exit3;
  printf("Opened substorage '%s'\n",szProgID);

  /* Open 'Contents' stream */

  if(FAILED(lpSubStg->lpVtbl->OpenStream(lpSubStg,wcsStream,NULL,dwMode,0,&lpStream)))
  {
    printf("No 'Contents' stream in substorage '%s'\n",szProgID);
    goto exit4;
  }
  printf("Opened 'Contents' stream:\n");

  if(FAILED(lpStream->lpVtbl->Read(lpStream,(void *)szContents,1024,&cbRead)))
    goto exit5;
  else
    printf("%s\n\n",szContents);

exit5:
  lpStream->lpVtbl->Release(lpStream);

exit4:
  lpSubStg->lpVtbl->Release(lpSubStg);

exit3:
  lpRootStg->lpVtbl->Release(lpRootStg);

exit2:
  lpMalloc->lpVtbl->Release(lpMalloc);
  OleUninitialize();

exit1:
  return (ERR(error));

}