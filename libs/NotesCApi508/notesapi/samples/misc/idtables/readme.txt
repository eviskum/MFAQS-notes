(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
idtables - Sample Lotus C API for Domino and Notes Program: 
	       Delete, Touch and Set Categories


PURPOSE   
-------   
This program shows how to use ID Tables to delete, touch, archive, and
categorize documents in Domino databases.


ENVIRONMENT
-----------
OS/2 (32-bit)


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

idtables.c   - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).

RUNNING idtables
----------------
Copy the sample databases, "id.nsf" and "id_arc.nsf", to the Domino data
directory on your system.  From the Notes user interface, add the database's
icon to your Notes workspace.

- Under OS/2:
  type the following at the system command prompt:


    idtables  -Sdb_name -action [-Bbegin (n) days ago] 
		    [-Ncategory] [-Aarchive_name]

	action:
		T  touch selected document's last modified date.
		D  delete selected documents.
		C  stamp selected documents with a given category value.
	options:
		B  begin document selection (n) days ago.
		N  new category string. Use with 'C' action.
		A  database to act as archive for deleted documents.


Use the -S parameter to specify the database. It should take the form:

-Sdb_name        - name of the Domino database to be modified


Specify only one of the three actions: -T (Touching documents), 
-D (Delete documents) & -C (set a Category). 

Touching documents, the -T option

	idtables -Sdb_name -T [-Bbegin days ago]


Deleting documents, the -D option

	idtables -Sdb_name -D [-Bbegin days ago] [-Aarchive_name]


Setting a category in a document, the -C option

	idtables -Sdb_name -C [-Bbegin days ago] [-Ncategory]



Specifying Options:

There are three optional parameters. They are -B (Begin selecting n 
days ago), -A (Archive deleted documents to this database) and -N (New 
category to set).

-Bbegin days ago - number of days back from today to start selecting 
                   documents.  This option may be used on any of the 
                   three actions. If not specified then all documents 
                   are selected.

-Aarchive_name   - database to put all deleted documents into.

-Ncategory       - category to set in each selected document.


EXAMPLES
========

EXAMPLE Using the -T option
---------------------------

	idtables -Sid.nsf -T -B365

Touch the Modified Date & Time field in each document of the id.nsf 
database that has been modified since 365 days ago.


Here is an example of what idtables.exe may display:
----------------------------------------------------
You have selected documents in id.nsf from:
	Begin date: 02/03/1999 01:02:42 PM EST through
	End date  : 02/03/2000 01:02:42 PM EST

ID Table Flags = 0001
ID Table size: 23
Number of entries in ID Table = 3 will be considered for touching.
Modified Time/Date = 02/03/2000 01:02:42 PM EST

Analysis of documents between begin & end:
	# of entries in ID Table  = 3
	# of deletion stubs      = 0
	# of touched documents   = 3

All Done!

Program completed successfully.
------------------------------------------


CHECKING THE RESULTS
--------------------
Check to see if the displayed results from idtables.exe indicate that 
any documents were touched (see the value on the line that reads "# of 
Touched Documents = ").  If no documents were touched, try running 
idtables.exe with no -B option.

In Notes, open id.nsf.  The Modified column in the All Docs view should
reflect the date and time for newly touched documents.



EXAMPLE Using the -C Option
---------------------------

	idtables -Sid.nsf -C -B1 -NEarth

Set the Category field to Earth of the documents of id.nsf that have 
been modified in the past 1 day. Also set the Modified Date & Time 
field in each selected document. If no field named Category exists, add 
a new field called Category and set it to Earth.

Here is an example of what idtables.exe may display:
--------------------------------------------------
You have selected documents in id.nsf from:
	Begin date: 02/02/2000 01:13:48 PM EST through
	End date  : 02/03/2000 01:13:48 PM EST

ID Table Flags = 0001
ID Table size: 23
Number of entries in ID Table = 3 will be considered for stamping.

Analysis of documents between begin & end:
	# of entries in ID Table  = 3
	# of deletion stubs       = 0
	# of stamped documents    = 3

All Done!

Program completed successfully.
--------------------------------------------------


CHECKING THE RESULTS
--------------------
Check to see if the displayed results from idtables.exe indicate that any
documents were Stamped (see the line that reads "# of Stamped 
documents = ").  If no documents were stamped, try running idtables.exe 
with no -B option.

In Notes, open id.nsf.  The Category column of the All Docs view should
have the value "Earth", for the documents that have been stamped, since 
that is the parameter we supplied on the command line.  In addition, the
Modified column in the All Docs view should reflect the date and time
these documents were stamped.



EXAMPLE Using The -D Option
---------------------------

	idtables -Sid.nsf -D -B23 -Aid_arc.nsf

Delete all the documents of the id.nsf database that have been modified in the
past 23 days. Copy the documents to be deleted into the id_arc.nsf database.


Here is an example of what idtables.exe may display:
----------------------------------------------
You have selected documents in id.nsf from:
	Begin date: 01/11/2000 01:18:19 PM EST through
	End date  : 02/03/2000 01:18:19 PM EST

ID Table Flags = 0001
ID Table size: 23
Number of entries in ID Table = 3 will be considered for deletion

Analysis of documents between begin & end:
	# of entries in ID Table  = 3
	# of entries in arc table = 3
	# of deletion stubs       = 0
	# of invalid documents    = 0

Archived 3 documents in id_arc.nsf

Deleted 3 documents in id.nsf

All Done!

Program completed successfully.
----------------------------------------------

CHECKING THE RESULTS
--------------------
Check to see if the displayed results from idtables.exe indicate that any
documents were deleted (see the line that reads "Deleted: xxx documents in
id.nsf").  If no documents were deleted, try running idtables.exe with no
-B option.

In Notes, open id.nsf.  There should be as many documents missing as are
indicated as having been deleted.

In Notes, open id_arc.nsf (the Archive database).  There should be as many
documents added as are indicated as having been archived.

After deleting records from a test database, it is a good idea to refresh the
database to its original state by using Notes to do a File - Database -
New Copy of the original database to the Domino data directory.  Likewise, to
rerun idtables.exe with the -A option again, it may be a good idea to delete
the documents in the archive database.

