(c) 1998 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software Development
Kit Agreement, Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAMS
--------

AGENTS -  Illustrates how to create a few Release 4 agent notes.

RAGENTS - Illustrates how to execute Release 4 agent notes.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95 (32-bit)
AIX IBM
HP HP-UX
SPARC Solaris
Solaris Intel Edition


FILES
-----
readme.txt      - This file. Specifies what is needed to use this sample.
		   
agents.cpp      - Main program to create Release 4 agent notes.

ragents.cpp     - Main program that executes the newly created Release 4
                  agent notes.

mswin32.mak     - Make file for MS-Windows (32-bit).

aix.mak         - Make file for IBM AIX.

hp.mak          - Make file for HP HP-UX.

sol_2x.mak      - Make file for SPARC Solaris.

sol_x86.mak     - Make file for Solaris Intel Edition.

problems.nsf    - Sample Notes database (in NOTEDATA directory).

agents.ref      - Reference sample output log file.

hotagent.j      - Java Agent source code.

HotAgent.class  - Java Agent class file. 


DESCRIPTION
-----------

AGENTS

This sample creates the following four agent notes in the sample
database, problems.nsf, which is included with the toolkit.  

1)"Send Reminder to Support Rep"
	This agent is a manual (menu command), shared, Actions agent that 
	runs against the currently selected documents. When executed, it 
	will send a mail message, with doclink, to the "Support Reps" of 
	the selected documents in the view. 
	
2)"Assign Support Rep"  
	This agent is a disabled, shared, background LotusScript agent 
	triggered and run against new and/or modified documents. When 
	executed, it assigns "Isabel Silton" to all open, problem documents
	that do not have an assigned Support Rep.

3)"Escalate Priority"
	This agent is an enabled, shared, scheduled, Formula based agent 
	that runs against selected documents in the database at 1AM on the 
	first day of each month. When executed, it increases the Priority 
	value of all open problems one level.

4)"Assign Hot Problems" 
	This agent is a manual (menu command), shared, Java agent that runs 
	against all documents. When executed, it assigns "Fire Fighters"
	as the Support Rep to all problem documents that have an "Open" Status 
	and "High" Priority.

RAGENTS

This sample executes the "Assign Support Rep" and "Escalate Priority" agents
created by agents.exe and displays the results.


BEFORE BUILDING THIS SAMPLE
---------------------------
If you installed the PC version of the toolkit using a version of PKUNZIP that
does not support long filenames, you'll need to rename the file hotagent.cla
to HotAgent.class before running the sample.


BEFORE RUNNING THIS SAMPLE
---------------------------
This sample uses the problems.nsf sample database that is included
in the NOTEDATA directory of the C++ API toolkit. Copy this file to
the Notes data directory.

Before running this sample, open the database from Notes and
perform the following preparatory steps:

1) From the Main View either create a Problem document with an empty
   Support Rep field value, or edit an existing Problem document and clear 
   the Support Rep assignment. 

2) From the Main View visually note which of the problems have Low and
   Medium priorities.


RUNNING AGENTS and RAGENTS:
---------------------------
1) Run the AGENTS program, by typing 'agents' at the command prompt, followed
   by the name of the sample directory and an optional server name. If no
   server name is specified, the database problems.nsf in the local Notes data
   directory is used.

   For example, on PC platforms, if you installed the C++ API toolkit in
   c:\notescpp, you could run the program as follows:

      agents c:\notescpp\samples\agents

   If your Notes id is password protected, you will be required to type in 
   the password.

   This program will create the four agent notes.

2) Go into Notes and open the Problem Tracking database (problems.nsf). Look at
   the Agents view. The four agents just created, "Escalate Priority," "Send
   Reminder to Support Rep," "Assign Support Rep," and "Assign Hot Problems"
   will be listed. Switch back to the Main View and close the database.

   Due to a current limitation with the creation and subsequent execution
   of a LotusScript Agent using the Notes API, you must open the Problem
   Tracking database and open the Agents view before running the "Assign
   Support Rep" agent from the RAGENTS program. This limitation will be
   addressed in a future release of Notes.

3) Run the RAGENTS program by typing 'ragents' at the command prompt:

       ragents

   There are no parameters.

   This program will execute two of the four agents just created:  "Assign
   Support Rep" and "Escalate Priority."


CHECKING THE RESULTS
--------------------
1) RAGENTS writes to the agents.log output log file. If no errors
   occur during execution, this file contains a trace of the execution 
   results and run information for the two triggered agents. Any errors 
   that occur during execution will be displayed to the console output. 
   The file, agents.ref, which is included in the directory of the sample, 
   contains a reference for the output log. Use this file to compare with 
   and validate the trace results in agents.log.

2) Open the Problem Tracking database (problems.nsf) and from the Main 
   View notice that the Problem document you had set up to not have an 
   assigned Support Rep now has a Support Rep value of "Isabel Silton."  
   This validates the "Assign Support Rep" agent execution. 

3) From the Main View, notice that the problems previously assigned "Low"
   Priority now have "Medium" Priority, and those previously assigned 
   "Medium" now have "High."  This validates the "Escalate Priority" agent
   execution. 

4) To validate the "Send Reminder to Support Rep" agent note:
	- Verify that it is available for selection from the Actions menu.
	- From the Main View modify the Support Rep value of one 
	  Problem document by assigning it your name. Save the
	  document, select the document, and execute the agent from the
	  Actions menu. After the agent executes, an execution log 
	  dialog is returned from Notes, and you will receive mail 
	  containing a doclink to the Problem from the agent.

5) To validate the "Assign Hot Problems" agent note:
	- Verify that it is available for selection from the Actions menu.
	- From the Main View execute the agent from the actions menu.
	  Verify all problem documents with an "Open" Status and "High" 
	  Priority have their Support Rep changed to "Fire Fighters."

5) All of the added agents can be reexecuted, as appropriate, from the
   Actions menu of either the Main View or the Agents View.

6) You can enable background execution of the "Assign Support Rep" agent
   by first enabling the agent from the Agents view, and then modifying or 
   adding a document to the database. Any documents that were not assigned
   a Support Rep should get updated the next time the local Agent Manager runs
   (Note that the "enable scheduled local agents" must be configured from the
   User Preferences of the Workstation).

7) Likewise, the scheduled "Escalate Priority" agent is enabled, and will 
   execute "On Schedule" at 1AM on the first day of the next month.

8) Lastly, all of the agents can be viewed and edited when selected from the 
   Agents view. You can verify the different attributes of the agent notes from
   this interface. Due to current limitations with the API support for the 
   LotusScript IDE with Notes, you will NOT be able to update the LotusScript 
   source of the "Assign Support Rep" agent. Instead, an error message will be
   displayed when exiting the Agents edit UI.
