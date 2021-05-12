/****************************************************************************

    PROGRAM:    threads    

    FILE:       threads.c

    PURPOSE:    sample multi-threaded Domino server add-in task

    SYNTAX:     (at the Domino server console) > load threads

    DESCRIPTION:
    This sample is a multithreaded version of a Domino server add-in 
    task. Three threads are spawned for each of the three operations 
    performed by the addin.  Each worker thread receives messages from
    the main thread's message queues to perform an operation based on 
    specific time intervals; specifically, write a note every 30 seconds
    and every minute, and read the notes every 2 minutes.
   
    For 32 bit Windows thread support, this add-in uses the Win32 API 
    functions _beginthread(), _endthread(),   and Sleep().
   
    For OS2 thread support, this add-in uses the OS2 API functions _
    beginthread(), _endthread(), and DosSleep().

    For portability to other platforms, the thread functions can be 
    replaced as appropriate to be compatible with other platforms.  

    A generic semaphore counter is used to determine if threads are running,
    and a file lock counter is used to serialize access to the local database.

****************************************************************************/

/* OS and standard C include files */

#ifdef OS2_2x
#define INCL_DOSPROCESS /* DosSleep */
#include <os2.h>        
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#if defined (UNIX)
#include <unistd.h>     /*  sleep() */
#include <pthread.h>    /*  pthread_create(), pthread_exit */
#else
#include <process.h>    /* _beginthread, _endthread, Sleep */
#endif

/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <addin.h>
#include <stdnames.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <mq.h>
#include <miscerr.h>
#include <ostime.h>
#include <osmisc.h>
#include <oserr.h>

#ifdef OS390
#include <_Ascii_a.h>   /* NOTE: must be the LAST file included */
#endif

/* Local definitions */

#define NOTES_DATABASE_NAME "threads.nsf"           /* sample database */
#define THIRTYSECOP   "30 SECOND OPERATION"   /* note text field strings */
#define ONEMINOP      "1 MINUTE OPERATION"     
#define THIRTYSECONDS 30     
#define SIXTYSECONDS  60     
#define TWOMINUTES    120     
#define RUNOP         1     
#define QUITOP        2     
#define MAX_MESSAGE   256

/* Global variables */

DBHANDLE    db_handle;       /* open handle to sample db */
NOTEHANDLE  note_handle;     /* note handle */
int         semaphore;       /* thread semaphore count */
int         filelock;        /* nsf file lock count */

char        MsgQueueName[3][128];                 /* generic Message queue name */
char        MsgQueue1[] = TASK_QUEUE_PREFIX "MSG_Q1"; /* Message queue name */
char        MsgQueue2[] = TASK_QUEUE_PREFIX "MSG_Q2"; /* Message queue name */
char        MsgQueue3[] = TASK_QUEUE_PREFIX "MSG_Q3"; /* Message queue name */
MQHANDLE hQueue[3];                              /* Handles to message queue */

   
/* Macros */

#if defined (WIN32)
#define SLEEP(x)    ( Sleep(x) )
#define TIME(x)     ( time(x) )
#elif defined (AIX)
#define SLEEP(x)    ( sleep(x / 1000) )
#define TIME(x)     ( time((int*)x) )
#elif defined (UNIX)
#define SLEEP(x)    ( sleep(x / 1000) )
#define TIME(x)     ( time(x) )
#else /* OS2 */
#define SLEEP(x)    ( DosSleep(x) )
#define TIME(x)     ( time(x) )
#endif

/* Function prototypes */

#if defined (WIN32)
void ThirtySecOps (void *);  /* 30 second operation - write db note */
void OneMinOps (void *);     /* 1 minute operation - write db note */
void TwoMinOps (void *);     /* 2 minute operation - read db notes */
#elif defined (UNIX)
void *ThirtySecOps (void *);  /* 30 second operation - write db note */
void *OneMinOps (void *);     /* 1 minute operation - write db note */
void *TwoMinOps (void *);     /* 2 minute operation - read db notes */
#else /* OS2 thread routines require Optlink calling convention */
void _Optlink ThirtySecOps (void *);  /* 30 second operation - write db note */
void _Optlink OneMinOps (void *);     /* 1 minute operation - write db note */
void _Optlink TwoMinOps (void *);     /* 2 minute operation - read db notes */
#endif

