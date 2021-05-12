(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory of
this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.


PROGRAM
-------
acls - Sample Lotus C API for Domino and Notes Program: 
       demonstrates the Access Control List routines.

PURPOSE
-------       
This program first reads into memory the Access Control List (ACL)
of the database specified in the command line, and then creates
a role.  Then, the program manipulates the ACL of three users and
a group in the following sequence:

1. user 1 : This is the user specified on the command line.  He is added
            to the ACL with Manager access level, and is granted the 
            newly added Role.

   user 2 : user 2 is added to the ACL with Author access level,
            his access level privilege is further refined so he will
            be unable to create documents and unable to delete
            documents.

   user 3 : user 3 is added to the ACL with Designer access level.

   The information from the Access Control List is then printed.
 
2. group 1: group 1 is added to the ACL with Designer access level.

   user 3 : user 3 is deleted from ACL with the assumption that he
            is a member of the newly added group.

   user 2 : user 2's ACL is modified to Editor access level, and
            his access level privilege is refined, so he will be
            unable to delete documents.

   default user: default user's access level is modified to Reader.

   The information from the Access Control List is then printed 
   again.

3. ACLLookupAccess is then demonstrated, for the first user (the
   manager) and user 3 who belongs to a group specified in the ACL.

4. The ACL is stored in the database.


ENVIRONMENTS
------------   
OS/2 (32-bit)
HP HP-UX
IBM AIX
Solaris SPARC Edition
Solaris Intel Edition
Linux RedHat


FILES
-----
readme.txt   - This file. Specifies what is needed to use this example.

acls.c       - Main program.

os2_32.mak   - Make file for OS/2 (32-bit).

aix.mak      - Make file for IBM AIX.

hp.mak       - Make file for HP HP-UX.

sol_2x.mak   - Make file for Solaris SPARC Edition.

sol_x86.mak  - Make file for Solaris Intel Edition.

linux.mak    - Make file for Linux RedHat.


RUNNING acls:
-------------
This sample program will run against the Domino database acls.nsf,
provided with the Lotus C API for Domino and Notes toolkit.  
You must copy this file to the Domino data directory before 
running this program.


- Under OS/2 and UNIX (AIX, HP-UX, Linux and Solaris)
  type the following at the system command prompt:

  acls <database> <ManagerName>

  where:

  <database>    is the database to operate on.
  <ManagerName> is the name of the Manager to be added to the ACL.  This
                name is likely to have spaces so put it in quotation marks.

  for example:

  acls acls "Dee Manager"



EXAMPLE:
--------
If you use acls.nsf for the database and Dee Manager for the Manager Name,
the program will print the following to the screen:



*** ACL info after the first set of changes ***

                    Access Level/
Name                Privileges           Roles
----------          -------------        ----------

-Default-           Manager             


Jayne Doe           Designer            


Johnny Doe          Author              
                    Cannot create docs.
                    Cannot delete docs.


Dee Manager         Manager             [Marketing]
                                        


*** ACL info after the second set of changes ***

                    Access Level/
Name                Privileges           Roles
----------          -------------        ----------

-Default-           Reader              


Dev Team            Designer            


Johnny Doe          Editor              
                    Cannot delete docs.


Dee Manager         Manager             [Marketing]
                                        




*** "Dee Manager" ACL info from ACLLookupAccess function ***

Dee Manager has the following access:
      Access Level:  Manager
      Roles: [Marketing]


*** "Jayne Doe" ACL info from ACLLookupAccess function ***

Jayne Doe has the following access:
      Access Level:  Designer


Program completed successfully.



CHECKING THE RESULTS
--------------------

To see the revised ACL in the database:

In Notes, select or open ACLS.NSF.

Choose File, Database, Access Control.

Examine the Access Control List.

