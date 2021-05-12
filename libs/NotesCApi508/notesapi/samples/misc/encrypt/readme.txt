(c) 1996-2001 Lotus Development Corporation.  All rights reserved.
This software is subject to the Lotus C API for Domino and Notes Software 
Development Kit Agreement (in the apilicns.txt file in the notesapi directory 
of this toolkit), Restricted Rights for U.S. government users, and applicable
export regulations.



PROGRAM
-------
encrypt  -  Shows how to encrypt and decrypt data.


ENVIRONMENTS
------------
OS/2 (32-bit)


FILES
-----------
readme.txt  -  This file. Specifies what is needed to use this example.

encrypt.c   -  Main program.

os2_32.mak   - Make file for OS/2 (32-bit).




RUNNING encrypt
---------------
- Under OS/2:  On the command line, type the full path and filename
  of this program.  You may also include the filename of the database
  and the name of the encryption key as command line arguments.  If
  no command line arguments are provided, the program will prompt for them.


EXAMPLE
-------
You need to first create an encryption key by selecting File-Tools-User ID 
then enter your password and in the dialog that comes up select encryption 
then click the new button and name your key EncKey1.

      encrypt  encrypt  EncKey1

Upon executing this command, encrypt will create in the database
'encrypt.nsf' a document containing fields of several different types.  
The field named "SECRET" will be encryption enabled but not encrypted.
A second document will be created.  This document will encrypt the
field named "SECRET".  The note id's and the contents of the "SECRET" 
field for each document created will then be printed.

The program will print out on the screen the following:

Note ID:  2136

The SECRET field is not encrypted.
Contents of SECRET field:

This is an encryption enabled field.  The data, however, is not encrypted.



Note ID:  213A

The SECRET field has been decrypted.
Contents of SECRET field:

This is an encryption enabled field.  The data is encrypted.

CHECKING THE RESULTS
--------------------
Open the database 'encrypt.nsf'

Highlight the first document that was just created.

Choose File-Document Properties
      
Highlight the field named "secret" on the field tab.  This will
display the data type of the data in that field, the length of the
data, the actual data itself, and the field flags that are set for
that field.  See that "SEAL"  is one of the Field flags set.  This  
signifies that encryption is enabled for that field. 

Open the second document that was just created.  Notice the
message, "Decrypting Document..." that appears in the status
bar while the document is being opened.  Choose 
File-Document Properties... and notice that on the fields tab, 
$SEAL and SecretEncryptionKeys appear in the Field listbox.

If another user who does not have the personal encryption key opens
this same document, then this user will not be able to read the 
contents of the encrypted field. Also, if File-Document Properties
is chosen, on the fields tab, $SEAL, $SEALDATA and SecretEncryptionKeys
appear in the Field listbox.
      

