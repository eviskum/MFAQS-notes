/****************************************************************************

    PROGRAM:    encrypt

    FILE:       encrypt.c

    SYNTAX:     encrypt  <database filename> <encryption key>

    PURPOSE:    Shows how to encrypt, decrypt, and encryption-enable data.

    DESCRIPTION:
        This program creates a document with a field that is encryption 
        enabled. It then creates a second document, encrypting the 
        encryption enabled field. The contents of the encryption enabled 
        field of each newly created document is then displayed (the 
        encrypted note is first decrypted).

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <ostime.h>
#include <stdnames.h>

#include <lapiplat.h>

/* Local function prototype */
STATUS DecryptAndReadNoteItem (DBHANDLE hDB, NOTEID dwNoteID, char *ItemName);
void  LNPUBLIC  ProcessArgs (int argc, char *argv[],
                               char *dbpath_name, char *ekey); 

#define ENCRYPTED_ITEM "SECRET"


/************************************************************************

    FUNCTION:   NotesMain/Main

    PURPOSE:    Lotus C API for Domino and Notes subroutine

    ALGORITHM:
      This creates a document and marks one of the fields in the
      document as encryption enabled by setting the ITEM_SEAL field flag.
      The data in this field is not encrypted.

      A second document is created similarly to the first document with the
      addition that the data in the encryption enabled field is encrypted
      with a personal key supplied on the command line. 

      The note id's for each of the two newly created documents are then
      displayed.  If the document has been encrypted, it is then decrypted. 
      The contents of the encryption enabled field is then displayed.

*************************************************************************/

