/****************************************************************************

    PROGRAM:   statdemo

    FILE:      statdemo.c

    PURPOSE:   Use the Lotus C API for Domino and Notes the statistics 
	           reporting routines to periodically query the Lotus Domino 
			   Server for statistics.

    DESCRIPTION:
         During initialization, all statistics are queried and written 
         to a new note in the database.  The Server Administrator's 
         name is then modified for this server session only.

         Every 10 minutes, all statistics in nine given facilities 
         are traversed.  The information is written to a new note in 
         the database.

         Conditional compilation is provided for OS/390
         environment which does not support resource string id's.

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <global.h>
#include <stats.h>
#include <osmem.h>
#include <addin.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <ostime.h>
#include <editods.h>
#include <easycd.h>
#include "statdemo.h"

#ifdef OS390
#include <_Ascii_a.h>	/* NOTE: must be the LAST file included */
#endif

#define LINEOTEXT 256
#define NUM_FACILS  9
#define NEW_SERVER_ADMINISTRATOR "Jayne Doe"

#define SERVER_DATABASE_NAME "statdemo.nsf"   /* database we will write to */

#define STAT_ORIGIN_QUERY 1
#define STAT_ORIGIN_TRAVERSE 2

char *FacilTable[NUM_FACILS]  = {STATPKG_OS,
                                 STATPKG_STATS,
                                 STATPKG_OSMEM,
                                 STATPKG_OSSEM,
                                 STATPKG_OSFILE,
                                 STATPKG_SERVER,
                                 STATPKG_REPLICA,
                                 STATPKG_MAIL,
                                 STATPKG_COMM};

/* Function prototypes */

STATUS LNCALLBACK DisplayTrav(void *Context, char *Facility, 
                              char *StatName, WORD ValueType, 
                              void *Value);

STATUS StatNoteCreate (DBHANDLE *phDB, NOTEHANDLE *phNote, 
                       HANDLE *phCompound, WORD StatOrigin);
STATUS StatNoteAddText (HANDLE hCompound, char *StatText);
STATUS StatNoteClose (DBHANDLE hDB, NOTEHANDLE hNote, HANDLE hCompound);

/************************************************************************

    FUNCTION:   AddInMain

    PURPOSE:    Main Domino Server Add-in task entry point

*************************************************************************/

