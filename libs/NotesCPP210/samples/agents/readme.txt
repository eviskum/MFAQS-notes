(c) 1998-2000 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus Notes C++ API Software 
Development Kit Agreement (in the apilicns.txt file in the 
notescpp directory of this toolkit), Restricted Rights for U.S. 
government users, and applicable export regulations.


PROGRAMS
--------

AGENTS -  Illustrates how to create a few Release 5 agent notes.

RAGENTS - Illustrates how to execute Release 5 agents.


ENVIRONMENTS
------------
Sample makefiles are provided for the following environments:

        Windows NT (32-bit)
	Windows 95 (32-bit)
	IBM VisualAge C++ for Win32
	HP HP-UX
	IBM AIX
	Sun Solaris SPARC Edition
	Sun Solaris Intel Edition
        Linux on Intel platforms


FILES
-----
mswin32.mak     - Make file for Windows NT (32-bit) 
                  and Windows 95 (32-bit) using Microsoft Visual C++.

ibmwin32.mak    - Make file for Windows NT (32-bit) and Windows 95 
                  (32-bit) using IBM VisualAge C++ for Windows.

borwin32.mak    - Make file for Windows NT (32-bit) and Windows 95 
                  (32-bit) using Borland C++ for Windows.

hp.mak          - Make file for HP-UX.               

sol_2x.mak      - Make file for Sun Solaris SPARC Edition.

sol_x86.mak     - Make file for Sun Solaris Intel Edition.

aix.mak         - Make file for IBM AIX.

linux.mak       - Make file for Linux on Intel platform.

hp.mak          - Make file for HP-UX.               

sol_2x.mak      - Make file for Sun Solaris SPARC Edition.

sol_x86.mak     - Make file for Sun Solaris Intel Edition.

aix.mak         - Make file for IBM AIX.

linux.mak       - Make file for Linux on Intel platform.

agents.cpp      - Main program to create Release 5 agent notes.

ragents.cpp     - Main program that executes the newly created Release 5
                  agents.

problems.nsf    - Sample Notes database (in NOTEDATA directory).

agents.ref      - Reference sample output log file.

HotAgent.java   - Java Agent source code.

HotAgent.class  - Java Agent class file. 

readme.txt      - This file.  Specifies what is needed to use this 
                  example.


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
	executed manually or as a background agent, it assigns default 
	"Isabel Silton" to all open, problem documents that do not have an 
	assigned Support Rep. When this agent is executed programmatically, 
	by RAGENTS program, it uses Parameter Document to set a different 
	name ("Sandy Block".)

3)"Decrease Priority"
	This agent is an enabled, shared, scheduled, formula based agent 
	that runs against selected documents in the database dayly, at 1AM.
	When executed, it decreases the Priority value of all open problems 
	created on the previous day by one level.

4)"Assign Hot Problems" 
	This agent is a manual (menu command), shared, java agent that runs 
	against all documents. When executed, it assigns "Fire Fighters"
	as the Support Rep to all problem documents that have an "Open" Status 
	and "High" Priority.

RAGENTS

This sample executes the "Assign Support Rep" and "Decrease Priority" agents
created by agents.exe and displays and logs the results.


BEFORE BUILDING THIS SAMPLE
---------------------------
If you installed the PC version of the toolkit using a version of PKUNZIP that
does not support long filenames, you'll need to rename the file HotAgent.cla
to HotAgent.class, and hotagent.jav to HotAgent.java.


BEFORE RUNNING THIS SAMPLE
---------------------------
This sample uses the problems.nsf sample database that is included
in the NOTEDATA directory of the C++ API toolkit. Copy this file to
the Notes data directory.

Before running this sample, open the database from Notes and
perform the following preparatory steps:

1) From the Main View create a new Problem document with an empty
   Support Rep field value, and set its Priority to "High".

2) Edit a number of existing Problem documents clearing the Support Rep field.


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

2) Go into Notes Designer and open the Problem Tracking database (problems.nsf). 
   Look at the Agents view. The four agents just created, "Decrease Priority," "Send
   Reminder to Support Rep," "Assign Support Rep," and "Assign Hot Problems"
   will be listed. 
   
   Note: You will find also "Default Agent with Lotus Script" which
   is included with the database and used solely as a repository of 
   the Lotus Script code.

3) Run the RAGENTS program by typing 'ragents' at the command prompt,
   followed by the optional server name. If no server name is specified, 
   it is assumed being local:

       ragents [optional server name]

   This program will execute two of the four agents just created:  "Assign
   Support Rep" and "Decrease Priority."


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
   assigned Support Rep now has a Support Rep value of "Sandy Block."  
   This validates the "Assign Support Rep" agent execution. 

3) From the Main View, notice that the newly created problem previously 
   assigned "High" Priority now have "Medium" Priority. 
   This validates the "Decrease Priority" agent execution. 

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

7) Likewise, the scheduled "Decrease Priority" agent is enabled, and will 
   execute "On Schedule" at 1AM every day.

8) Lastly, all of the agents can be viewed and edited when selected from the 
   Agents view. You can verify the different attributes of the agent notes from
   this interface.
