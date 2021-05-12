/*
  
  PROGRAM:    extmngr.dll
  
  FILE:       extmngr.c
  
  Extension Manager Lotus C API for Domino and Notes Example Program
  
  OVERVIEW:
  This sample program registers and deregisters all of the Extension Manager functions to 
  show how they interact in an application.  It also transforms a non Domino database "animals.db"
  into a Domino database "animals.nsf" when specific extension manager hooks are called.
  
  The sample attempts to register a callback function for a selected set of Domino and Notes 
  extension manager hooks.  When the program traps an EM_NSFDBCREATE and EM_NSFDBCLOSE 
  hook for the Database "animals.nsf", the data in the database is built from an 
  existing file "animals.db" containing information and transformed into a Domino Database. The
  extension manager hooks are deregistered when Domino and Notes is exited.  The log file 
  OUTPUT.LOG, tracks extension manager calls and is created in the Domino and Notes Data directory.
  
*/


#if defined(MAC)
#include "Errors.h"
#include "Aliases.h"
#include "TextUtils.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*
 *  Domino and Notes header files
 */
#include <lapicinc.h> 
#include <global.h>
#include <ixport.h>
#include <dbdrv.h>
#include <dbdrverr.h>
#include <osmem.h>
#include <nsfdata.h>
#include <names.h>
#include <osfile.h>
#include <lapiplat.h>
#include <nif.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <editods.h>
#include <stdnames.h>
#include <nsfsearc.h>
#include <colorid.h>
#include <miscerr.h>
#include <actods.h>
#include <nifcoll.h>
#include <osmisc.h>
#include <viewfmt.h>

#include "extmngr.h"

/*===== GLOBAL VARIABLES =============================*/

EMHANDLER   gHandlerProc;
char        gTextBuffer[1024];
char        DataDir[256];
char        FileName[256];
BOOL        gHooksRegistered=FALSE;
WORD        gRecursionID;
DBRECORD    *pDBRecord;  /* Global record pointer                 */

#if defined(NT) || defined(OS2_2x)
FILE         *gFStream = (__FILE *)0;

#elif defined(MAC)
short        grefNum;
short        *gFStream;
OSErr        gFileError;

#endif

#if defined(NT)
/* Storage needed for synchronization under Windows NT */
CRITICAL_SECTION    gCriticalSection;
#endif