LAPI_MAIN
{


   /* Local data declarations */

   char        PathName[MAXPATH]; /* pathname of database */
   char        EncryptKey[100];   /* name of personal encryption key */
   DBHANDLE    hDB;               /* database handle */
   NOTEHANDLE  hNote;             /* note handle */
   char        TextField[100];    /* contents of a text field */
   NUMBER      NumField = 1;      /* contents of a numeric field */
   TIMEDATE    TimeField;         /* contents of a time/date field */
   NOTEID      NoteID1, NoteID2;  /* note id's of the created documents */
   NOTEHANDLE  hEncryptedNote;    /* note handle of encrypted note */
   STATUS      error;             /* return code from API calls */


    LAPI_INIT(error);
    if (error)
      LAPI_INIT_ERROR;


   /* Get the pathname of the database. 
      Also get the personal encryption key name with which to encrypt the 
      document */

   ProcessArgs(argc, argv, PathName, EncryptKey); 

   /* Open the database. */

   if (error = NSFDbOpen (PathName, &hDB))
      LAPI_RETURN (ERR(error));

   /* Create the first data note. */

   if (error = NSFNoteCreate (hDB, &hNote))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a field named FORM to the note -- this field specifies the
      form to use when displaying the note. */

   if (error = NSFItemSetText ( hNote, 
               "FORM",
               "SimpleDataForm", 
               MAXWORD))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a text field named PLAIN_TEXT to the note. 
      Set the ITEM_SUMMARY flag so the field can be seen in a view. */

   strcpy (TextField, "This is an example of an encryption enabled document.");

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY,
         "PLAIN_TEXT", strlen("PLAIN_TEXT"),
         TYPE_TEXT,
         TextField, strlen(TextField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a numeric field named NUMBER to the note. 
      Set the ITEM_SUMMARY flag so the field can be seen in a view. */

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY,
         "NUMBER", strlen("NUMBER"),
         TYPE_NUMBER,
         &NumField, sizeof(NumField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }


   /* Write a time/date field named TIME_DATE to the note. 
      Set the ITEM_SUMMARY flag so the field can be seen in a view. */

   OSCurrentTIMEDATE(&TimeField);

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY,
         "TIME_DATE", strlen("TIME_DATE"),
         TYPE_TIME,
         &TimeField, sizeof(TimeField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a text field named, ENCRYPTED_ITEM, to the note. Set the 
      ITEM_SEAL flag so the field is encryption enabled.  */

   strcpy (TextField, "This is an encryption enabled field.  ");
   strcat (TextField, "The data, however, is not encrypted.");

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY | ITEM_SEAL,
         ENCRYPTED_ITEM, strlen(ENCRYPTED_ITEM),
         TYPE_TEXT,
         TextField, strlen(TextField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Add the entire new note (with all fields) to the database. */

   if (error = NSFNoteUpdate (hNote, 0))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Store the NOTEID.  It will be used later to read the encrypted
      enabled field. */

      NSFNoteGetInfo (hNote, _NOTE_ID, &NoteID1);

   if (error = NSFNoteClose (hNote))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Create a second note */

   if (error = NSFNoteCreate (hDB, &hNote))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a field named FORM to the note -- this field specifies the
      form to use when displaying the note. */

   if (error = NSFItemSetText ( hNote, 
               "FORM",
               "SimpleDataForm", 
               MAXWORD))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a text field named PLAIN_TEXT to the note. 
      Set the ITEM_SUMMARY flag so the field can be seen in a view. */

   strcpy (TextField, "This is an example of an encrypted document.");

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY,
         "PLAIN_TEXT", strlen("PLAIN_TEXT"),
         TYPE_TEXT,
         TextField, strlen(TextField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a numeric field named NUMBER to the note. 
      Set the ITEM_SUMMARY flag so the field can be seen in a view. */

   ++NumField;

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY,
         "NUMBER", strlen("NUMBER"),
         TYPE_NUMBER,
         &NumField, sizeof(NumField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a time/date field named TIME_DATE to the note. 
      Set the ITEM_SUMMARY flag so the field can be seen in a view. */

   OSCurrentTIMEDATE(&TimeField);

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY,
         "TIME_DATE", strlen("TIME_DATE"),
         TYPE_TIME,
         &TimeField, sizeof(TimeField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write a text field named, ENCRYPTED_ITEM to the note. Set the 
      ITEM_SEAL flag so the field is encryption enabled.  */

   strcpy (TextField, "This is an encryption enabled field.  ");
   strcat (TextField, "The data is encrypted.");

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY | ITEM_SEAL,
         ENCRYPTED_ITEM, strlen(ENCRYPTED_ITEM),
         TYPE_TEXT,
         TextField, strlen(TextField)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Write an item, ITEM_NAME_NOTE_SEALNAMES, to the note with the 
      personal encryption key name. This is an item of TYPE_TEXT
      with the ITEM_SUMMARY flag set. */

   if (error = NSFItemAppend (
         hNote,
         ITEM_SUMMARY,
         ITEM_NAME_NOTE_SEALNAMES, strlen(ITEM_NAME_NOTE_SEALNAMES),
         TYPE_TEXT,
         EncryptKey, strlen(EncryptKey)))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Encrypt the note */

   if (error = NSFNoteCopyAndEncrypt (hNote, 0, &hEncryptedNote))
   {
      NSFNoteClose (hNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   if (error = NSFNoteUpdate (hEncryptedNote, 0))
   {
      NSFNoteClose (hNote);
      NSFNoteClose (hEncryptedNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Store the NOTEID of this document.  It will be used later to
      decrypt and read the document. */

      NSFNoteGetInfo (hEncryptedNote, _NOTE_ID, &NoteID2);

   /* Close the notes. (Remove its structure from memory.) */

   if (error = NSFNoteClose (hNote))
   {
      NSFNoteClose (hEncryptedNote);
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   if (error = NSFNoteClose (hEncryptedNote))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Demonstrate reading encrypted fields. */

   if (error = DecryptAndReadNoteItem (hDB, NoteID1, ENCRYPTED_ITEM))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   if (error = DecryptAndReadNoteItem (hDB, NoteID2, ENCRYPTED_ITEM))
   {
      NSFDbClose (hDB);
      LAPI_RETURN (ERR(error));
   }

   /* Close the database */

   if (error = NSFDbClose (hDB))
      LAPI_RETURN (ERR(error));

/* End of subroutine. */
   printf("\nProgram completed successfully.\n");
   LAPI_RETURN (NOERROR);
}

/************************************************************************

    FUNCTION:   DecryptAndReadNoteItem

    PURPOSE:    Decrypt the note and print the note ID and a text field.
    
    ALGORITHM:
    This function opens the note with the specified NOTEID.  It tests 
    whether the note is encrypted.  If the note is encrypted, it decrypts 
    the note.  It then prints out the note id and the contents of the 
    specified text field.

    INPUTS:
        DBHANDLE    - Handle to the open database.
        dwNoteID    - Note id.
        ItemName    - Name of the text item to be read.

    RETURNS:
        status returned from an API call

*************************************************************************/

STATUS DecryptAndReadNoteItem (DBHANDLE hDB, NOTEID dwNoteID, char *ItemName)

{
   NOTEHANDLE hNote;           /* note handle */
   STATUS     error;           /* return code from API calls */
   FLAG       fSealed;         /* Is not encrypted? */
   BOOL       FieldFound;
    WORD          len;
    char          ItemText[500];


   if (error = NSFNoteOpen (
                            hDB,           /* database handle */
                            dwNoteID,      /* note id */
                            0,             /* open flags */
                           &hNote))        /* note handle (return) */
      
      return (error);

   /* If the note is encrypted, decrypt it. */

   if (NSFNoteIsSignedOrSealed (hNote, (BOOL far *) NULL, (BOOL far *) &fSealed) )
      if (fSealed)
         if (error = NSFNoteDecrypt (
                                     hNote,    /* note handle */
                                     0,        /* reserved */
                                     NULL))    /* Key for attachments - not
                                                  needed */
         {
            NSFNoteClose (hNote);
            return (error);
         }

   printf("\n\n\nNote ID:  %lX\n\n", dwNoteID);

   FieldFound = NSFItemIsPresent (hNote,
                                  ItemName,
                                  strlen (ItemName));

   if (FieldFound)
   {

      len = NSFItemGetText ( 
                            hNote, 
                            ItemName,
                            ItemText,
                            sizeof (ItemText));

      if (fSealed)
         printf ("The %s field has been decrypted.\n", ItemName);
      else
         printf ("The %s field is not encrypted.\n", ItemName);

      printf ("Contents of %s field:\n\n%s\n", ItemName, ItemText);

   }

   /* If the specified field is not there, print a message. */

   else
      printf ("%s field not found.\n", ItemName);

   return (NOERROR);
                     
}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line
   
    OUTPUTS:    dbname - server name obtained from command line or
                              from prompt.
                ekey -     	  personal encryption key
                              from prompt.

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[], 
                               char *dbname, char *ekey)
{ 
#ifndef MAC
    if (argc != 3)  
    {
#endif

        printf("Enter database name: ");      
        fflush (stdout);
        gets(dbname);
		  printf("\n");
		
        printf ("Enter encryption key:  ");
        fflush (stdout);
        gets(ekey);

#ifndef MAC
    }    
    else
    {
        strcpy(dbname, argv[1]);    
        strcpy(ekey, argv[2]);    
    } /* end if */
#endif
} /* ProcessArgs */
