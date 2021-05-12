//===========================================================================
//
//      Module: MThread.CPP
//
//      Description:
//          This is a Notes C++ API sample application that demonstrates
//          how to use the multithreading features of the C++ API.
//
//      Syntax: MThread
//
//===========================================================================

#include <iostream.h>
#include "lncppapi.h"

// Put multiplatform definitions for threading code here.
// NOTE:  So far, only Win32 is completely supported.  The WAITFORTHREADS
// macro needs to be implemented for UNIX and OS/2.  Need to find simillar
// functionality to the Win32 WaitForMultipleObjects() function on those
// platforms.

#if defined OS2

    #define INCL_DOSPROCESS     // for DosSleep function
    #include <os2.h>

    #define THREADFUNC void _Optlink
    #define CREATETHREAD(func, arg) _beginthread(func, 0, 8192, arg)
    #define ENDTHREAD() _endthread()
    #define SLEEP(x) DosSleep(x)

#elif defined UNIX

    #include <pthread.h>

    static pthread_t thread;
    #define THREADFUNC void
    #define CREATETHREAD(func, arg) \
        pthread_create(&thread, pthread_attr_default, func, arg)
    #define ENDTHREAD() pthread_exit(NULL)
    #define SLEEP(x) sleep(x)

#else   // Win32

    #include <process.h>
    #define THREADFUNC unsigned __stdcall
    #define MAX_THREADS MAXIMUM_WAIT_OBJECTS
    #define THREADCOUNT 5
    #define THREADHANDLE static HANDLE

    #define CREATETHREAD(func, arg, pThreadID) \
        (HANDLE)_beginthreadex(NULL, 0, func, arg, 0, pThreadID)

    //  This is the prototype for the _beginthreadex function for Win32
    //
    //  unsigned long _beginthreadex( 
    //      void *security,
    //      unsigned stack_size, 
    //      unsigned ( __stdcall *start_address )( void * ), 
    //      void *arglist, 
    //      unsigned initflag, 
    //      unsigned *thrdaddr
    //  );

    #define ENDTHREAD(retval) _endthreadex( retval )

    #define SLEEP(x) Sleep(x)

    #define WAITFORTHREADS( count, handlearray, waitflag, timeout ) \
        WaitForMultipleObjects( count, handlearray, waitflag, timeout )

    //  This is the prototype for the WaitForMultipleOpjects function for Win32
    //
    //  DWORD WaitForMultipleObjects(
    //      DWORD nCount,             // number of handles in the handle array
    //      CONST HANDLE *lpHandles,  // pointer to the object-handle array
    //      BOOL fWaitAll,            // wait flag
    //      DWORD dwMilliseconds      // time-out interval in milliseconds
    //  );

    #define CLOSETHREAD( threadhandle ) CloseHandle(threadhandle)

#endif

// Forward declarations:

THREADFUNC ThreadFunc( void *dummy );

//---------------------------------------------------------------------------
//
//      MAIN
//
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
int             ProgramStatus = 0;
int             index[THREADCOUNT];
LNNotesSession  Session;

    // Throw all errors encountered during command execution.
    // The Throw all errors macro is global across all threads,
    // so exceptions occurring in the C++ API called from any
    // thread will throw and must be inside a try block
    // if you want to catch them in the thread.

    LNSetThrowAllErrors (TRUE);

    try
    {
    THREADHANDLE aThreads[THREADCOUNT];
    THREADHANDLE hNewThread;
    unsigned threadID;
    int ThreadCount = THREADCOUNT;


        // Initialize the API. This is the master LNNotesSession object.
        // Each thread must have its own local LNNotesSession object
        // as well.  This master Session object must be initialized
        // before the threads can initialize their session objects,
        // and all of the threads must have terminated their session
        // objects before this master Session object is terminated.

        Session.Init (argc, argv);

        // Start the threads.  Do not start more than the operating
        // system allows to run concurrently.

        if (ThreadCount > MAX_THREADS)
            throw "Error! Cannot allocate this many threads.";

        for (int i = 0; i < ThreadCount; i++)
        {
            index[i] = i;
            cout << "Starting thread: " << i << endl;

            // NOTE: WIN32 returns -1 for error. Other platforms may return other
            // constants for an error condition.  TODO: Need to create multiplatform
            // constant definitions to make this logic work on all platforms!!! ***dhs

            hNewThread = CREATETHREAD(ThreadFunc, &index[i], &threadID);
            if (hNewThread < 0)
            {
                cout << "\nUnable to start thread!" << endl;
                ThreadCount = i;
                break;
            }
            
            aThreads[i] = hNewThread;
        }

        // The Main thread is pretty much done now.  It just
        // needs to wait until all threads finish, and then 
		// clean up, terminate the Session, and exit.

        // WAITFORTHREADS is implemented so that it uses minimal
        // processor reasource.

        if (ThreadCount)
        {
            WAITFORTHREADS( ThreadCount, aThreads, TRUE, INFINITE );

            // When this returns, all the threads will be done
            // and in the signaled state ready to be destroyed.
            // Clean em up now.

            for (int i=0; i<ThreadCount; i++)
                CLOSETHREAD(aThreads[i]);
        }

        cout << "\nExecution successful" << endl;

    } // END try

    catch (LNSTATUS lnerror)
    {
    char ErrorBuf[LNERROR_MESSAGE_LENGTH];

        LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);
        cout << "\nException thrown during execution of main process." << endl;
        cout << "\nError:  " << ErrorBuf << endl;
        ProgramStatus = 3;
    }

    catch (const char *pErrorMessage)
    {
        cout << "\nException thrown during execution of main process." << endl;
        cout << "\nError: " << pErrorMessage << endl << endl;
        ProgramStatus = 2;
    }

    catch (...)
    {
        cout << "\nException thrown during execution of main process." << endl;
        cout << "\nError unknown!" << endl;
        ProgramStatus = 1;
    }

    char CommandBuf[80];
    cout << "All Done.  Hit return to exit: ";
    cin.getline(CommandBuf, 80);

    // Terminate the API.
    Session.Term();

    return (ProgramStatus);

} // END MAIN