STATUS WriteOpNote (char *);
STATUS LNPUBLIC ReadOpNote (void *, SEARCH_MATCH *, ITEM_TABLE *);
STATUS ProcessMessage (char   *pMsg,WORD  msgLen);

/* Command table entries */
typedef struct {
   char  *pCmdName;
} CMD_ENTRY;

/* Table of commands
 * "TELL THREADS QUIT" is handled by the server.  The 
 * state of the message queue is set to "QUIT".
 */   
CMD_ENTRY CmdTable [] =
{
   {"RUN"},
   {"QUIT"},
   /* This entry marks the end of the table! */
   {NULL}   
};

/************************************************************************

    FUNCTION:   AddInMain

    PURPOSE:    Main entry point for all Domino server add-in tasks 

    ALGORITHM:
    Get the default status line.  Delete it. Create a new status line
    with the task name "Sample Multi-thread Addin".  Set the default 
    status line this new status line. Set the status string to 
    "Initializing".
    
     Call three threads and wait until the Domino server exited, the
     addin is exited, or the threads have completed.  The main thread based
     on time will send messages to the worker threads to simulate one of the 
     following three operations performed by the addin.
     
       Once every 30 seconds call WriteOpNote to write a new note to the
       sample database, while setting the appropriate addin status and writing
        the appropriate addin log messages.

       Once every minute call WriteOpNote to write a new note to the
       sample database, while setting the appropriate addin status and writing
        the appropriate addin log messages.
    
       Once every 2 minutes call ReadOpNote (via NSFSearch) to display all 
       notes in the sample database, while setting the appropriate addin 
       status and writing the appropriate addin log messages.

*************************************************************************/
 