STATUS LNPUBLIC AddInMain (HMODULE hModule, int argc, char *argv[])
{
   int i;
   STATUS nError;       /* return code from API calls */
   HANDLE hStatBuffer;
   DWORD dwStatBufferLen;
   char *pStatBuffer;
   DBHANDLE hDB;
   NOTEHANDLE hNote;
   HANDLE hCompound; 
   char msgBuffer[LINEOTEXT];
      
   /* Initialize this task. */

#if defined (OS390)
    HANDLE     hOldStatusLine;  /* handle to initial default status line*/
    HANDLE     hStatusLineDesc; /* handle to new default status line */
    HMODULE    hMod;            /* add-in task's module handle */

    /* Under OS/390, delete the default status line and create a
       new one so that a more descriptive program name will appear on
       the status line rather than the default program name (the
       value of argv[0]).  There is no need to do this under OS/2 
       because a descriptive program name is given in the resource 
       file. */

    AddInQueryDefaults (&hMod, &hOldStatusLine);
    AddInDeleteStatusLine (hOldStatusLine);
    hStatusLineDesc = AddInCreateStatusLine("Statdemo Sample");
    AddInSetDefaults (hMod, hStatusLineDesc);
   AddInSetStatusText("Initializing");
#else
   AddInSetStatus(ADDIN_MSG_FMT, "Initializing");
#endif

   /* Get all statistics in a formatted statistics buffer */

   nError = StatQuery ("From Stat Query:\n", /* Header string */
                       "  ",               /* chars to preceed stat name */
                       "\t",               /* char to preceed stat value */
                       "\n",               /* char to terminate stat value */
                       &hStatBuffer,       /* return buffer handle */
                       &dwStatBufferLen);  /* return buffer length */

   if (nError != NOERROR)
      return (ERR(nError));

   /* Create a new note for this set of statistics */
   
   nError = StatNoteCreate (&hDB, &hNote, &hCompound, STAT_ORIGIN_QUERY);

   if (nError != NOERROR)
      return (ERR(nError));

   /* Lock the statistics buffer to obtain a pointer to the buffer and
      then copy the buffer to the compound text context. */

   pStatBuffer = OSLock (char, hStatBuffer);

   nError = StatNoteAddText (hCompound, pStatBuffer);
   OSUnlock (hStatBuffer);
   OSMemFree (hStatBuffer);
   if (nError != NOERROR)
   {
      CompoundTextDiscard (hCompound);
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      return (ERR(nError));
   }


   /* Update and close the note and the database */

   nError = StatNoteClose (hDB, hNote, hCompound);
   if (nError != NOERROR)
      return (ERR(nError));

   /* Modify the server's administrator name for this server session only.
      This will not modify the administrator's name in the server record.
    */

   nError = StatUpdate (STATPKG_SERVER,          /* name of facility */
                        "Administrator",         /* stat name */
                        ST_UNIQUE,               /* stat is unique */
                        VT_TEXT,                 /* stat value type */
                        NEW_SERVER_ADMINISTRATOR); /* new name */

   if (nError != NOERROR)
      return (ERR(nError));

#if defined (OS390)
   AddInLogMessageText("StatDemo:  Initialization complete.", NOERROR);
   AddInSetStatusText("Idle"); 
#else
   AddInLogMsg(ADDIN_MSG_FMT, "StatDemo: Initialization complete.");
   AddInSetStatus(ADDIN_MSG_FMT, "Idle");
#endif

   /* Begin the main loop.  We give up control to the server at the start of 
      each iteration, and get control back when the server says it is OK to 
      proceed.  The server returns TRUE when it is time to shut down 
      this task.
    */
 
   while (!AddInIdle())
   {
      /* Report on all the statistics every 10 minutes */

      if (AddInMinutesHaveElapsed(10))
      {
#if defined (OS390)
         AddInSetStatusText("Statdemo:  Traversing statistics");
#else
         AddInSetStatus(ADDIN_MSG_FMT, "Statdemo:  Traversing statistics");
#endif
         /* Create a new note for this set of statistics */
   
         nError = StatNoteCreate (&hDB, &hNote, &hCompound, 
                                  STAT_ORIGIN_TRAVERSE);

         if (nError != NOERROR)
            return (ERR(nError));
    
         for ( i = 0; i < NUM_FACILS; i++)
         {
            sprintf (msgBuffer, "\n\n\nTraversing %s facility\n\n", 
                     FacilTable[i]);
            nError = StatNoteAddText (hCompound, msgBuffer);
            if (nError != NOERROR)
            {
               CompoundTextDiscard (hCompound);
               NSFNoteClose (hNote);
               NSFDbClose (hDB);
               return (ERR(nError));
            }

            StatTraverse(FacilTable[i],        /* name of facility */
                         NULL,                 /* traverse all stats */
                         DisplayTrav,          /* callback function */
                         (void *)&hCompound);  /* param passed to callback
                                                  function */

         } /* for */


         /* Update and close the note and the database */

         nError = StatNoteClose (hDB, hNote, hCompound);
         if (nError != NOERROR)
            return (ERR(nError));

#if defined (OS390)
         AddInLogMessageText("Statdemo: Traversing statistics complete.",
                              NOERROR);
         AddInSetStatusText ("Idle");
#else
         AddInLogMsg(ADDIN_MSG_FMT, 
                     "Statdemo: Traversing statistics complete.");           
         AddInSetStatus(ADDIN_MSG_FMT, "Idle");
#endif
      }
   }

   /* We get here when the server notifies us that it is time to terminate.  
      This is usually when the user has entered "quit" to the server console. 
      Clean up anything we have been doing.  
    */

#if defined (OS390)
   AddInSetStatusText("Terminating");
   AddInLogMessageText ("StatDemo: Termination complete.", NOERROR);
#else
   AddInSetStatus(ADDIN_MSG_FMT, "Terminating");
   AddInLogMsg(ADDIN_MSG_FMT, "StatDemo: Termination complete.");
#endif
  
   return (NOERROR);
}

/************************************************************************

    FUNCTION:  DisplayTrav

    PURPOSE:   User defined traversal routine called by StatTraverse.

    INPUTS:
       Context   - pointer to data passed to StatTraverse to be given to 
                   this function.
       Facility  - pointer to facility name.
       StatName  - pointer to name of statistic.
       ValueType - Value type of the statistic.
       Value     - Value of the statistic.

    RETURNS:
         error status from API calls 

*************************************************************************/

STATUS LNCALLBACK DisplayTrav(void *Context, char *Facility, 
                              char *StatName, WORD ValueType, void *Value)

{
   char NameBuffer[80];
   char ValueBuffer[80];
   char OutBuffer[LINEOTEXT];
   STATUS nError;       /* return code from API calls */

   StatToText(Facility, StatName, ValueType, Value,
            NameBuffer, sizeof(NameBuffer)-1,
            ValueBuffer, sizeof(ValueBuffer)-1);
   sprintf(OutBuffer, "  %s = %s\n", NameBuffer, ValueBuffer);

   nError = StatNoteAddText (*(HANDLE*)Context, OutBuffer);
   return (nError);
}

/************************************************************************

    FUNCTION:   StatNoteCreate

    PURPOSE:    Open the database and create a note.

    ALGORITHM:
         Open the database and create a note.  Return the 
         handle to the database, handle to the note and a 
         handle to a compound text context which will hold 
         the statistics to be printed in the body field of the 
         note.

    INPUTS:
      StatOrigin - STAT_ORIGIN_QUERY if this function was called for
                   StatQuery output.
                   STAT_ORIGIN_TRAVERSE if this function was called for
                   StatTraverse output.

    OUTPUTS:
      phDB       - pointer to returned database handle.
      phNote     - pointer to returned handle to the Note.
      phCompound - pointer to returned handle to the compound text context.
 
    RETURNS:
      error status from API calls 

*************************************************************************/

