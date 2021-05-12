(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAMS
--------
AGENTS -  Illustrates how to create various agent notes.


RAGENTS - Illustrates how to execute agent notes.


ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)
IBM AIX
HP HP-UX
SPARC Solaris
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt  - This file. Specifies what is needed to use this sample.
                   
agents.c    - Main program to create agent notes.

ragents.c   - Main program that executes the newly created agent notes.

mswin32.mak - Make file for Windows 32-bit.

aix.mak     - Make file for IBM AIX.

hp.mak      - Make file for HP HP-UX.

sol_2x.mak  - Make file for Solaris SPARC Edition.

sol_x86.mak - Make file for Solaris Intel Edition.

linux.mak   - Make file for Linux RedHat.

agents.ref  - Reference sample output log file. 

HotAgent.java  - Java Agent source file.

HotAgent.class - Java Agent executable file. 



DESCRIPTION
-----------

AGENTS

This sample creates the following four agent notes in the sample
database, problems.nsf, which is included with the toolkit. 

1)"Send Reminder to Support Rep"
        This agent is a manual (menu command), shared, Formula agent that 
        runs against the currently selected documents.  When executed, it 
        will send a mail message, with doclink, to the "Support Reps" of 
        the selected documents in the view. 
        
2)"Assign Support Rep"  
        This agent is a disabled, private, background LotusScript agent 
        triggered and run against new and/or modified documents.  When 
        executed, it assigns "Isabel Silton" to all open, problem documents
        that do not have an assigned Support Rep.

3)"Escalate Priority"
        This agent is an enabled, shared, scheduled, Formula based agent 
        that runs against all documents in the database at 1AM on the 
        first day of each month.  When executed, it increases the Priority 
        level of all problems that have been opened for over a month. 

4)"Assign Hot Problems" 
        This agent is a manual (menu command), shared, Java agent that runs 
        against all documents.  When executed, it assigns "Fire Fighters"
        as the Support Rep to all problem documents that have an "Open" Status 
        and "High" Priority.


RAGENTS

This sample executes the "Assign Support Rep" and "Escalate Priority" agents
created by agents.exe and displays the results.


BEFORE BUILDING THIS SAMPLE
---------------------------
Before building this sample, edit the variable "szCode" in the
AddJavaAgent function in agents.c to reflect the current path of
your agents sample.  Note: The Java Agent directory path is hardcoded
in the source and must reside on the current system you run the sample from.


BEFORE RUNNING THIS SAMPLE
---------------------------
This sample uses the problems.nsf sample database that is included
with the API toolkit.   Use OS commands or a Notes client to create a copy
of this database in the Domino or Notes data directory.

Before running this sample, open the database from a Notes client and
perform the following preparatory steps:

1) From the Main View either create a Problem document with an empty
Support Rep field value, or edit an existing Problem document and clear 
the Support Rep assignment.  

2) From the Main View visually note which of the problems have Low and
Medium priorities.


RUNNING AGENTS and RAGENTS:
---------------------------
1) From the system command prompt, in the directory for the AGENTS
sample, type the following command:

  agents problems

If your user id is password protected, you will be required to type in 
the password.

This program will create the agents mentioned above.

2) From the system command prompt, in the directory for the AGENTS 
sample, type the following command: 


    ragents problems


This program will execute two of the agents just created:  Assign
Support Rep and Escalate Priority.


CHECKING THE RESULTS
--------------------
1) ragents writes to the agents.log output log file.  If no errors
occur during execution, this file contains a trace of the execution 
results and run information for the two triggered agents.   Any errors 
that occur during execution will be displayed to the console output.  
The file, agents.ref, which is included in the directory of the sample, 
contains a reference for the output log.  Use this file to compare with 
and validate the trace results in agents.log.

2) Open the Problem Tracking database (problems.nsf) and from the Main 
View notice that the Problem document you had set up to not have an 
assigned Support Rep now has a Support Rep value of "Isabel Silton".  
This validates the "Assign Support Rep" agent execution.  

3) From the Main View, notice that the problems that are over one month
old and were previously assigned "Low" Priority now have "Medium" Priority, 
and those previously assigned "Medium" now have "High".  This validates the 
"Escalate Priority" agent execution.  

4) To validate the "Send Reminder to Support Rep" agent note:
        - Verify that it is available for selection from the Actions menu.
        - From the Main View modify the Support Rep value of one 
          Problem document by assigning it your name.  Save the
          document, select the document, and execute the agent from the
          Actions menu.  After the agent executes, an execution log 
          dialog is returned, and you will receive mail containing a doclink 
          to the Problem from the agent.

5) To validate the "Assign Hot Problems" agent note:
        - Verify that it is available for selection from the Actions menu.
        - From the Main View execute the agent from the actions menu.
          Verify all problem documents with an "Open" Status and "High" 
          Priority have their Support Rep changed to "Fire Fighters".

6) All of the added agents can be reexecuted, as appropriate, from the
Actions menu of either the Main View or from Domino Designer's Agents View.

7) You can enable background execution of the "Assign Support Rep" agent
by first enabling the agent from Domino Designer's Agents view, and then 
modifying or adding a document to the database.  Any documents that were 
not assigned a Support Rep should get updated the next time the local Agent 
Manager runs.
(Note that when running on a Notes client, the "Enable scheduled local 
agents" check box seen from the User Preferences screen must be checked).

8) Likewise, the scheduled "Escalate Priority" agent is enabled, and will 
execute "On Schedule" at 1AM on the first day of the next month.

9) Lastly, all of the agents can be viewed and edited when selected from the 
Agents view in Domino Designer.  You can verify the different attributes of
the agent notes from this interface.  