STATUS LNPUBLIC  AddInMain (HMODULE hModule, int argc, char *argv[])
{
    
    /* Local data. */

    HANDLE     hOldStatusLine;  /* handle to initial default status line*/
    HANDLE     hStatusLineDesc; /* handle to new default status line */
    HMODULE    hMod;            /* add-in task's module handle */
    STATUS     error;           /* return code from Lotus C API for Domino and Notes */
    char    MsgBuffer[3] [MAX_MESSAGE + 1];      /* Buffer for messages */
    WORD    MsgLen;                           /* Size of message */

   long       cur_time;    /* current time of day */
   long       op_time_1;      /* current time of day + 30 seconds */
   long       op_time_2;      /* current time of day + 60 seconds */
   long       op_time_3;      /* current time of day + 120 seconds */
   int        counter1=0;
   int        counter2=0;
   int        counter3=0;
   int        threadsdone = 0;
   int        quit_thread[3];
   int         i;

#if defined (UNIX)
    /* points to where thread IDs will be stored */
    pthread_t op_th_30; 
    pthread_t op_th_01;
    pthread_t op_th_02;

    int rc;  /* return value: 
              0      - if succeded; 
             EAGAIN  - The system does not have sufficient resources to 
                       create another  thread.
             EINVAL -  The thread is not valid.  */
#endif

   /* 
      Initialize the addin task -
      Set the task name and status string of this add-in task. The task
      name and status string appear on the status line at the Domino
      server in response to the 'show tasks' command. By default, the
      name in the status line is the name of the program (the value of 
      argv[0]). First get the handle to this default status line descriptor 
      and delete it. Then create a new status line and set the status to
      'Initializing'.
    */
 
    AddInQueryDefaults (&hMod, &hOldStatusLine);
    AddInDeleteStatusLine (hOldStatusLine);
    hStatusLineDesc = AddInCreateStatusLine("Sample Multithread Add-in");
    AddInSetDefaults (hMod, hStatusLineDesc);
    AddInSetStatusText("Initializing Add-in");
    
    /* Initialization is complete */

    AddInLogMessageText("THREADS: Initialization complete.", NOERROR);
    AddInSetStatusText("Idle");     /* 'Idle' replaces 'Initializing' */

    /* Open sample database and assign global handle */

    if (error = NSFDbOpen (NOTES_DATABASE_NAME, &db_handle))
    {
        AddInLogMessageText("Error opening database.", ERR(error));
        return(ERR(error));
    }

    /* Create and Open Message Queues for worker threads */
   strcpy(MsgQueueName[0], MsgQueue1);
   strcpy(MsgQueueName[1], MsgQueue2);
   strcpy(MsgQueueName[2], MsgQueue3);

    for (i=0; i<3; i++)
   {
      
        error = MQCreate (MsgQueueName[i], 0, 0);  /* No quota on messages */
        if (NOERROR != error)
         return (ERR(error));
      
        error = MQOpen (MsgQueueName[i], 0, &hQueue[i]);
        if (NOERROR != error)
         return (ERR(error));
    }


   /* Initialize semaphore and lock counts and spawn threads for each of 
      the addin operations
   */

   semaphore = 0;
   filelock = 0;

#if defined (UNIX)
   rc = pthread_create(&op_th_30, NULL, ThirtySecOps, NULL);
    rc = pthread_create(&op_th_01, NULL, OneMinOps, NULL);
    rc = pthread_create(&op_th_02, NULL, TwoMinOps, NULL);
#elif defined (WIN32)        
   _beginthread (ThirtySecOps, 0, NULL);   /* 30 Second op thread */
   _beginthread (OneMinOps, 0, NULL);      /* 1 Minute op thread */
   _beginthread (TwoMinOps, 0, NULL);      /* 2 Minute op thread */
#else /* OS2 */
   _beginthread (ThirtySecOps, NULL, 16384, NULL);   /* 30 Second op thread */
   _beginthread (OneMinOps, NULL, 16384, NULL);      /* 1 Minute op thread */
   _beginthread (TwoMinOps, NULL, 16384, NULL);      /* 2 Minute op thread */
#endif


    TIME(&cur_time);
    op_time_1 = cur_time;
    op_time_2 = cur_time;
    op_time_3 = cur_time;
    quit_thread[0] = 0;
    quit_thread[1] = 0;
    quit_thread[2] = 0;

         /* let's sleep until at least one thread starts */

         while (semaphore == 0)
                SLEEP(5000L);


      /*
     * thread message queues.  Each thread is then told to terminate after a specific number
     * of job assignments have been sent.
     */

     while (threadsdone < 3)
     {
       AddInIdleDelay(5000);

        if (semaphore == 0)
                goto Done;
         
      /* get current time */
      TIME(&cur_time);

        /* send message every 30 seconds */
        if ((cur_time >= op_time_1 + THIRTYSECONDS) && !quit_thread[0])
       {
        /* if assigned jobs == 6 tell thread to quit */
          if (++counter1 > 6)
        {
          strcpy(MsgBuffer[0], "QUIT");
          MsgLen = strlen(MsgBuffer[0]);

            /* put the QUIT message in the first queue */
         error = MQPut (hQueue[0], 1, MsgBuffer[0], MsgLen, 0);
          if (error)
            goto Done;
            threadsdone++;
         quit_thread[0] = 1;
        }
        else /* tell thread to run job */
        {
            strcpy(MsgBuffer[0], "RUN");
          MsgLen = strlen(MsgBuffer[0]);
            
            /* put the RUN message in the first queue */
            error = MQPut (hQueue[0], 1, MsgBuffer[0], MsgLen, 0);
          if (error)
            goto Done;
        }

          op_time_1 += THIRTYSECONDS; /* bump up time another 30 seconds */
       }
         
         /* send message every 60 seconds */
        if ((cur_time >= op_time_2 + SIXTYSECONDS) && !quit_thread[1])
       {
        
        /* if assigned jobs == 3 tell thread to quit */
                  if (++counter2 > 3)
        {
          strcpy(MsgBuffer[1], "QUIT");
          MsgLen = strlen(MsgBuffer[1]);

            /* put the QUIT message in the second queue */
         error = MQPut (hQueue[1], 1, MsgBuffer[1], MsgLen, 0);
          if (error)
            goto Done;
            threadsdone++;
         quit_thread[1] = 1;
        }
        else /* tell thread to run job */
        {
         strcpy(MsgBuffer[1], "RUN");
          MsgLen = strlen(MsgBuffer[1]);
            
            /* put the RUN message in the second queue */
           error = MQPut (hQueue[1], 1, MsgBuffer[1], MsgLen, 0);
          if (error)
            goto Done;
        }
          op_time_2 += SIXTYSECONDS; /* bump up time another 60 seconds */
       }

       /* send message every two minutes */
        if ((cur_time >= op_time_3 + TWOMINUTES) && !quit_thread[2])
       {
        /* if assigned jobs == 2 tell thread to quit */
              if (++counter3 > 2)
        {
          strcpy(MsgBuffer[2], "QUIT");
          MsgLen = strlen(MsgBuffer[2]);
            
            /* put the QUIT message in the third queue */
         error = MQPut (hQueue[2], 1, MsgBuffer[2], MsgLen, 0);
          if (error)
            goto Done;
            threadsdone++;
         quit_thread[2] = 1;

        }
        else /* tell thread to run job */
        {
          strcpy(MsgBuffer[2], "RUN");
          MsgLen = strlen(MsgBuffer[2]);
            
            /* put the RUN message in the third queue */
           error = MQPut (hQueue[2], 1, MsgBuffer[2], MsgLen, 0);
          if (error)
            goto Done;
        }
          op_time_3 += TWOMINUTES; /* bump up time another 2 minutes */
       }

     }
            
   /* We get here when the server notifies us that it is time to terminate.  
      This can occur when 
         1) The user has entered "quit" at the server console. 
        2) The user has entered "tell <ThisTask> quit" at the server console.
        3) When all three operation threads have ended.
    */

    /* Wait for threads to terminate for user exits */

    AddInSetStatusText("Terminating Add-In Threads");
    while ( semaphore )
        SLEEP(5000L);

    
Done:
    /* close the message queues */
    for (i=0; i<3; i++)
   {
        error = MQClose (hQueue[i], 0);
        if (error)
          return (ERR(error));
      }
    NSFDbClose (db_handle);
    AddInSetStatusText("Terminating Add-in");
    AddInLogMessageText("THREADS: Termination complete.", NOERROR);
    
   /* End of add-in task.  We must "return" here rather than "exit". */

    return (NOERROR);
}

