
#ifndef ADMINP_DEFS
#define ADMINP_DEFS

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KFM_DEFS
#include "kfm.h"
#endif


/*	Values for "dwDeleteInNABType" field below. */

#define DELETE_PERSON_IN_NAB 1
#define DELETE_SERVER_IN_NAB 2
#define DELETE_GROUP_IN_NAB 3

typedef struct{
	DWORD 		Flags;				/* Reserved */

/* Original 4.x structure ended here.  The following fields were added for V5 */

	DWORD		dwDeleteInNABType;	/* DELETE_xxxx_IN_NAB defined above */
	char far*	chGroupName;		/* if dwDeleteInNABType equals DELETE_PERSON_IN_NAB
										a pointer to a group (termination perhaps) to have
										the name added */
	} ADMINReqParams;

/* When the Administration Process passes parameters to an Addin process
	through an MQueue, the following structure defines the format of the 
	data the Addin process receives */

typedef struct{
	NOTEID RequestNoteId;	/* the note id of the Admin Request note */ 
	NOTEID ResponseNoteId;	/* the note id of the Admin Log note */	
	} AdminpAddInMessage;

STATUS LNPUBLIC ADMINReqDeleteInNAB( DBHANDLE dbhAdmin4,
                                     char far *chAuthor,
                                     char far *chUserName,
                                     char far *chMailServerName,
                                     char far *chMailFileName,
                                     char far *chDeleteMailFile,
									 ADMINReqParams far *arpAdminReqParamsPtr,
									 WORD wAdminReqParamsSize 
                                     );
STATUS LNPUBLIC ADMINReqDeleteInACL( DBHANDLE dbhAdmin4,
                                     char far *chAuthor,
                                     char far *chUserName,
                                     char far *chMailServerName,
                                     char far *chMailFileName,
                                     char far *chDeleteMailFile,
									 ADMINReqParams far* arpAdminReqParamsPtr,
									 WORD wAdminReqParamsSize 
                                     );
STATUS LNPUBLIC ADMINReqChkAccessNewReplica( DBHANDLE dbhAdmin4,
                                             char far *chAuthor,
                                             char far *chSrcServer,
                                             char far *chSrcPathName,
                                             char far *chTitle,
                                             DBREPLICAINFO *Replicainfo,
                                             char far *chDesServer,
                                             char far *chDesPathName,
											 ADMINReqParams far* arpAdminReqParamsPtr,
											 WORD wAdminReqParamsSize 
                                             );
STATUS LNPUBLIC ADMINReqChkAccessMoveReplica( DBHANDLE dbhAdmin4,
                                              char far *chAuthor,
                                              char far *chSrcServer,
                                              char far *chSrcPathName,
                                              char far *chTitle,
                                              DBREPLICAINFO *Replicainfo,
                                              char far *chDesServer,
                                              char far *chDesPathName,
											  ADMINReqParams far* arpAdminReqParamsPtr,
											  WORD wAdminReqParamsSize 
                                              );
STATUS LNPUBLIC ADMINReqRename( HCERTIFIER	hCertCtx,
							                  DBHANDLE	  dbhNab,
							                  NOTEHANDLE	nhNote,
							                  char far    *pFirstName,
							                  char far    *pMiddleInitial,  
							                  char far    *pLastName,
							                  char far    *pOU,
							                  BOOL far    *retfWeLoggedThisEntry,
							                  BOOL far    *retfFatalError,
											  ADMINReqParams far* arpAdminReqParamsPtr,
											  WORD wAdminReqParamsSize 
                                			  );
STATUS LNPUBLIC ADMINReqRecertify( HCERTIFIER	hCertCtx,
							                     DBHANDLE		dbhNab,
							                     NOTEHANDLE	nhNote,
							                     BOOL far   *retfWeLoggedThisEntry,
							                     BOOL far   *retfFatalError,
											  	 ADMINReqParams far* arpAdminReqParamsPtr,
											     WORD wAdminReqParamsSize 
							                     );
STATUS LNPUBLIC ADMINReqMoveUserInHier( HCERTIFIER	hCertCtx,
							                          DBHANDLE	  dbhNab,
							                          NOTEHANDLE	nhNote,
							                          char far    *pTargetCert,
							                          BOOL far    *retfWeLoggedThisEntry,
							                          BOOL far    *retfFatalError, 
											  	 	  ADMINReqParams far* arpAdminReqParamsPtr,
											          WORD wAdminReqParamsSize 
							                          );
STATUS LNPUBLIC ADMINReqMoveComplete( HCERTIFIER	hCertCtx,
								                      DBHANDLE 		dbhAdmin4,
								                      NOTEHANDLE	nhAdminReq,
								                      char far	  *pTargetCert,
								                      BOOL far    *retfWeLoggedThisEntry,
								                      BOOL far    *retfFatalError,
											  	 	  ADMINReqParams far* arpAdminReqParamsPtr,
											          WORD wAdminReqParamsSize 
								                      );

#ifdef __cplusplus
}

#endif

#endif	/*	ADMINP_DEFS	*/





