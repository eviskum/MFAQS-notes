#ifdef __cplusplus
extern "C" {
#endif

#ifndef STATS_DEFS
#define STATS_DEFS

#include "misc.h"
#include "names.h"

/*	Cross-package definitions */

#define	STATPKG_OS "OS"
#define	STATPKG_STATS "Stats"
#define	STATPKG_OSMEM "Mem"
#define	STATPKG_OSSEM "Sem"
#define	STATPKG_OSSPIN "Spin"
#define	STATPKG_OSFILE "Disk"
#define	STATPKG_SERVER "Server"
#define	STATPKG_REPLICA "Replica"
#define	STATPKG_MAIL "Mail"
#define	STATPKG_MAILBYDEST "MailByDest"
#define	STATPKG_COMM "Comm"
#define	STATPKG_NSF "Database"
#define	STATPKG_NIF "Database"
#define	STATPKG_TESTNSF "Testnsf"
#define STATPKG_OSIO "IO"
#define STATPKG_NET "NET"
#define STATPKG_OBJSTORE "Object"
#define STATPKG_AGENT "Agent"		/* used by agent manager */
#define STATPKG_WEB "Web"			/* used by Web retriever */
#define STATPKG_CAL	"Calendar"		/* used by schedule manager */
#define STATPKG_SMTP "SMTP"			/* Used by SMTP listener */
#define STATPKG_LDAP "LDAP"			/* Used by the LDAP Server */
#define STATPKG_NNTP "NNTP"			/* Used by the NNTP Server */
#define STATPKG_ICM "ICM"			/* Used by the ICM Server */

#define STATPKG_MONITOR "Monitor"
#define STATPKG_POP3 "POP3"			/* Used by the POP3 Server */

/*	Value type constants */

#define	VT_LONG		0
#define	VT_TEXT		1
#define	VT_TIMEDATE	2
#define	VT_NUMBER	3


/*	Flags for StatUpdate */

#define	ST_UNIQUE		0x0001		/* Statistic is unique */
#define	ST_ADDITIVE		0x0002		/* Add to VT_LONG statistic, don't replace */
#define	ST_RESETABLE	0x0003		/* Statistic is resetable to 0 */

/* Collector Daemon tasks */
#define STAT_REPORT_TASK			1
#define CHECK_ALARM_TASK			2
#define GET_STAT_TASK				3
#define STAT_MONITOR_TASK			4
#define INTERVAL_MONITOR_ADD_SRV	5
#define INTERVAL_MONITOR_DEL_SRV	6
#define GET_TASK_STATUS_TASK		7
#define STAT_REMOTE_MONITOR_TASK	8

/* Server task masks */
#define TASK_CHRONOS		0x00000001
#define TASK_DB_COMPACT		0x00000002
#define TASK_ADMIN_PROC		0x00000004
#define TASK_AGENT_MGR		0x00000008
#define TASK_BILLING		0x00000010
#define TASK_CALENDAR_CONN	0x00000020
#define TASK_CLUSTER_DIR	0x00000040
#define TASK_CLUSTER_REPL	0x00000080
#define TASK_COLLECTOR		0x00000100
#define TASK_DB_SERVER		0x00000200
#define TASK_EVENT			0x00000400
#define TASK_FTP_SERVER		0x00000800
#define TASK_HTTP_SERVER	0x00001000
#define TASK_IMAP_SERVER	0x00002000
#define TASK_INDEXER		0x00004000
#define TASK_LDAP_SERVER	0x00008000
#define TASK_MTBF_MGR		0x00010000
#define TASK_NNTP_SERVER	0x00020000
#define TASK_POP3_SERVER	0x00040000
#define TASK_ROUTER			0x00080000
#define TASK_REPLICATOR		0x00100000
#define TASK_SCHED_MGR		0x00200000
#define TASK_STATS			0x00400000
#define TASK_WEB_RETRIEVER	0x00800000
#define TASK_REPORTER		0x01000000
#define TASK_SMTPMTA		0x02000000

#define MAX_TASK_COUNT 26

#define TASK_ID_CHRONOS			 0
#define TASK_ID_DB_COMPACT		 1
#define TASK_ID_ADMIN_PROC		 2
#define TASK_ID_AGENT_MGR		 3
#define TASK_ID_BILLING			 4
#define TASK_ID_CALENDAR_CONN	 5
#define TASK_ID_CLUSTER_DIR		 6
#define TASK_ID_CLUSTER_REPL	 7
#define TASK_ID_COLLECTOR		 8
#define TASK_ID_DB_SERVER		 9
#define TASK_ID_EVENT			 10
#define TASK_ID_FTP_SERVER		 11
#define TASK_ID_HTTP_SERVER		 12 
#define TASK_ID_IMAP_SERVER		 13
#define TASK_ID_INDEXER			 14
#define TASK_ID_LDAP_SERVER		 15
#define TASK_ID_MTBF_MGR		 16
#define TASK_ID_NNTP_SERVER		 17
#define TASK_ID_POP3_SERVER		 18
#define TASK_ID_ROUTER			 19
#define TASK_ID_REPLICATOR		 20
#define TASK_ID_SCHED_MGR		 21
#define TASK_ID_STATS			 22
#define TASK_ID_WEB_RETRIEVER	 23
#define TASK_ID_REPORTER		 24
#define TASK_ID_SMTPMTA			 25

/* Monitor flags */
#define STAT_REPORTING		0x00000001 /* Generate stat reports to statrep.nsf.  TRUE=yes FALSE=no */
#define ALARM_CHECKING		0x00000002 /* Generate alarms for monitored stats. TRUE=yes FALSE=no */


typedef struct
	{
	char 		TaskName[24];					/* For return of user defined tasks */
	TIMEDATE 	LastTaskTime;				 	/* Time task last updated status */
	WORD 		Fatal;							/* Fatal errors returned by task */
	WORD 		Failure;						/* Failure errors returned by task */
	WORD 		WarningHigh;					/* Warning(High) errors returned by task */
	DWORD 		TaskMask;						/* Mask to know which task this is */
	} TASK_STATUS_BLOCK;

typedef struct
	{
	DWORD 		Task;							/* Task to be processed by collector I.E.: Add server */
	DWORD 		Interval;						/* Intreval to return info in minutes */
	char 		StatName[MAXSPRINTF];			/* REMOVE */
	char 		StatServerName[MAXPATH];		/* Name of server that you want info about */
	char 		MonitorServerName[MAXPATH];	 	/* If remote provide proxy server name otherwise NULL */
	DWORD 		MonitorFlags;					/* Flags passed to monitor (Reports, Alarms, ...) */
	HANDLE 		hTaskList;						/* List of user defined tasks to monitor */
	DWORD		TaskListLen;					/* Size of stat list */
	HANDLE 		hStatList;						/* List of stats to return to monitor */
	DWORD		StatListLen;					/* Size of stat list */
	char 		QueueName[20];					/* Used by remote collector to pass info to proxy collector */
	} SERVER_MSG_BLOCK;

typedef struct
	{			
	char	StatName[MAXSPRINTF];		
	char 	StatValue[MAXSPRINTF];						
	} STAT_MONITOR_BLOCK;


typedef struct
	{
	STATUS 		error;						 	/* Error rturned by remote server */
	TIMEDATE 	TimeStamp;					 	/* Time info retrieved */
	BOOL 		Build;							/* TRUE=V5+, FALSE=pre-V5 */
	char 		StatServerName[MAXPATH];		/* Server returning info */
	char 		RtnBuffer[MAXSPRINTF];		 	/* Error or list of stats and  their values */
	WORD 		TaskCount;						/* Count of TASK_STATUS_BLOCK's in hTaskBuffer */
	TASK_STATUS_BLOCK TaskBuffer[26];	 		/* REMOVE */
	HANDLE 		hRetStats;						/* Handle to stat info (type - TEXT) */
	WORD 		wRetStatsCount;					/* Size of of block hRetStats */
	DWORD 		RunningTasks;					/* Task mask see stats.h */
	HANDLE 		hTaskBuffer;					/* Handle to task info (type - TASK_STATUS_BLOCK) */
	HANDLE 		hUserTaskBuffer;				/* Handle to user task info (type - TASK_STATUS_BLOCK) */
	WORD 		UserTaskCount;					/* Count of TASK_STATUS_BLOCK's in hUserTaskBuffer */
	BOOL 		Quiting;						/* TRUE=V5+, FALSE=pre-V5 */
	BOOL		HangUp;
	} RETURN_MSG_BLOCK;

typedef struct
	{
	char 		ServerName[MAXPATH];			/* Server generating alarm */
	char 		AlarmString[MAXSPRINTF];		/* Alarm text */
	} ALARM_REPORT_BLOCK;

typedef struct
	{
	char 	StatName[MAXSPRINTF];			
	HANDLE	hStatName;			
	DWORD	StatNameSize;			
	char 	ServerName[MAXPATH];			
	STATUS 	error;							
	} STAT_RETURN_BLOCK;

/*	Prototypes */

STATUS LNPUBLIC	 StatUpdate (char far *Facility, char far *StatName, WORD Flags, WORD ValueType, void far *Value);
void LNPUBLIC	 StatDelete (char far *Facility, char far *StatName);
STATUS LNPUBLIC	 StatReset (char *Facility, char *StatName);
typedef STATUS (LNCALLBACKPTR STATTRAVERSEPROC)(void far *, char far *, char far *, WORD, void far *);
void LNPUBLIC	 StatTraverse (char far *Facility, char far *StatName, STATTRAVERSEPROC Routine, void far *Context);
void LNPUBLIC	 StatToText(char far *Facility, char far *StatName, WORD ValueType, void far *Value,
							char far *NameBuffer, WORD NameBufferLen,
							char far *ValueBuffer, WORD ValueBufferLen);
STATUS LNPUBLIC	 StatQuery(char far *HeaderString,
							char far *NamePrefix, char far *ValuePrefix,
							char far *LineSuffix,
							HANDLE far *rethStats, DWORD far *retStatsLength);
STATUS LNPUBLIC  StatQueryTime(char far *Facility, char far *StatName, char far *HeaderString,
							char far *NamePrefix, char far *ValuePrefix,
							char far *LineSuffix,
							HANDLE far *rethStats, DWORD far *retStatsLength);

#endif

#ifdef __cplusplus
}
#endif