/************************************************************************

    FUNCTION:   ThirtySecOps

    PURPOSE:    Addin thread routine that performs "30 Second" operations
                by writing a note to the sample database.

*************************************************************************/

#if defined (WIN32)
void ThirtySecOps(void *dummy)
#elif defined (UNIX)
void *ThirtySecOps(void *dummy)
#else /* OS2 */
void _Optlink ThirtySecOps(void *dummy)
#endif
{
   STATUS  error;
    int     counter = 0;
   int     op = 0;
   char  MsgBuffer [MAX_MESSAGE + 1];  /* Buffer for messages */
    WORD MsgLen;                       /* Size of message */


      
   /* First increment semaphore */

    semaphore++;
     
   /* Initialize Domino and Notes thread - required by threads calling the Lotus C API for Domino and Notes */

    error = NotesInitThread ();                 
    if (error)
    {
      AddInLogMessageText("Error initializing 30 Second operation thread.",
                        NOERROR);
        semaphore--;

#if defined (UNIX)
      pthread_exit(NULL);
#else
      _endthread();
#endif
    }


    /* while there isn't an error loop for messages from main thread */
 
    while (NOERROR == error)
    {

        /* if the main thread terminates we're done */
        if (AddInShouldTerminate())
                goto Done;
            
      /* attempt to get a message from the queue and wait for 5 seconds */ 
      error = MQGet (hQueue[0], MsgBuffer, MAX_MESSAGE,
         MQ_WAIT_FOR_MSG, (5 * 1000), &MsgLen);

      MsgBuffer[MsgLen] = '\0';

        /* if we received a message... */
      if (NOERROR == error)
      {
          /* get the message from the buffer */
         op = ProcessMessage (MsgBuffer, MsgLen);
   
           /* perform operation depending on message received */
           switch(op)
         {
           /* run the job assignment */
           case RUNOP:
                AddInSetStatusText("Performing 30 Second operation");
       
                /* Do not write note until the database is no longer opened by one
                   of the other threads.
                 */
           
               while ( filelock ) 
                  SLEEP (50L);
                filelock++;                             /* lock database */
              if (error = WriteOpNote(THIRTYSECOP))   /* and write note */
                {
                AddInLogMessageText("Error writing 30 Second operation  Note to database.",
                        ERR(error));
                  goto Done;
                }
              AddInLogMessageText("THREADS: 30 Second operation complete.", 
                           NOERROR);
              AddInSetStatusText("30 Second operation Idle");
             break;
         
           /* quit the job */
           case QUITOP:
            goto Done;
             break;
         
           default:
            error = op;
              break;
         }
      }
      /* if we have a timeout loop again */
      else if (ERR_MQ_TIMEOUT == error)
      {
         error = NOERROR;
      }
   
    }   /* End of main task loop. */
 

   /* We get here when the server notifies us that it is time to terminate.  
      Clean up anything we have been doing.  
    */

Done:
    AddInLogMessageText("THREADS: Ending 30 Second operation thread.",
                  NOERROR);
    AddInSetStatusText("Exiting 30 Second operation");

   /* Terminate Domino and Notes thread, decrement semaphore count, and end OS thread */

    NotesTermThread ();                 
   semaphore--;

#if defined (UNIX)
      pthread_exit(NULL);

#if defined (HPUX)
      return(NULL);
#endif

#else
      _endthread();
#endif
} 