//---------------------------------------------------------------------------
//
// Name:
//      ThreadFunc
//
// Description:
//      Implementation of an individual C++ API thread process.
//
// Inputs:
//      Pointer to a void that can be de-referenced and cast 
//      to a user-defined parameter block.  In this case, it
//      just holds a pointer to an int.  (The index number of
//      the thread used for id purposes.)
//
// Outputs:
//      None.
//
// Returns:
//      Platform dependent (void or int).
//
// Remarks:
//
//---------------------------------------------------------------------------

THREADFUNC ThreadFunc( void *dummy )
{
int index=*((int*) dummy);
LNNotesSession  tSession;  // Each thread must have its own Session object.
LNString threadname;

    try
    {
    LNString receivesubject;
    LNString sendsubject;

        // Initialize this thread's instance of the Notes session.
        // Each thread must have its own local LNNotesSession object
        // and it must be terminated before the thread exits under
        // all conditions, otherwise it could cause problems in the
        // Notes environment, requiring all Notes-related processes
        // to be terminated and restarted.

        tSession.InitThread();

        // Assign a name to this thread and set up strings.

        switch (index)
        {
        case 0:
            threadname      = "Michael thread";
            sendsubject     = "Hey, Serge!";
            receivesubject  = "spam";
            break;

        case 1:
            threadname      = "Serge thread";
            sendsubject     = "Hey, Dave!";
            receivesubject  = "Hey, Serge!";
            break;

        case 2:
            threadname      = "Dave thread";
            sendsubject     = "Hey, Dan!";
            receivesubject  = "Hey, Dave!";
            break;

        case 3:
            threadname      = "Dan thread";
            sendsubject     = "Oh, no! Here come the Cops!";
            receivesubject  = "Hey, Dan!";
            break;

        case 4:

            threadname      = "Police thread";
            sendsubject     = "All right, guys, let\'s stop the mail spam now!";
            receivesubject  = "Cops!";
            break;

        default:
            threadname = "Error thread!";
            throw "Error!  Too many threads have been spawned.";
            break;
        }

        cout << "Thread: " << threadname << " started." << endl;

        // Send mail message to another thread.

        cout << "Thread: " << threadname << " sending message." << endl;

        LNString receiver;
        LNMailMessage message;

        tSession.CreateMailMessage(&message);

        receiver = tSession.GetUserName();
        message.SetRecipients(receiver);
        message.SetSubject(sendsubject);

        message.Save();
        message.Close();

        // Check for mail from another thread.

        LNDatabase db;
        LNDocumentArray docs;
        LNString searchstring;

        // Construct a simple formula that searches for a key phrase in the 
        // Subject field of all documents in the user's mail database.

        searchstring = "SELECT @Contains( Subject; \"";
        searchstring << receivesubject;
        searchstring << "\" )";

        tSession.GetMailDatabase(&db);
        db.Open();

        LNBOOL nomessage = TRUE;

        while (nomessage)
        {
            // A better synchronization scheme needs to be used here.
			// Don't use the technique shown below.

            SLEEP(1000);

            // Look for a message from other thread.

            db.Search( searchstring, &docs ); 

            // If message is read successfully, clear nomessage flag.

            if (docs.GetCount())
            {
                nomessage = FALSE;
                cout << "Thread: " << threadname << " found message." << endl;
            }
        }
    }

    catch (LNSTATUS lnerror)
    {
    char ErrorBuf[LNERROR_MESSAGE_LENGTH];

        LNGetErrorMessage(lnerror, ErrorBuf, LNERROR_MESSAGE_LENGTH);
        cout << "\nException thrown during execution of thread: " << threadname << endl;
        cout << "\nError:  " << ErrorBuf << endl;
    }

    catch (const char *pErrorMessage)
    {
        cout << "\nException thrown during execution of thread: " << threadname << endl;
        cout << "\nError:  " << pErrorMessage << endl << endl;
    }

    catch (...)
    {
        cout << "\nException thrown during execution of thread: " << threadname << endl;
        cout << "\nError unknown!" << endl;
    }

    // Terminate this thread's session.

    cout << "Thread: " << threadname << " shutting down" << endl;

    tSession.TermThread();

    // Terminate this thread now.

    ENDTHREAD(0);

    return (0);

} // END ThreadFunc()


// END MThread.cpp


