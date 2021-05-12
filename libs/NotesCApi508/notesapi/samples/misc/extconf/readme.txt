(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
extconf - Extension manager replication conflict handler


PURPOSE:       
--------      
This Dynamic Link Library (DLL) demonstrates how to write an extension
manager replication conflict handler.  It intercepts the Domino 
notification that a replication conflict occurred.

When a replication conflict between two documents occurs in the
sample database, Conflict Handler, this extension manager examines each
item in the "newer" document.  If the item is the Payout field, it 
compares the value of this item with the one in the older document and 
saves the lower value.  For all other items, it determines whether there 
is a conflict between the two documents.  If there is a conflict, the 
newer item value is saved.  The extension manager then returns 
CONFLICT_ACTION_MERGE to the Lotus Domino Server so that the two 
documents will be merged and a Replication or Save Conflict document 
will not be posted.
  

ENVIRONMENTS
------------
Windows NT (32-bit) (including DEC Alpha)
Windows 95/98 (32-bit)


FILES:
------
extconf.c    - Extension manager entry point and callback.

extcwin.c    - Windows DLL code.

extconf.h    - Header file for sample program.

mswin32.mak  - Make file for Windows 32-bit.

mswin32.def  - DLL module definition file for Windows NT and Windows 95/98.

mswin32a.def - DLL module definition file for Windows NT on DEC Alpha.

readme.txt   - This file. Specifies what is needed to use this example.


USING EXTCONF
-------------

The name of the DLL depends on the platform.  The names used are:

        nextconf.dll            32-bit Windows (Windows NT and Windows 95/98)
        aextconf.dll            Windows NT on DEC Alpha

The DLL must be copied to the executable directory of the Lotus Domino
Server and to the executable directory of your workstation.

With the Lotus Domino Server and your workstation shut down, add the 
following line to notes.ini on the Lotus Domino Server and on your
workstation:

        EXTMGR_ADDINS=extconf

Bring up the Lotus Domino Server and bring up Notes on your workstation.
  
This sample program will run against the Domino database conflict.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  In order to 
enact a replication conflict, copy this file to the Domino data directory 
on a Lotus Domino Server.  Then, make a replica copy of this database on 
your local workstation.

From your workstation open the sample database on the server and edit the 
Customer Name and Payout fields of the document.  Save the document.  
Open the local replica copy of the sample database.  Edit the Payout 
field to be a higher value than the edit you made on the server.  Also 
change the Customer Name field using a different name than what is on the 
server's document.  Save the document.

Replicate the local database with the server.  When replication has 
completed open the database on the server.  Notice that there is no 
replication or save conflict document.  Also notice that the Payout field 
contains the lower of the two edited values.  The Customer Name field 
contains the newer of the two edited values.