/************************************************************************

    FUNCTION:   OneMinOps

    PURPOSE:    Addin thread routine that performs "1 Minute" operations
                by writing a note to the sample database.

*************************************************************************/

#if defined (WIN32)
void OneMinOps(void *dummy)
#elif defined (UNIX)
void *OneMinOps(void *dummy)
#else /* OS2 */
void _Optlink OneMinOps(void *dummy)
#endif
{
   STATUS  error;
    int     counter = 0;
   int     op = 0;
    char MsgBuffer [MAX_MESSAGE + 1];  /* Buffer for messages */
    WORD MsgLen;                       /* Size of message */

   /* First increment semaphore */

    semaphore++;

   /* Initialize Domino and Notes thread - required by threads calling the Lotus C API for Domino and Notes. */

    error = NotesInitThread ();                 
    if (error)
    {
      AddInLogMessageText("Error initializing 1 Minute operation thread.", 
                        NOERROR);
        semaphore--;

#if defined (UNIX)
      pthread_exit(NULL);
#else
      _endthread();
#endif
    }

    /* while there isn't an error loop for messages from main thread */
 
    while (NOERROR == error)
    {

        /* if the main thread terminates we're done */
        if (AddInShouldTerminate())
                goto Done;
   
      /* attempt to get a message from the queue and wait for 5 seconds */ 
      error = MQGet (hQueue[1], MsgBuffer, MAX_MESSAGE,
         MQ_WAIT_FOR_MSG, (5 * 1000), &MsgLen);

      MsgBuffer[MsgLen] = '\0';

        /* if we received a message... */
      if (NOERROR == error)
      {
          /* get the message from the buffer */
         op = ProcessMessage (MsgBuffer, MsgLen);
   
           /* perform operation depending on message received */
           switch(op)
         {
           /* run the job assignment */
           case RUNOP:
             AddInSetStatusText("Performing 1 Minute operation");

                /* Do not write note until the database is no longer opened by one
                   of the other threads.
                */
          
                while ( filelock ) 
                  SLEEP (50L);
                filelock++;                         /* lock database */
                 if (error = WriteOpNote(ONEMINOP))  /* and write note */
               {
                AddInLogMessageText("Error writing 1 Minute operation note to database.",
                           ERR(error));
                 goto Done;
                }
               AddInLogMessageText("THREADS: 1 Minute operation complete.", NOERROR);
              AddInSetStatusText("1 Minute operation idle");
                break;
         
           /* quit the job */
           case QUITOP:
            goto Done;
             break;
         
           default:
            error = op;
              break;
         }
      }
      else if (ERR_MQ_TIMEOUT == error)
      {
         error = NOERROR;
      }
   
    }   /* End of main task loop. */
 
   /* We get here when the server notifies us that it is time to terminate.  
      Clean up anything we have been doing.  
    */
    
Done:
    AddInLogMessageText("THREADS: Ending 1 Minute operation thread.", NOERROR);
    AddInSetStatusText("Exiting 1 Minute operation");

   /* Terminate Domino and Notes thread, decrement semaphore count, and end OS thread */

    NotesTermThread (); 
   semaphore--;

#if defined (UNIX)
      pthread_exit(NULL);
#if defined (HPUX)
      return(NULL);
#endif

#else
      _endthread();
#endif
} 