TExtensionInfo  ExtensionHookTable[] = {
  {EM_NSFDBCLOSESESSION, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBCLOSESESSION"},
  {EM_NSFDBCLOSE, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBCLOSE"},
  {EM_NSFDBCREATE, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBCREATE"},
  {EM_NSFDBDELETE, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBDELETE"},
  {EM_NSFNOTEOPEN, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTEOPEN"},
  {EM_NSFNOTECLOSE, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTECLOSE"},
  {EM_NSFNOTECREATE, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTECREATE"},
  {EM_NSFNOTEDELETE, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTEDELETE"},
  {EM_NSFNOTEOPENBYUNID, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTEOPENBYUNID"},
  {EM_FTGETLASTINDEXTIME, EM_REG_BEFORE, 0, FALSE, "EM_FTGETLASTINDEXTIME"},
  {EM_FTINDEX, EM_REG_BEFORE, 0, FALSE, "EM_FTINDEX"},
  {EM_FTSEARCH, EM_REG_BEFORE, 0, FALSE, "EM_FTSEARCH"},
  {EM_NIFFINDBYKEY, EM_REG_BEFORE, 0, FALSE, "EM_NIFFINDBYKEY"},
  {EM_NIFFINDBYNAME, EM_REG_BEFORE, 0, FALSE, "EM_NIFFINDBYNAME"},
  {EM_NIFREADENTRIES, EM_REG_BEFORE, 0, FALSE, "EM_NIFREADENTRIES"},
  {EM_NIFUPDATECOLLECTION, EM_REG_BEFORE, 0, FALSE, "EM_NIFUPDATECOLLECTION"},
  {EM_NSFDBALLOCOBJECT, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBALLOCOBJECT"},
  {EM_NSFDBCOMPACT, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBCOMPACT"},
  {EM_NSFDBDELETENOTES, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBDELETENOTES"},
  {EM_NSFDBFREEOBJECT, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBFREEOBJECT"},
  {EM_NSFDBGETMODIFIEDNOTETABLE, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBGETMODIFIEDNOTETABLE"},
  {EM_NSFDBGETNOTEINFO, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBGETNOTEINFO"},
  {EM_NSFDBGETNOTEINFOBYUNID, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBGETNOTEINFOBYUNID"},
  {EM_NSFDBGETOBJECTSIZE, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBGETOBJECTSIZE"},
  {EM_NSFDBGETSPECIALNOTEID, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBGETSPECIALNOTEID"},
  {EM_NSFDBINFOGET, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBINFOGET"},
  {EM_NSFDBINFOSET, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBINFOSET"},
  {EM_NSFDBLOCATEBYREPLICAID, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBLOCATEBYREPLICAID"},
  {EM_NSFDBMODIFIEDTIME, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBMODIFIEDTIME"},
  {EM_NSFDBREADOBJECT, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBREADOBJECT"},
  {EM_NSFDBREALLOCOBJECT, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBREALLOCOBJECT"},
  {EM_NSFDBREPLICAINFOGET, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBREPLICAINFOGET"},
  {EM_NSFDBREPLICAINFOSET, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBREPLICAINFOSET"},
  {EM_NSFDBSPACEUSAGE, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBSPACEUSAGE"},
  {EM_NSFDBSTAMPNOTES, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBSTAMPNOTES"},
  {EM_NSFDBWRITEOBJECT, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBWRITEOBJECT"},
  {EM_NSFNOTEUPDATE, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTEUPDATE"},
  {EM_NIFOPENCOLLECTION, EM_REG_BEFORE, 0, FALSE, "EM_NIFOPENCOLLECTION"},
  {EM_NIFCLOSECOLLECTION, EM_REG_BEFORE, 0, FALSE, "EM_NIFCLOSECOLLECTION"},
  {EM_NSFDBGETBUILDVERSION, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBGETBUILDVERSION"},
  {EM_NSFDBITEMDEFTABLE, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBITEMDEFTABLE"},
  {EM_NSFDBREOPEN, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBREOPEN"},
  {EM_NSFDBOPENEXTENDED, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBOPENEXTENDED"},
  {EM_NSFNOTEDECRYPT, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTEDECRYPT"},
  {EM_GETPASSWORD, EM_REG_BEFORE, 0, FALSE, "EM_GETPASSWORD"},
  {EM_SETPASSWORD, EM_REG_BEFORE, 0, FALSE, "EM_SETPASSWORD"},
  {EM_CLEARPASSWORD, EM_REG_BEFORE, 0, FALSE, "EM_CLEARPASSWORD"},
  {EM_NSFCONFLICTHANDLER, EM_REG_BEFORE, 0, FALSE, "EM_NSFCONFLICTHANDLER"},
  {EM_NSFNOTEUPDATEXTENDED, EM_REG_BEFORE, 0, FALSE, "NSFNOTEUPDATEXTENDED"},
  {EM_SCHFREETIMESEARCH, EM_REG_BEFORE, 0, FALSE, "SCHFREETIMESEARCH"},
  {EM_SCHRETRIEVE, EM_REG_BEFORE, 0, FALSE, "SCHRETRIEVE"},
  {EM_SCHSRVRETRIEVE, EM_REG_BEFORE, 0, FALSE, "SCHSRVRETRIEVE"},
  {EM_ADMINPPROCESSREQUEST, EM_REG_BEFORE, 0, FALSE, "EM_ADMINPPROCESSREQUEST"},
  {EM_NIFGETCOLLECTIONDATA, EM_REG_BEFORE, 0, FALSE, "NIFGETCOLLECTIONDATA"},
  {EM_NSFDBCOPYNOTE, EM_REG_BEFORE, 0, FALSE, "NSFDBCOPYNOTE"},
  {EM_NSFNOTECOPY, EM_REG_BEFORE, 0, FALSE, "NSFNOTECOPY"},
  {EM_NSFNOTEATTACHFILE, EM_REG_BEFORE, 0, FALSE, "NSFNOTEATTACHFILE"},
  {EM_NSFNOTEDETACHFILE, EM_REG_BEFORE, 0, FALSE, "NSFNOTEDETACHFILE"},
  {EM_NSFNOTEEXTRACTFILE, EM_REG_BEFORE, 0, FALSE, "NSFNOTEEXTRACTFILE"},
  {EM_NSFNOTEATTACHOLE2OBJECT, EM_REG_BEFORE, 0, FALSE, "NSFNOTEATTACHOLE2OBJECT"},
  {EM_NSFNOTEDELETEOLE2OBJECT, EM_REG_BEFORE, 0, FALSE, "NSFNOTEDELETEOLE2OBJECT"},
  {EM_NSFNOTEEXTRACTOLE2OBJECT, EM_REG_BEFORE, 0, FALSE, "NSFNOTEEXTRACTOLE2OBJECT"},
  {EM_NSGETSERVERLIST, EM_REG_BEFORE, 0, FALSE, "NSGETSERVERLIST"},
  {EM_NSFDBCOPY, EM_REG_BEFORE, 0, FALSE, "NSFDBCOPY"},
  {EM_NSFDBCREATEANDCOPY, EM_REG_BEFORE, 0, FALSE, "NSFDBCREATEANDCOPY"},
  {EM_NSFDBCOPYACL, EM_REG_BEFORE, 0, FALSE, "NSFDBCOPYACL"},
  {EM_NSFDBCOPYTEMPLATEACL, EM_REG_BEFORE, 0, FALSE, "NSFDBCOPYTEMPLATEACL"},
  {EM_NSFDBCREATEACLFROMTEMPLATE, EM_REG_BEFORE, 0, FALSE, "NSFDBCREATEACLFROMTEMPLATE"},
  {EM_NSFDBREADACL, EM_REG_BEFORE, 0, FALSE, "NSFDBREADACL"},
  {EM_NSFDBSTOREACL, EM_REG_BEFORE, 0, FALSE, "NSFDBSTOREACL"},
  {EM_NSFDBFILTER, EM_REG_BEFORE, 0, FALSE, "NSFDBFILTER"},
  {EM_FTDELETEINDEX, EM_REG_BEFORE, 0, FALSE, "FTDELETEINDEX"},
  {EM_NSFNOTEGETINFO, EM_REG_BEFORE, 0, FALSE, "NSFNOTEGETINFO"},
  {EM_NSFNOTESETINFO, EM_REG_BEFORE, 0, FALSE, "NSFNOTESETINFO"},
  {EM_NSFNOTECOMPUTEWITHFORM, EM_REG_BEFORE, 0, FALSE, "NSFNOTECOMPUTEWITHFORM"},
  {EM_NIFFINDDESIGNNOTE, EM_REG_BEFORE, 0, FALSE, "NIFFINDDESIGNNOTE"},
  {EM_NIFFINDPRIVATEDESIGNNOTE, EM_REG_BEFORE, 0, FALSE, "NIFFINDPRIVATEDESIGNNOTE"},
  {EM_NIFGETLASTMODIFIEDTIME, EM_REG_BEFORE, 0, FALSE, "NIFGETLASTMODIFIEDTIME"},
  {EM_FTSEARCHEXT, EM_REG_BEFORE, 0, FALSE, "FTSEARCHEXT"},
  {EM_NAMELOOKUP, EM_REG_BEFORE, 0, FALSE, "NAMELOOKUP"},
  {EM_NSFNOTEUPDATEMAILBOX, EM_REG_BEFORE, 0, FALSE, "NSFNOTEUPDATEMAILBOX"},
  {EM_NIFFINDDESIGNNOTEEXT, EM_REG_BEFORE, 0, FALSE, "NIFFINDDESIGNNOTEEXT"},
  {EM_AGENTOPEN, EM_REG_BEFORE, 0, FALSE, "AGENTOPEN"},
  {EM_AGENTCLOSE, EM_REG_BEFORE, 0, FALSE, "AGENTCLOSE"},
  {EM_AGENTISENABLED, EM_REG_BEFORE, 0, FALSE, "AGENTISENABLED"},
  {EM_AGENTCREATERUNCONTEXT, EM_REG_BEFORE, 0, FALSE, "AGENTCREATERUNCONTEXT"},
  {EM_AGENTDESTROYRUNCONTEXT, EM_REG_BEFORE, 0, FALSE, "AGENTDESTROYRUNCONTEXT"},
  {EM_AGENTSETDOCUMENTCONTEXT, EM_REG_BEFORE, 0, FALSE, "AGENTSETDOCUMENTCONTEXT"},
  {EM_AGENTSETTIMEEXECUTIONLIMIT, EM_REG_BEFORE, 0, FALSE, "AGENTSETTIMEEXECUTIONLIMIT"},
  {EM_AGENTQUERYSTDOUTBUFFER, EM_REG_BEFORE, 0, FALSE, "AGENTQUERYSTDOUTBUFFER"},
  {EM_AGENTREDIRECTSTDOUT, EM_REG_BEFORE, 0, FALSE, "AGENTREDIRECTSTDOUT"},
  {EM_NAMELOOKUP2, EM_REG_BEFORE, 0, FALSE, "NAMELOOKUP2"},
  {EM_NIFOPENNOTE, EM_REG_BEFORE, 0, FALSE, "NIFOPENNOTE"},
  {EM_NSFNOTEOPENEXTENDED, EM_REG_BEFORE, 0, FALSE, "EM_NSFNOTEOPENEXTENDED"},
  {EM_TERMINATENSF, EM_REG_BEFORE, 0, FALSE, "EM_TERMINATENSF"},
  {EM_MAILSENDNOTE, EM_REG_BEFORE, 0, FALSE, "EM_MAILSENDNOTE"},
  {EM_AGENTRUN, EM_REG_BEFORE, 0, FALSE, "EM_AGENTRUN"},
  {EM_SECAUTHENTICATION, EM_REG_BEFORE, 0, FALSE, "EM_SECAUTHENTICATION"},
  {EM_NSFMARKREAD, EM_REG_BEFORE, 0, FALSE, "EM_NSFMARKREAD"},
  {EM_NSFADDTOFOLDER, EM_REG_BEFORE, 0, FALSE, "EM_NSFADDTOFOLDER"},
  {EM_NSFDBSPACEUSAGESCALED, EM_REG_BEFORE, 0, FALSE, "EM_NSFDBSPACEUSAGESCALED"},


/*            Here down is all EM_REG_AFTER                     */


  {EM_NSFDBCLOSESESSION, EM_REG_AFTER, 0, FALSE, "EM_NSFDBCLOSESESSION"},
  {EM_NSFDBCLOSE, EM_REG_AFTER, 0, FALSE, "EM_NSFDBCLOSE"},
  {EM_NSFDBCREATE, EM_REG_AFTER, 0, FALSE, "EM_NSFDBCREATE"},
  {EM_NSFDBDELETE, EM_REG_AFTER, 0, FALSE, "EM_NSFDBDELETE"},
  {EM_NSFNOTEOPEN, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTEOPEN"},
  {EM_NSFNOTECLOSE, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTECLOSE"},
  {EM_NSFNOTECREATE, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTECREATE"},
  {EM_NSFNOTEDELETE, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTEDELETE"},
  {EM_NSFNOTEOPENBYUNID, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTEOPENBYUNID"},
  {EM_FTGETLASTINDEXTIME, EM_REG_AFTER, 0, FALSE, "EM_FTGETLASTINDEXTIME"},
  {EM_FTINDEX, EM_REG_AFTER, 0, FALSE, "EM_FTINDEX"},
  {EM_FTSEARCH, EM_REG_AFTER, 0, FALSE, "EM_FTSEARCH"},
  {EM_NIFFINDBYKEY, EM_REG_AFTER, 0, FALSE, "EM_NIFFINDBYKEY"},
  {EM_NIFFINDBYNAME, EM_REG_AFTER, 0, FALSE, "EM_NIFFINDBYNAME"},
  {EM_NIFREADENTRIES, EM_REG_AFTER, 0, FALSE, "EM_NIFREADENTRIES"},
  {EM_NIFUPDATECOLLECTION, EM_REG_AFTER, 0, FALSE, "EM_NIFUPDATECOLLECTION"},
  {EM_NSFDBALLOCOBJECT, EM_REG_AFTER, 0, FALSE, "EM_NSFDBALLOCOBJECT"},
  {EM_NSFDBCOMPACT, EM_REG_AFTER, 0, FALSE, "EM_NSFDBCOMPACT"},
  {EM_NSFDBDELETENOTES, EM_REG_AFTER, 0, FALSE, "EM_NSFDBDELETENOTES"},
  {EM_NSFDBFREEOBJECT, EM_REG_AFTER, 0, FALSE, "EM_NSFDBFREEOBJECT"},
  {EM_NSFDBGETMODIFIEDNOTETABLE, EM_REG_AFTER, 0, FALSE, "EM_NSFDBGETMODIFIEDNOTETABLE"},
  {EM_NSFDBGETNOTEINFO, EM_REG_AFTER, 0, FALSE, "EM_NSFDBGETNOTEINFO"},
  {EM_NSFDBGETNOTEINFOBYUNID, EM_REG_AFTER, 0, FALSE, "EM_NSFDBGETNOTEINFOBYUNID"},
  {EM_NSFDBGETOBJECTSIZE, EM_REG_AFTER, 0, FALSE, "EM_NSFDBGETOBJECTSIZE"},
  {EM_NSFDBGETSPECIALNOTEID, EM_REG_AFTER, 0, FALSE, "EM_NSFDBGETSPECIALNOTEID"},
  {EM_NSFDBINFOGET, EM_REG_AFTER, 0, FALSE, "EM_NSFDBINFOGET"},
  {EM_NSFDBINFOSET, EM_REG_AFTER, 0, FALSE, "EM_NSFDBINFOSET"},
  {EM_NSFDBLOCATEBYREPLICAID, EM_REG_AFTER, 0, FALSE, "EM_NSFDBLOCATEBYREPLICAID"},
  {EM_NSFDBMODIFIEDTIME, EM_REG_AFTER, 0, FALSE, "EM_NSFDBMODIFIEDTIME"},
  {EM_NSFDBREADOBJECT, EM_REG_AFTER, 0, FALSE, "EM_NSFDBREADOBJECT"},
  {EM_NSFDBREALLOCOBJECT, EM_REG_AFTER, 0, FALSE, "EM_NSFDBREALLOCOBJECT"},
  {EM_NSFDBREPLICAINFOGET, EM_REG_AFTER, 0, FALSE, "EM_NSFDBREPLICAINFOGET"},
  {EM_NSFDBREPLICAINFOSET, EM_REG_AFTER, 0, FALSE, "EM_NSFDBREPLICAINFOSET"},
  {EM_NSFDBSPACEUSAGE, EM_REG_AFTER, 0, FALSE, "EM_NSFDBSPACEUSAGE"},
  {EM_NSFDBSTAMPNOTES, EM_REG_AFTER, 0, FALSE, "EM_NSFDBSTAMPNOTES"},
  {EM_NSFDBWRITEOBJECT, EM_REG_AFTER, 0, FALSE, "EM_NSFDBWRITEOBJECT"},
  {EM_NSFNOTEUPDATE, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTEUPDATE"},
  {EM_NIFOPENCOLLECTION, EM_REG_AFTER, 0, FALSE, "EM_NIFOPENCOLLECTION"},
  {EM_NIFCLOSECOLLECTION, EM_REG_AFTER, 0, FALSE, "EM_NIFCLOSECOLLECTION"},
  {EM_NSFDBGETBUILDVERSION, EM_REG_AFTER, 0, FALSE, "EM_NSFDBGETBUILDVERSION"},
  {EM_NSFDBITEMDEFTABLE, EM_REG_AFTER, 0, FALSE, "EM_NSFDBITEMDEFTABLE"},
  {EM_NSFDBREOPEN, EM_REG_AFTER, 0, FALSE, "EM_NSFDBREOPEN"},
  {EM_NSFDBOPENEXTENDED, EM_REG_AFTER, 0, FALSE, "EM_NSFDBOPENEXTENDED"},
  {EM_NSFNOTEDECRYPT, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTEDECRYPT"},
  {EM_NSFCONFLICTHANDLER, EM_REG_AFTER, 0, FALSE, "EM_NSFCONFLICTHANDLER"},
  {EM_NSFNOTEUPDATEXTENDED, EM_REG_AFTER, 0, FALSE, "NSFNOTEUPDATEXTENDED"},
  {EM_SCHFREETIMESEARCH, EM_REG_AFTER, 0, FALSE, "SCHFREETIMESEARCH"},
  {EM_SCHRETRIEVE, EM_REG_AFTER, 0, FALSE, "SCHRETRIEVE"},
  {EM_SCHSRVRETRIEVE, EM_REG_AFTER, 0, FALSE, "SCHSRVRETRIEVE"},
  {EM_ADMINPPROCESSREQUEST, EM_REG_AFTER, 0, FALSE, "EM_ADMINPPROCESSREQUEST"},
  {EM_NIFGETCOLLECTIONDATA, EM_REG_AFTER, 0, FALSE, "NIFGETCOLLECTIONDATA"},
  {EM_NSFDBCOPYNOTE, EM_REG_AFTER, 0, FALSE, "NSFDBCOPYNOTE"},
  {EM_NSFNOTECOPY, EM_REG_AFTER, 0, FALSE, "NSFNOTECOPY"},
  {EM_NSFNOTEATTACHFILE, EM_REG_AFTER, 0, FALSE, "NSFNOTEATTACHFILE"},
  {EM_NSFNOTEDETACHFILE, EM_REG_AFTER, 0, FALSE, "NSFNOTEDETACHFILE"},
  {EM_NSFNOTEEXTRACTFILE, EM_REG_AFTER, 0, FALSE, "NSFNOTEEXTRACTFILE"},
  {EM_NSFNOTEATTACHOLE2OBJECT, EM_REG_AFTER, 0, FALSE, "NSFNOTEATTACHOLE2OBJECT"},
  {EM_NSFNOTEDELETEOLE2OBJECT, EM_REG_AFTER, 0, FALSE, "NSFNOTEDELETEOLE2OBJECT"},
  {EM_NSFNOTEEXTRACTOLE2OBJECT, EM_REG_AFTER, 0, FALSE, "NSFNOTEEXTRACTOLE2OBJECT"},
  {EM_NSGETSERVERLIST, EM_REG_AFTER, 0, FALSE, "NSGETSERVERLIST"},
  {EM_NSFDBCOPY, EM_REG_AFTER, 0, FALSE, "NSFDBCOPY"},
  {EM_NSFDBCREATEANDCOPY, EM_REG_AFTER, 0, FALSE, "NSFDBCREATEANDCOPY"},
  {EM_NSFDBCOPYACL, EM_REG_AFTER, 0, FALSE, "NSFDBCOPYACL"},
  {EM_NSFDBCOPYTEMPLATEACL, EM_REG_AFTER, 0, FALSE, "NSFDBCOPYTEMPLATEACL"},
  {EM_NSFDBCREATEACLFROMTEMPLATE, EM_REG_AFTER, 0, FALSE, "NSFDBCREATEACLFROMTEMPLATE"},
  {EM_NSFDBREADACL, EM_REG_AFTER, 0, FALSE, "NSFDBREADACL"},
  {EM_NSFDBSTOREACL, EM_REG_AFTER, 0, FALSE, "NSFDBSTOREACL"},
  {EM_NSFDBFILTER, EM_REG_AFTER, 0, FALSE, "NSFDBFILTER"},
  {EM_FTDELETEINDEX, EM_REG_AFTER, 0, FALSE, "FTDELETEINDEX"},
  {EM_NSFNOTEGETINFO, EM_REG_AFTER, 0, FALSE, "NSFNOTEGETINFO"},
  {EM_NSFNOTESETINFO, EM_REG_AFTER, 0, FALSE, "NSFNOTESETINFO"},
  {EM_NSFNOTECOMPUTEWITHFORM, EM_REG_AFTER, 0, FALSE, "NSFNOTECOMPUTEWITHFORM"},
  {EM_NIFFINDDESIGNNOTE, EM_REG_AFTER, 0, FALSE, "NIFFINDDESIGNNOTE"},
  {EM_NIFFINDPRIVATEDESIGNNOTE, EM_REG_AFTER, 0, FALSE, "NIFFINDPRIVATEDESIGNNOTE"},
  {EM_NIFGETLASTMODIFIEDTIME, EM_REG_AFTER, 0, FALSE, "NIFGETLASTMODIFIEDTIME"},
  {EM_FTSEARCHEXT, EM_REG_AFTER, 0, FALSE, "FTSEARCHEXT"},
  {EM_NAMELOOKUP, EM_REG_AFTER, 0, FALSE, "NAMELOOKUP"},
  {EM_NSFNOTEUPDATEMAILBOX, EM_REG_AFTER, 0, FALSE, "NSFNOTEUPDATEMAILBOX"},
  {EM_NIFFINDDESIGNNOTEEXT, EM_REG_AFTER, 0, FALSE, "NIFFINDDESIGNNOTEEXT"},
  {EM_AGENTOPEN, EM_REG_AFTER, 0, FALSE, "AGENTOPEN"},
  {EM_AGENTCLOSE, EM_REG_AFTER, 0, FALSE, "AGENTCLOSE"},
  {EM_AGENTISENABLED, EM_REG_AFTER, 0, FALSE, "AGENTISENABLED"},
  {EM_AGENTCREATERUNCONTEXT, EM_REG_AFTER, 0, FALSE, "AGENTCREATERUNCONTEXT"},
  {EM_AGENTDESTROYRUNCONTEXT, EM_REG_AFTER, 0, FALSE, "AGENTDESTROYRUNCONTEXT"},
  {EM_AGENTSETDOCUMENTCONTEXT, EM_REG_AFTER, 0, FALSE, "AGENTSETDOCUMENTCONTEXT"},
  {EM_AGENTSETTIMEEXECUTIONLIMIT, EM_REG_AFTER, 0, FALSE, "AGENTSETTIMEEXECUTIONLIMIT"},
  {EM_AGENTQUERYSTDOUTBUFFER, EM_REG_AFTER, 0, FALSE, "AGENTQUERYSTDOUTBUFFER"},
  {EM_AGENTREDIRECTSTDOUT, EM_REG_AFTER, 0, FALSE, "AGENTREDIRECTSTDOUT"},
  {EM_NAMELOOKUP2, EM_REG_AFTER, 0, FALSE, "NAMELOOKUP2"},
  {EM_NIFOPENNOTE, EM_REG_AFTER, 0, FALSE, "NIFOPENNOTE"},
  {EM_NSFNOTEOPENEXTENDED, EM_REG_AFTER, 0, FALSE, "EM_NSFNOTEOPENEXTENDED"},
  {EM_TERMINATENSF, EM_REG_AFTER, 0, FALSE, "EM_TERMINATENSF"},
  {EM_MAILSENDNOTE, EM_REG_AFTER, 0, FALSE, "EM_MAILSENDNOTE"},
  {EM_AGENTRUN, EM_REG_AFTER, 0, FALSE, "EM_AGENTRUN"},
  {EM_SECAUTHENTICATION, EM_REG_AFTER, 0, FALSE, "EM_SECAUTHENTICATION"},
  {EM_NSFMARKREAD, EM_REG_AFTER, 0, FALSE, "EM_NSFMARKREAD"},
  {EM_NSFADDTOFOLDER, EM_REG_AFTER, 0, FALSE, "EM_NSFADDTOFOLDER"},
  {EM_NSFDBSPACEUSAGESCALED, EM_REG_AFTER, 0, FALSE, "EM_NSFDBSPACEUSAGESCALED"},

  {0,  0,  0, 0, NULL}
};
/************************* End of ExtensionHookTable ************************
*****************************************************************************/


/*===== LOCAL FUNCTION PROTOTYES ======================================*/

STATUS LNPUBLIC DLL_EXPORT MainEntryPoint( void );

#if defined (NT)

BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD fdwReason,
		     LPVOID lpReserved );

#elif defined(MAC)
/*
  Prototypes for file i/o functions that are mac specific because 
  the standard C fopen and fclose do not work under shared libraries.
  these functions have been written such that they perform the same
  functionality as the standard C functions.
*/
OSErr FSpLocationFromFullPath(short fullPathLength,
				     const void *fullPath,
				     FSSpec *spec);
#endif

STATUS LNPUBLIC DLL_EXPORT EMHandlerProc( EMRECORD FAR * pExRecord);
void CleanUp( void );
STATUS GetDBTitle(DBHANDLE hDb, char *title);

/*
* LogLine: Attempts to write a line to the output.log
*
*   in: Line => The Line to log
*
*   out: If gFStream is not NULL an attempt will be made to
*        ship out the line. If that fails gFStream will
*        be dropped.
*/
void LogLine(char *Line)
{
    if (gFStream) {
	      __WriteLine(Line, gFStream);
	      if (__FileError(gFStream)) {
		 __CloseFile(gFStream);
		 gFStream = (__FILE *)0;
	      }
    }
}

/*
* RegisterEntry: Attempts to Register one entry.
*
*   in: x = Offset into table
*
*   out: 0 if ok, returned error otherwise
*/
STATUS RegisterEntry(int x)
{
    STATUS error = NOERROR;

    if (ExtensionHookTable[x].m_Name == NULL) return(error);

    LogLine("-------------------------------------------------\n");

    sprintf(gTextBuffer, "Calling EMRegister with %s\n",
    ExtensionHookTable[x].m_Name); 
    LogLine( gTextBuffer );

    error = EMRegister( ExtensionHookTable[x].m_Identifier,
	    ExtensionHookTable[x].m_Notification,
	    (EMHANDLER)gHandlerProc, 
	    gRecursionID,
	    &ExtensionHookTable[x].m_RegistrationHandle);

    if (error) {
		LogLine("EMRegister Failed\n");
		if (gFStream) __CloseFile(gFStream);
		gFStream = (__FILE *)0;
		return(error);
    }
    LogLine("-------------------------------------------------\n");

    return(error);
}

/*
* DeregisterEntry: Attempts to Deregister one entry.
*
*   in: x = Offset into table
*
*   out: 0 if ok, returned error otherwise
*/
STATUS DeregisterEntry(int x)
{
    STATUS error = NOERROR;

    if (ExtensionHookTable[x].m_Name == NULL) return(error);

    gFStream = __OpenFile( FileName, APPEND_PERMISSION );

    LogLine("-------------------------------------------------\n");

    sprintf(gTextBuffer, "Calling EMDeregister with %s\n",
	    ExtensionHookTable[x].m_Name); 
    LogLine( gTextBuffer );

    error = EMDeregister(ExtensionHookTable[x].m_RegistrationHandle);

    if (error) {
		LogLine("EMDregister Failed\n");
		if (gFStream) __CloseFile(gFStream);
		gFStream = (__FILE *)0;
		return(error);
    }
    LogLine("-------------------------------------------------\n");
    __CloseFile(gFStream);

    return(error);
}

STATUS LNPUBLIC DLL_EXPORT MainEntryPoint( void )
{
    STATUS    error;
    WORD      x;

    error = NOERROR;

	
/* 
*    When run on a server the dll is called multiple times. the flag 
*    keeps the main code from being executed more than once. 
*/
    if ( gHooksRegistered )
	 return(NOERROR);
	gHooksRegistered = TRUE; 

	
/* Open log __FILE for DLL. */

    x = OSGetDataDirectory(FileName);
    strcpy(DataDir,FileName);

    strcat(FileName, LOG_FILE_NAME);

    gFStream = __OpenFile( FileName, WRITE_PERMISSION );

/* Get proc instance for the handler callback. */
#if defined (NT)
/* Done in the DllMain function at startup. */
#else
gHandlerProc = EMHandlerProc;
#endif

/*  Next get a recursion ID  for the run */

    LogLine("-------------------------------------------------\n");
    LogLine("Calling EMCreateRecursionID\n");
   
    error = EMCreateRecursionID( &gRecursionID );

    if (error)
      LogLine("EMCreateRecursionID Failed\n");
       
/* Loop through the table testing each entry */

    else {
	   LogLine("EMCreateRecursionID Returned Success\n");

	 for ( x = 0; ExtensionHookTable[x].m_Name != NULL; x += 1 ) {
	       error = RegisterEntry(x);
	       if (error)
		 break;
	     }
	 }
    if ( gFStream ) {
		     __CloseFile(gFStream);
		     gFStream = (__FILE *)0;
    }
    return( error );
}

/*==========================================================================*/
  
STATUS LNPUBLIC EMHandlerProc( EMRECORD FAR * pExRecord )
{ 

    STATUS error = 0;
    DBRECORD *pDBHead=0;
    DBRECORD *pDBNext=0;
    static int inHook=0;
    static int inHookNoteClose=0;

    switch (pExRecord->EId)
    {
	case EM_NSFDBCREATE:
	{
	    char far *DBName;
	    USHORT DbClass;
	    BOOL Force;
	    VARARG_PTR ap;

	    char PathName[256];

	    /* get arguments */
	    ap = pExRecord->Ap;
	    DBName = VARARG_GET (ap, char far *);
	    DbClass = VARARG_GET (ap, USHORT);
	    Force = VARARG_GET (ap, BOOL);

        /* check error code */
	    if (pExRecord->Status != NOERROR)
		  break;

	    if (pExRecord->NotificationType != EM_AFTER)
		  break;

	    /* construct database path name */
	    strcpy(PathName,DataDir);

#if !defined(MAC)
	    strcat(PathName,"\\");
#else
	    strcat(PathName,":");
#endif
	    strcat(PathName,"animals.nsf");
 
 		
#if defined(OS2_2x) || defined(_ALPHA_) /* for OS2 and Alpha Servers strip path from database name */
	    strcpy(PathName, "animals.nsf");
#endif
	    
	    /* if this isn't the database we're looking for then break */
	    if (strcmp(DBName, PathName))
	      break;

	    inHook = 0; /* init tracking routine cnt to zero on creation */

	    inHook += 1;

	    gFStream = __OpenFile( FileName, APPEND_PERMISSION );
	    LogLine("-------------------------------------------------\n");

	    sprintf(gTextBuffer, "Calling EM_NSFDBCREATE for Database: %s\n",DBName);
	    LogLine( gTextBuffer );
	    LogLine("-------------------------------------------------\n");
	    __CloseFile(gFStream);

	    /* read the non-Domino database and parse info into records */
	    error = ReadDataBase(&pDBRecord);
	    pDBHead = pDBRecord;

	    if (error)
	    {
	      gFStream = __OpenFile( FileName, APPEND_PERMISSION );
	      sprintf(gTextBuffer, "Read Database Error: %d\n",error);
	      LogLine( gTextBuffer );
	       __CloseFile(gFStream);
	      goto FreeMem;
	    }

	    /* create the Domino and Notes form in the Domino database */
	    error = CreateDBForm(pDBHead);
	    if (error)
	    {
	      gFStream = __OpenFile( FileName, APPEND_PERMISSION );
	      sprintf(gTextBuffer, "Create Database Form Error: %d\n",error);
	      LogLine( gTextBuffer );
	      __CloseFile(gFStream);
	      goto FreeMem;
	    }

	    /* create all the notes from the data records */
	    error = CreateDBNotes(pDBHead);
	    if (error)
	    {
	      gFStream = __OpenFile( FileName, APPEND_PERMISSION );
	      sprintf(gTextBuffer, "Create Database Note Error: %d\n",error);
	      LogLine( gTextBuffer );
	      __CloseFile(gFStream);
	      goto FreeMem;
	    }

	    /* create the view in the Domino database */
	    error = CreateDBView();
	    if (error)
	    {
	      gFStream = __OpenFile( FileName, APPEND_PERMISSION );
	      sprintf(gTextBuffer, "Create Database View Error: %d\n",error);
	      LogLine( gTextBuffer );
	      __CloseFile(gFStream);
	      goto FreeMem;
	    }
FreeMem:
	   
	    /* free up memory */
	    if (pDBHead)
	    {
	      pDBRecord = pDBHead;
	      while (pDBRecord != NULL)
	      {
		pDBNext = pDBRecord->Next;
		__FreeMemory(pDBRecord);
		pDBRecord = pDBNext;
	      }
	      pDBHead = 0;
	    }

	    break;
	}

	/* before the Database is closed, create all forms, notes, and views */
	case EM_NSFDBCLOSE:
	{
	    HANDLE hDb;
	    VARARG_PTR ap;
	    char title [MAXSPRINTF];

	    /* get arguments */
	    ap = pExRecord->Ap;
	    hDb = VARARG_GET(ap,HANDLE);

        /* check error code */
        if (pExRecord->Status != NOERROR)
		  break;

	    if (pExRecord->NotificationType != EM_BEFORE)
		break;

	    /* Only do this for our sample DB */
	    if (error = GetDBTitle (hDb, title))
		  break;

	    if (strcmp(title, "animals"))
	      break;

	    gFStream = __OpenFile( FileName, APPEND_PERMISSION );
	    LogLine("-------------------------------------------------\n");

	    sprintf(gTextBuffer, "Calling EM_NSFDBCLOSE for Database: %s\n",title);
	    LogLine( gTextBuffer );
	    LogLine("-------------------------------------------------\n");
	    __CloseFile(gFStream);

	}
    }

    return( ERR_EM_CONTINUE );
}


/*===========================================================================

   void CleanUp(void)

===========================================================================*/ 
void CleanUp(void)
{
  gHooksRegistered = FALSE;
}


/*===========================================================================

   STATUS GetDBTitle(HANDLE, char *)

===========================================================================*/ 
STATUS GetDBTitle(HANDLE hDb, char *title)
{
  
  STATUS error = NOERROR;
  char dbinfo[NSF_INFO_SIZE];
  char the_title[MAXSPRINTF];

  if (error = NSFDbInfoGet (hDb, dbinfo))
    return(error);

  NSFDbInfoParse(dbinfo, INFOPARSE_TITLE, the_title, sizeof(the_title));
  strcpy(title, &the_title[0]);

  return(error);

}

/*============================================================================
	    M A C I N T O S H  S P E C I F I C  F U N C T I O N S 
============================================================================*/
#if defined(MAC)

/*===========================================================================
  
   __FILE * __OpenFile ( char * fileName, int permission )
    
  OVERVIEW:
  ---------
  opens the file specified using the permission parameter. the function
  assumes that the filename being passed in is NULL terminated CString
  and converts it to a pascal style string. The function will create the
  file if it does not exist already.
  
  on an error condition NULL is returned an the global gFileError is
  set to the ioResult, this is done to simplify portability and the use
  of ferror on other platforms
  
===========================================================================*/ 
__FILE * __OpenFile ( char * fileName, int permission )
{

  FSSpec  theSpec;
  OSErr theErr;  
    
    gFileError = FSpLocationFromFullPath(strlen(fileName), fileName, &theSpec);
 
    if (!gFileError || gFileError == fnfErr)
    {
    
	theErr = FSpCreate(&theSpec, 'nOTE', 'TEXT', smSystemScript);   
	/* if the file already exists or if no error then open it */
	if ( theErr == noErr || theErr == dupFNErr)
	{
	  theErr = FSpOpenDF(&theSpec, permission,  &grefNum);

	}
    
	/* set global file error */
	gFileError = theErr;
    
    }
  
  return(&grefNum);
}



/*===========================================================================
  
   static int __WriteLine( char *lineBuf, __FILE *  pbp)
    
  OVERVIEW:
  ---------
  writes line of text to the file specified in the parameter pbp.
  the text is always appended to the end of the text file. the function
  returns the length of the text that was actually written to the file.
  this function was designed to emulate the functionality of the stdlib
  function fwrite()
  
===========================================================================*/ 
static int __WriteLine( char *lineBuf, __FILE *  pbp)
{
  int   refNum;
  long  count;
  
  refNum = *pbp;
  
  count = strlen(lineBuf);
  
  gFileError = FSWrite( refNum, &count, lineBuf);
  
  
  return((int) count );
} 

int __ReadLine( char *lineBuf, long maxLen, __FILE * pbp  )
{
    IOParam     pb;
    long        len;
    OSErr       rc;

    pb.ioRefNum = *pbp;

    pb.ioPosMode = fsAtMark | 0x80 | (256*EOL);
    /* max line size */
    pb.ioReqCount = maxLen;    
    /* transfer to this address */           
    pb.ioBuffer = lineBuf;                  

	/* read one line */
    rc=PBRead( (ParmBlkPtr)&pb, FALSE );    

	/* end of file reached */
    if (rc==eofErr && pb.ioActCount==0)
      return ( NULL );  

    if ((rc==noErr) || (rc==eofErr)) {
	len = pb.ioActCount;
	/* not a delimited file */
	if (len==maxLen) return(0);    
	/* last line has no EOL */    
	/* convert to ASCIIZ */
	if (lineBuf[len-1] != EOL) len++;   
	  lineBuf[len]=0;                   
    }

    return( (int)lineBuf );
}

OSErr FSpLocationFromFullPath(short fullPathLength,
				     const void *fullPath,
				     FSSpec *spec)
{
    AliasHandle alias;
    OSErr       result;
    Boolean     wasChanged;
    Str32       nullString;

    /* Create a minimal alias from the full pathname */
    nullString[0] = 0; /* null string to indicate no zone or server name */
    result = NewAliasMinimalFromFullPath(fullPathLength, fullPath, nullString, nullString, &alias);
    if ( result == noErr && alias != NULL)
    {
      /* Let the Alias Manager resolve the alias. */
	result = ResolveAlias(NULL, alias, spec, &wasChanged);
	DisposeHandle((Handle)alias); /* Free up memory used */
    }
    return ( result );
}





#endif /*defined(MAC)*/



/* ========================================================= */
/* =================== STARTUP FUNCTIONS =================== */
/* ========================================================= */

#if defined (NT)
/*===========================================================================
  
  Startup and Shutdown Function DllMain for Windows NT
  ---------------------------------------------------- 

   BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD fdwReason, 
						   LPVOID lpReserved )
    
  OVERVIEW:
  ---------
   Standard windows NT DLL entrypoint, does initialzation required to get the
   FARPROC for the Extension Manager callback function.
  
===========================================================================*/ 
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD fdwReason, 
						   LPVOID lpReserved )
{
  int x;
  STATUS error=NOERROR;

  switch(fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      InitializeCriticalSection(&gCriticalSection);

      gHandlerProc = (EMHANDLER)MakeProcInstance((FARPROC)EMHandlerProc,
				hInstance);
      break;

    case DLL_PROCESS_DETACH:
      CleanUp();

      /* Free procedure instance */
      FreeProcInstance( gHandlerProc ); 

      /* Deregister Extension Manager routines */
      for ( x = 0; ExtensionHookTable[x].m_Name != NULL; x += 1 )
      {
	error = DeregisterEntry(x);
	if (error)
	  break;
      }

      DeleteCriticalSection(&gCriticalSection);

      break;
  }

  return( TRUE );

  UNREFERENCED_PARAMETER(lpReserved);
}

#endif


/* ========================================================== */
/* =================== SHUTDOWN FUNCTIONS =================== */
/* ========================================================== */
#if defined (NT)
/* 
   NOTE:
   -----
      SHUTDOWN PROCESSES ARE DONE IN THE DLLMAIN FUNCTION IN NT 
*/
#endif

