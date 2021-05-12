//===========================================================================
//
//
//	Program:    Schedule
//
//	File:       SCHEDULE.CPP
//
//	Syntax:     SCHEDULE <filename> <ownername> <start date> <end date> [<server>]
		
//				A sample command line for schedule is:
//	schedule jdoe.nsf "Jane Doe" "07/08/98 9:00am" "07/08/98 10:00am" "Saturn"
//	(The date syntax is mm/dd/yy)
//
//	Description:
//				This program shows how to use the calendaring and scheduling 
//				features.
//
//  Note: 		This sample could take a minute or more to run if you have a 
//				large number of entries in your calendar.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#include <iostream.h>

#include <lncppapi.h>
#include <lncalend.hpp>

#define ERR_BUF_SIZE 512

#if defined(MAC)
// These headers are only needed for Macintosh applications
#include <Types.h>
#include <Quickdraw.h>
#define thePort qd.thePort
#include <Dialogs.h>
#include <Menus.h>
#include <Windows.h>
#include <Fonts.h>
#include <Memory.h>
#include <stdio.h>
#endif

char CommandBuf[80];

int main(int argc, char *argv[])
{
	char *			File;
	char *			User;
	char *			Server=NULL;
	char *			Start;
	char *			End;
	LNNotesSession	Session;
	LNCalendar		Calendar;
	LNCalendarEntry	Entry;


#if defined MAC
	// On the Macintosh, we need to prompt for parameters
	// since they are not being passed in on the command line

	char	Filename[MAXPATH];
	char	Username[MAXPATH];
	char	Servername[MAXPATH];
	char	Startdate[MAXALPHATIMEDATE + 1];
	char	Enddate[MAXALPHATIMEDATE + 1];
	
	// Initialize the Macintosh toolbox
	InitGraf(&thePort); 
	InitFonts();
	InitWindows(); 
	InitDialogs(0);
	SetApplLimit(GetApplLimit()-8192); 
	MaxApplZone();
	MoreMasters(); 
	MoreMasters(); 
	MoreMasters();	

	User = Username;
	Server = Servername;
	Start = Startdate;
	End = Enddate;
	File = Filename;
	
	
	// Prompt for parameters since they are not being passed in on the command line.
	cout << endl << "Enter the file name for the calendar: " << flush;
	gets(File);
   	cout << endl << "Enter the calendar owners name: " << flush;
	gets(User);
 	cout << endl << "Enter start date for the appointment: " << flush;
	gets(Start);
	cout << endl << "Enter end date for the appointment:  " << flush;
	gets(End);
	cout << endl << "Enter server name:  " << flush;
	gets(Server);
	
#else
		// On all other platforms the parameters are entered on the command line

	// Check the command line.
	if (argc < 6) 
	{
		cout << "\nUsage:\n\t" << argv[0]
			<< " <filename> <username> <startdate> [<enddate>] [<server>] \n"
			<< endl;
		return(1); 
	}

	// Get info from command line.
	File = argv[1];
	User = argv[2];
	Start = argv[3];
	End = argv[4];
	Server = argv[5];
#endif


	// Set the error handler to throw all errors encountered during execution.
	LNSetThrowAllErrors(TRUE);

	try
	{
		LNDatetimeRange TheDate;
		LNText 			List;
		LNString 		DateString;
		LNString 		Desc;

		// Initialize the C++ API.
		Session.Init(argc, argv);

		// These must be done AFTER the session is initialized
		LNDatetime 		AptBegin ( Start );
		LNDatetime 		AptEnd (  End ) ;
	
		TheDate.SetBegin(AptBegin);
		TheDate.SetEnd(AptEnd);

		// Get a calendar
		Session.GetCalendar(&Calendar, Server, File, User);	

		cout << "Searching the file '" << File <<  "' on server '" << Server << "'..." << endl;

		// Check if a certain date is available
		if (Calendar.IsAvailable(TheDate))
		{
			// Create an appointment type entry for this date
			Calendar.CreateEntry(TheDate, "My appointment", LNCALENTRYTYPE_APPOINTMENT, &Entry);

			// Get the brief description and display it
			Desc = Entry.GetBriefDescription();
			cout << "The description that was set was: " << Desc << endl;

			// Get the date information and display it
			TheDate = Entry.GetDatetimeRange();
			TheDate.GetText(&DateString);
			cout << "The date that was set was: " << DateString << endl;
		
			// Save the entry
			Entry.Save();
		}
		else
			cout << "The date that you requested is not available" << endl;


	}

	// Error handler.  If an error occurred then get the text of
	// the error message and display it.
	catch (LNSTATUS lnerror)
	{
		char ErrorBuf[ERR_BUF_SIZE];
		LNGetErrorMessage(lnerror, ErrorBuf, ERR_BUF_SIZE);
		cout << "Error:  " << ErrorBuf << endl;
	}

	cout << "All Done.  Hit return to exit: ";
	cin.getline(CommandBuf, 50);
	

	// Terminate the API.
	Session.Term();

	return (0);
}