/************************************************************************

    FUNCTION:   TwoMinOps

    PURPOSE:    Addin thread routine that performs "2 Minute" operations..
                by reading and displaying all the notes in the sample database.

*************************************************************************/

#if defined (WIN32)
void TwoMinOps(void *dummy)
#elif defined (UNIX)
void *TwoMinOps(void *dummy)
#else /* OS2 */
void _Optlink TwoMinOps(void *dummy)
#endif
{
    DBHANDLE    read_handle;    /* local database handle */
   STATUS      error;
    int         counter = 0;
   int         op = 0;
   char      MsgBuffer [MAX_MESSAGE + 1]; /* Buffer for messages */
    WORD     MsgLen;                      /* Size of message */

   /* First increment semaphore */

    semaphore++;

   /* Initialize Domino and Notes thread - required by threads calling the Lotus C API for Domino and Notes. */

    error = NotesInitThread ();                 
    if (error)
    {
      AddInLogMessageText("Error initializing 2 Minute operation thread.",
                     NOERROR);
        semaphore--;

#if defined (UNIX)
      pthread_exit(NULL);
#else
      _endthread();
#endif
    }

    /* while there isn't an error loop for messages from main thread */
 
    while (NOERROR == error)
    {

        /* if the main thread terminates we're done */
        if (AddInShouldTerminate())
                goto Done;
            
      /* attempt to get a message from the queue and wait for 5 seconds */ 
      error = MQGet (hQueue[2], MsgBuffer, MAX_MESSAGE,
         MQ_WAIT_FOR_MSG, (5 * 1000), &MsgLen);

      MsgBuffer[MsgLen] = '\0';

        /* if we received a message... */
      if (NOERROR == error)
      {
          /* get the message from the buffer */
         op = ProcessMessage (MsgBuffer, MsgLen);
   
           /* perform operation depending on message received */
           switch(op)
         {
           /* run the job assignment */
           case RUNOP:
                AddInSetStatusText("Performing 2 Minute operation");

                AddInLogMessageText("THREADS: Begin 2 Minute Database Summary:",NOERROR);

                /* Do not read note until the database is no longer opened by one
                   of the other threads.
                */

                  while ( filelock ) 
                 SLEEP (50L);   /* sleep length based on typical lock time */

                /* Lock and reopen the database from the global handle. */
   
                filelock++;        
                if (error = NSFDbReopen (db_handle, &read_handle))
                {
                  AddInLogMessageText("Error opening database.", 
                           ERR(error));
                  filelock--;
                  goto Done;
                }
   
                /* Call NSFSearch to find all data notes in the database. */

                if (error = NSFSearch (
                    read_handle,        /* database handle */
                    NULLHANDLE,       /* selection formula (all) */
                    NULL,             /* title of view in selection formula */
                    0,                /* search flags */
                    NOTE_CLASS_DATA,  /* note class to find */
                    NULL,             /* starting date (unused) */
                    ReadOpNote,       /* action routine for notes found */
                    &read_handle,       /* argument to action routine */
                    NULL))            /* returned ending date (unused) */
                {
                  NSFDbClose (read_handle);
                  AddInLogMessageText("Error reading notes from database.", 
                                   ERR(error));
                  filelock--;
                  goto Done;
                }

               /* Close and unlock the database. */
           
              if (error = NSFDbClose (read_handle))
              {
                AddInLogMessageText("Error closing database.", 
                                    ERR(error));
                filelock--;
                goto Done;
              }
              filelock--;
              AddInLogMessageText("THREADS: 2 Minute operation complete.", 
                                NOERROR);
                AddInSetStatusText("2 Minute operation Idle");
              break;
         
           /* quit the job */
           case QUITOP:
            goto Done;
             break;
         
           default:
            error = op;
              break;
         }
      }
      else if (ERR_MQ_TIMEOUT == error)
      {
         error = NOERROR;
      }
   
    }   /* End of main task loop. */
 

   /* We get here when the server notifies us that it is time to terminate.  
      Clean up anything we have been doing.  
    */

Done:
    AddInLogMessageText("THREADS: Ending 2 Minute operation thread.",
                  NOERROR);
    AddInSetStatusText("Exiting 2 Minute operation");

   /* Terminate Domino and Notes thread, decrement semaphore count, and end OS thread */

    NotesTermThread ();                 
   semaphore--;

#if defined (UNIX)
      pthread_exit(NULL);
#if defined (HPUX)
      return(NULL);
#endif

#else
      _endthread();
#endif
} 