STATUS StatNoteCreate (DBHANDLE *phDB, NOTEHANDLE *phNote, 
                       HANDLE *phCompound, WORD StatOrigin)
{
   STATUS nError;       /* return code from API calls */
   TIMEDATE StartTime;  /* contents of a time/date field */
   char *TempBuffer;

/* Open the database. */

    if (nError = NSFDbOpen (SERVER_DATABASE_NAME, phDB))
        return (nError);

   /* Create a new data note. */

   nError = NSFNoteCreate (*phDB, phNote);
   if (nError != NOERROR)
   {
      NSFDbClose (*phDB);
        return (nError);
   }

   /* Write the form name to the note. */

    nError = NSFItemSetText (*phNote, "Form",    "StatForm", MAXWORD);
   if (nError != NOERROR)
    {
        NSFNoteClose (*phNote);
        NSFDbClose (*phDB);
        return (nError);
    }

   /* Write the current time into the note. */

    OSCurrentTIMEDATE(&StartTime);
    nError = NSFItemSetTime (*phNote, "StartTime", &StartTime);
   if (nError != NOERROR)
    {
        NSFNoteClose (*phNote);
        NSFDbClose (*phDB);
        return (nError);
    }

   /* Write whether this is StatQuery output or StatTraverse output
      to the note.
    */
   
   switch (StatOrigin)
   {
      case STAT_ORIGIN_QUERY:
         TempBuffer = "StatQuery";
         break;

      case STAT_ORIGIN_TRAVERSE:
         TempBuffer = "StatTraverse";
         break;
   
      default:
         TempBuffer = "Unknown";
         break;
   }
   nError = NSFItemSetText (*phNote, "StatOrigin", TempBuffer, MAXWORD);

   if (nError != NOERROR)
    {
        NSFNoteClose (*phNote);
        NSFDbClose (*phDB);
        return (nError);
    }

   /* Create the CompoundText context */
   nError = CompoundTextCreate (
               *phNote,      /* handle of note */
               "StatBody",   /* item name */
               phCompound);  /* returned handle to CompoundText context */

   if (nError != NOERROR)
   {
      NSFNoteClose (*phNote);
      NSFDbClose (*phDB);
      return (nError);
   }
   return (NOERROR);

}

/************************************************************************

    FUNCTION:   StatNoteClose

    PURPOSE:   Add the compound text context to the note and close
               the note and the database.

    INPUTS:
      hDB       - database handle.
      hNote     - handle to the Note.
      hCompound - handle to the compound text context.

    RETURNS:
      error status from API calls 

*************************************************************************/

STATUS StatNoteClose (DBHANDLE hDB, NOTEHANDLE hNote, HANDLE hCompound)
{
   STATUS nError;       /* return code from API calls */

   /* Add the CompoundText context to the note. Since this is an ItemContext
      (associated with the newly created note), only specify hCompound 
      parameter */

   nError = CompoundTextClose (
             hCompound,            /* handle to CompoundText context */
             0,                    
             0L,
             NULL,
             0);
   if (nError != NOERROR)
   {
      CompoundTextDiscard (hCompound);
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      return (nError);
   }

   /* Add the new note to the database. */

   if ( (nError = NSFNoteUpdate (hNote, 0)) != NOERROR )
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
       return (nError);
   }
   /* Close the new note. */

   if ( (nError = NSFNoteClose (hNote)) != NOERROR )
   {
      NSFDbClose (hDB);
      return (nError);
   }

   /* Close the database */

   if ( (nError = NSFDbClose (hDB)) != NOERROR )
      return (nError);

   return (NOERROR);
}
/************************************************************************

    FUNCTION:   StatNoteAddText

    PURPOSE:    Adds statistics text to the compound text context.  

    INPUTS:
      hCompound - handle to the compound text context
      StatText  - pointer to the text to add
 
    OUTPUTS:

    RETURNS:
      error status from API calls

*************************************************************************/

STATUS StatNoteAddText (HANDLE hCompound, char *StatText)

{
   COMPOUNDSTYLE Style;
   DWORD         dwStyleID;
   STATUS nError;       /* return code from API calls */

   CompoundTextInitStyle (&Style);    /* initializes Style to the defaults */

   nError = CompoundTextDefineStyle (
               hCompound,          /* handle to CompoundText context */
               "Normal",           /* style name */
               &Style,
               &dwStyleID);        /* style id */
 
   if (nError != NOERROR)
      return (nError);

   nError = CompoundTextAddTextExt (
             hCompound,                 /* handle to CompoundText context */
             dwStyleID,                 /* style ID */
             DEFAULT_FONT_ID,           /* font ID */
             StatText,                  /* text to add */
             (DWORD) strlen (StatText), /* length of text */
             "\r\n",                    /* newline delimiter - handle \r \n 
                                           and combinations of \r\n */
             COMP_PRESERVE_LINES,       /* preserve line breaks */
             NULLHANDLE);               /* handle of CLS translation table */

   return (nError);
}


