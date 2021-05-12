#ifdef __cplusplus
extern "C" {
#endif

#ifndef KFM_DEFS
#define KFM_DEFS


/*	Structure returned by KFMCreatePassword to encode a password securely
	in memory to avoid scavenging. */

typedef struct
	{
	BYTE	Type;				/* Type as shown is "0".  This field is a	*/
								/* hook for future compatibility.			*/
	BYTE	HashedPassword[48];	/* Hashed password							*/
	}
	KFM_PASSWORD;

typedef HANDLE HCERTIFIER;	
#define	NULLHCERTIFIER ((HCERTIFIER)0)

/*	Aliases for public routines 
*/

#ifndef SEMAPHORES
	#define _NOSEMS_OR_BSAFE_INTERNAL_
#endif


#ifdef _NOSEMS_OR_BSAFE_INTERNAL_
#define SECKFMUserInfo				KFMUserInfo
#define SECKFMGetUserName			KFMGetUserName
#define SECKFMGetCertifierCtx		KFMGetCertifierCtx
#define SECKFMFreeCertifierCtx		KFMFreeCertifierCtx
#define SECKFMCreatePassword		KFMCreatePassword
#define SECKFMChangePassword        KFMChangePassword
#define SECKFMSwitchToIDFile       	KFMSwitchToIDFile
#undef _NOSEMS_OR_BSAFE_INTERNAL_
#endif

/*	Function codes for routine SECKFMUserInfo  
*/

#define	KFM_ui_GetUserInfo				 1

/*	Function codes for routine SECKFMGetPublicKey
*/

#define KFM_pubkey_Primary				0
#define KFM_pubkey_International		1

STATUS LNPUBLIC SECKFMUserInfo			(WORD Function, 
										 char far *lpName, 
										 LICENSEID far *lpLicense);
STATUS LNPUBLIC SECKFMGetUserName		(char far *retUserName);

STATUS LNPUBLIC SECKFMSwitchToIDFile 	(char	*pIDFileName
				  				  	 	,char	*pPassword
								  	 	,char	*pUserName
								  	 	,WORD	MaxUserNameLength
									 	,DWORD	ReservedFlags
									 	,void	*pReserved);								

STATUS LNPUBLIC SECKFMGetCertifierCtx   (char far 		  *pCertFile, 
										 KFM_PASSWORD far *pKfmPW,
										 char far		  *pLogFile, 
										 TIMEDATE far	  *pExpDate, 
										 char far		  *retCertName,
										 HCERTIFIER far   *rethKfmCertCtx,
										 BOOL far 		  *retfIsHierarchical, 
										 WORD far 		  *retwFileVersion);

VOID   LNPUBLIC SECKFMFreeCertifierCtx	(HCERTIFIER hKfmCertCtx);

VOID   LNPUBLIC SECKFMCreatePassword	(char far 		  *pPassword
										,KFM_PASSWORD far *retHashedPassword
										);
STATUS LNPUBLIC SECKFMSetCertifierExpiration   (HCERTIFIER hKfmCertCtx,
												TIMEDATE far *pExpirationDate);
STATUS LNPUBLIC SECKFMGetPublicKey		(char far	*pName
										,WORD		Function
										,WORD		Flags
										,HANDLE far *rethPubKey
										);
STATUS LNPUBLIC SECKFMChangePassword    (char far   *pIDFile
										,char far   *pOldPassword
										,char far   *pNewPassword
										);


/*	Constants used to indicate various types of IDs that can be created. */

#define KFM_IDFILE_TYPE_FLAT	0	/* Flat name space (V2 compatible) 		*/
#define KFM_IDFILE_TYPE_STD		1	/* Standard (user/server hierarchical) 	*/
#define	KFM_IDFILE_TYPE_ORG		2	/* Organization certifier 				*/
#define	KFM_IDFILE_TYPE_ORGUNIT	3	/* Organizational unit certifier 		*/
#define	KFM_IDFILE_TYPE_DERIVED 4	/* Derived from certifer context.		*/
									/*  hierarchical => STD					*/
									/*  non-hierarchical => FLAT			*/ 
#define KFM_IDFILE_TYPE_INET	5	/*	Internet certifier.					*/


#endif
#ifdef __cplusplus
}
#endif