/************************************************************************

    FUNCTION:   WriteOpNote

    PURPOSE:    Local function called by the operation thread routines to 
                write a note to the sample database.  Checks that file 
                locks are in place before opening local database.

*************************************************************************/

STATUS WriteOpNote (char *op_thread)
{

/* Local data declarations. */

    DBHANDLE    write_handle;       /* local database handle */
    STATUS      error = NOERROR;    /* return code from API calls */
    TIMEDATE    timedate;           /* contents of a time/date field */
    char        thread_text[64];    /* thread specific item text */

   /* First ensure that the file has been locked. */

    if (filelock < 1) 
    {
        filelock = 0;
        return (ERR(ERR_LOCK_FAILED));
    }
    
   /* Then ensure that the database file has been locked by only one thread. */
   
    if (filelock > 1) 
    {
        error = ERR_LOCK;
        goto Done;
    }

   /* Reopen the database from the global handle. */

    if (error = NSFDbReopen (db_handle, &write_handle))
      goto Done;
   
   /* Create a new data note. */

    if (error = NSFNoteCreate (write_handle, &note_handle))
    {
       NSFDbClose (write_handle);
      goto Done;
    }

   /* Write the form name to the note. */

    if (error = NSFItemSetText (note_handle, "Form", "AddInForm", MAXWORD))
    {
       NSFNoteClose (note_handle);
      NSFDbClose (write_handle);
       goto Done;
    }
    
   /* Write a text field to the note. */

    sprintf(thread_text, "%s thread note.",  op_thread);
    if (error = NSFItemSetText (note_handle, "AddIn_Text",
                thread_text, MAXWORD))
    {
      NSFNoteClose (note_handle);
       NSFDbClose (write_handle);
      goto Done;
    }
    
   /* Write the current time into the note. */

    OSCurrentTIMEDATE(&timedate);
    if (error = NSFItemSetTime (note_handle, "AddIn_Time", &timedate))
    {
      NSFNoteClose (note_handle);
       NSFDbClose (write_handle);
      goto Done;
    }

   /* Add the note to the database. */

    if (error = NSFNoteUpdate (note_handle, 0))
    {
       NSFNoteClose (note_handle);
      NSFDbClose (write_handle);
      goto Done;
    }

   /* Deallocate the new note from memory. */

    if (error = NSFNoteClose (note_handle))
    {
       NSFDbClose (write_handle);
      goto Done;
    }
    
   /* Close the database. */

    if (error = NSFDbClose (write_handle))
       goto Done;
    
   /* End of function.  Unlock database file and return status. */

Done:
    filelock--;
    return (error);
}


/************************************************************************

    FUNCTION:   ReadOpNote

    PURPOSE:    Local function called by the operation thread routines to 
                read and print out all the notes from the sample database.
                Assumes that file locks are in place for local database.

                This routine is called by NSFSearch for each note that 
                matches the selection criteria (in this case all the notes)

    INPUTS:
        The first argument to this function is the optional argument
        that we supplied when we called NSFSearch.

        The second argument is supplied by NSFSearch.    It is
        a structure of information about the note that was found.

        The third argument is also supplied by NSFSearch and is
        the summary buffer for this note. 


*************************************************************************/

STATUS LNPUBLIC ReadOpNote ( VOID *read_handle,
                            SEARCH_MATCH *search_info,
                            ITEM_TABLE *summary_info)
{

/* Local data declarations. */

    STATUS          error;
    char            field_text[64];          /* contents of a AddIn_Text field */
    WORD            field_len;               /* length of field */
    char            msg_text[80];            /* add-in message string */
    SEARCH_MATCH    SearchMatch;             /* local copy of search match */  

    memcpy ((char*)(&SearchMatch), (char *)search_info, sizeof(SEARCH_MATCH));

    /* Skip this note if it does not really match the search criteria (it is
     * now deleted or modified).  This is not necessary for full searches,
     * but is shown here in case a starting date was used in the search. 
     */

    if (!(SearchMatch.SERetFlags & SE_FMATCH))
        return (NOERROR);

    /* Open the note. */

    if (error = NSFNoteOpen (
            *(DBHANDLE *)read_handle,         /* database handle */
            SearchMatch.ID.NoteID,          /* note ID */
            0,                              /* open flags */
            &note_handle))                  /* note handle (return) */
       
        return (ERR(error));

    /* Get note text item. */

    field_len = NSFItemGetText ( note_handle, 
                            "AddIn_Text",
                             field_text,
                             (WORD) sizeof (field_text));
    field_text[field_len] = '\0';
 
    /* Build message text: note ID + field text. */
    sprintf (msg_text, "     Note ID: %lX", SearchMatch.ID.NoteID);
    sprintf (msg_text, "%s - %s", msg_text, field_text);

    /* Display the note information message. */

    AddInLogMessageText(msg_text, NOERROR);

    /* Close the note. */

    if (error = NSFNoteClose (note_handle))
        return (ERR(error));

    /* End of subroutine. */

    return (NOERROR);
}

/************************************************************************

    FUNCTION:   ProcessMessage

    PURPOSE:    Figure out which command we got (if any).
    
    NOTE:      This function modifies the message buffer pointed
            to by the pMsg parameter!

*************************************************************************/

STATUS ProcessMessage(char *pMsg,   WORD msgLen) 
{
   CMD_ENTRY   *pEntry;
   char    *pCmd;
   WORD     originalLen;

   originalLen = msgLen;
         
    /* Skip any leading blanks in message */
   while ((msgLen > 0) && (isspace (*pMsg)))
   {
      msgLen--;
      pMsg++;
   }
   
   /* Split off the command */
   pCmd = pMsg;
   while ((msgLen > 0) && (!isspace (*pMsg)))
   {
      *pMsg = (char) toupper (*pMsg);
      msgLen--;
      pMsg++;
   }
   
   /* Null-terminate the command name */
   *(pMsg++) = '\0';
   if (msgLen > 0)
      msgLen--;
   
   /* Look up command in command table */
   for (pEntry = CmdTable; TRUE; pEntry++)
   {
      if (((char *) NULL) == pEntry->pCmdName)
      {
         /* Log as a bad command */
         *(pMsg - 1) = ' ';
         return (-1);
      }
      else if (strcmp (pEntry->pCmdName, pCmd)==0)
      {

          if (strcmp(pCmd,"RUN")==0)
          return(RUNOP);
          else if (strcmp(pCmd,"QUIT")==0)
          return(QUITOP);
      }
   }
}
