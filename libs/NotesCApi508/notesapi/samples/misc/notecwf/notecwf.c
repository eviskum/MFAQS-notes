/****************************************************************************

    PROGRAM:    NoteCWF

    FILE:       Notecwf.c

    SYNTAX:     Notecwf  <database filename>

    PURPOSE:    Create a new data note, set input fields, and generate
                            computed fields via NSFNotesComputeWithForm

****************************************************************************/

/* OS and C include files */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Lotus C API for Domino and Notes include files */

#include <lapicinc.h>

#include <global.h>
#include <stdnames.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <editods.h>
#include <osmem.h>

#include <lapiplat.h>

/* Function prototypes */
void PromptValues(NUMBER *, NUMBER *);              /* user input routine */
void DisplayValues(NUMBER, NUMBER, NUMBER, NUMBER); /* display routine */ 

/* CWF_ERROR_PROC callback function */
STATUS LNPUBLIC CWFCallback (const void *pCDField, WORD phase, STATUS error, 
                            HANDLE ErrorText, WORD wErrorTextSize,
                            void *Ctx);

/* Function prototypes for local functions */
void  LNPUBLIC  ProcessArgs (int argc, char *argv[]);

/* global constants */
#define IO_LENGTH  256  /* user input, display output line length */

NUMBER  width;          /* input width field data */    
NUMBER  length;         /* input length field data */
 
/************************************************************************

    FUNCTION:   NotesMain

*************************************************************************/

LAPI_MAIN
{

/* Local constants */

/* Local type definitions */

/* Local data declarations */
    char        *path_name;     /* pathname of database */
    DBHANDLE    db_handle;      /* database handle */
    NOTEHANDLE  note_handle;    /* note handle */

    NUMBER  perimeter;      /* computed perimeter field data */
    NUMBER  area;           /* computed area field data */
    NUMBER  temp_val;       /* passed field value to API */

    STATUS  error=0;        /* return code from API calls */

    LAPI_INIT(error)
    if (error)
        LAPI_INIT_ERROR;

/* Get the pathname of the database (Compute.nsf). */
    path_name = (char *) malloc(IO_LENGTH);
    if (path_name == NULL)
       {
        printf("Error: Out of memory.\n");
        LAPI_RETURN (NOERROR);
       }

    printf("Enter the database filename: ");
    fflush(stdout);
    gets(path_name);

/* Open the database. */
    if (error = NSFDbOpen (path_name, &db_handle))
        LAPI_RETURN (ERR(error));

/* Finished with database name. */
    free(path_name);

    /* Create a note and add all input data to it. */
        if (error = NSFNoteCreate (db_handle, &note_handle))
    {
        NSFDbClose (db_handle);
        LAPI_RETURN (ERR(error));
    }

    /* process command line arguments or prompt for user input */
    ProcessArgs(argc, argv);


/* Set the input data measurement */
    temp_val = (NUMBER) length;
    if (error = NSFItemSetNumber (note_handle, "Length", &temp_val))
        goto Item_Error;

    temp_val = (NUMBER) width;
    if (error = NSFItemSetNumber (note_handle, "Width", &temp_val))
        goto Item_Error;

/* Call NSFNoteComputeWithForm to 
 * 1) ensure that input measurement data is valid, or flag error in callback
 * 2) compute the output measurement data, or flag error in callback
 */
    if (error = NSFNoteComputeWithForm (note_handle, NULLHANDLE, (DWORD) 0,
                                        CWFCallback, NULL))
        goto Item_Error;

/* No error; get entered and computed field values and display measurement 
summary */
    if (NSFItemGetNumber (note_handle, "Length", &length) == FALSE)
        goto Item_Error;
    if (NSFItemGetNumber (note_handle, "Width", &width) == FALSE)
        goto Item_Error;
    if (NSFItemGetNumber (note_handle, "Perimeter", &perimeter) == FALSE)
        goto Item_Error;
    if (NSFItemGetNumber (note_handle, "Area", &area) == FALSE)
        goto Item_Error;
    DisplayValues(length, width, perimeter, area);

/* Update the note. */
    if (error = NSFNoteUpdate (note_handle, 0))
        goto Item_Error;

Item_Error:
/* Close the note. */
    NSFNoteClose (note_handle);
 
/* Close Db and return last status. */
    NSFDbClose (db_handle);
    LAPI_RETURN (ERR(error));
}

/************************************************************************
 
    FUNCTION:   ProcessArgs
 
    INPUTS:     argc, argv - directly from the command line
 
    OUTPUTS:    Length, Width - data from the command line.
 
*************************************************************************/
 
void  LNPUBLIC  ProcessArgs (int argc, char *argv[])
                               
{
        /* Prompt for input data. */
        PromptValues(&length, &width);
} /* ProcessArgs */



/************************************************************************

    FUNCTION:   PromptValues

    PURPOSE:    Prompt user for input measurement values

*************************************************************************/
void PromptValues(NUMBER *length, NUMBER *width)
{
        printf("\nEnter Rectangle Measurment Values:\n");
        
        printf("\tLength (l): ");
        scanf("\n%lf", length);
        fflush(stdin);
        
        printf("\tWidth (w): ");
        scanf("\n%lf", width);
    
        printf("\n");

/* Note: Non numeric entries will be converted to floating point by using 
 *       scanf().  For these input, since the resulting value is always less 
 *       than .01, the sample database field formulas will flag an invalid
 *       input during the call to NSFNoteComputeWithForm.   
 *       In general, the input values should be validated programatically.
 */ 

    return;
}


/************************************************************************

    FUNCTION:   DisplayValues

    PURPOSE:    Display measurement value summary to the console

*************************************************************************/
void DisplayValues(NUMBER length, NUMBER width, NUMBER perimeter, NUMBER area)
{
        printf("\nRectangle Measurement Value Summary:");
        
        printf("\n\tLength (l): %.2lf", length);
        printf("\n\tWidth (w): %.2lf", width);
        printf("\n\tPerimeter (2l+2w): %.2lf", perimeter);
        printf("\n\tArea (lw): %.4lf", area);
        
        printf("\n");
        return;
}


/************************************************************************

    FUNCTION:   CWFCallback

    PURPOSE:    NSFNoteComputeWithForm error callback function

*************************************************************************/

STATUS LNPUBLIC CWFCallback(
   const void *pCDField,
   WORD phase,
   STATUS error, 
   HANDLE ErrorText,
   WORD wErrorTextSize,
   void *Ctx)
{
   char    *ptr = (char *) pCDField;
   CDFIELD  field;
   char     name[IO_LENGTH];    /*field name*/
   BYTE    *pErrText;
   char     ErrTextBuf[IO_LENGTH];
   int      i;
   int      bufPos;

   /* Build field value/phase error string */
   printf ("***NSFNoteComputeWithForm ERROR***\n"); 

   /* Point to the field name by moving past the CDFIELD structure, 
      then copy its value */
   ODSReadMemory(&ptr, _CDFIELD, &field, 1 );
   strncpy(name, ptr + field.DVLength + field.ITLength + field.IVLength, 
           field.NameLength);
   name[field.NameLength] = '\0';
   printf ("\tField Name: %s\n", name);

   /* determine compute phase where error occurred */
   printf ("\tPhase: ");
   switch(phase)
   {
      case CWF_DV_FORMULA:
         printf ("Default Value\n");
         break;

      case CWF_IT_FORMULA:
         printf ("Translation\n");
         break;

      case CWF_IV_FORMULA:
         printf ("Validation\n");
         break;

      case CWF_COMPUTED_FORMULA:
         printf ("Computed Value\n");
         break;

      case CWF_DATATYPE_CONVERSION:
         printf ("DataType\n");
         break;

      case CWF_COMPUTED_FORMULA_SAVE:
         printf ("Computed Formula Save\n");
         break;

      default:
         printf ("Unknown - phase code is %d (0x%X)\n", phase, phase);
         break;
   }

   /* make sure the handle isn't NULL */
   if (ErrorText)
   {
      /* get a pointer to the handle */
      pErrText = (BYTE *)OSLockObject(ErrorText);

      ErrTextBuf[0]='\0';
      bufPos = 0;

      /* go through each byte */
      for (i = 0; i < wErrorTextSize; i++)
      {
         /* skip the following chars and start over to build text string */
         if ((*pErrText=='\0') || (*pErrText=='\n') || (*pErrText=='\r') || (*pErrText=='\f'))
         {
            pErrText++;
            bufPos = 0;
         }
         else /* build text string */
            ErrTextBuf[bufPos++] = *pErrText++;     
      }
      
      ErrTextBuf[bufPos++] = '\0';
      printf("\tErrorText: %s\n", ErrTextBuf);

      OSUnlockObject(ErrorText);
      OSMemFree(ErrorText);
   }

   return CWF_NEXT_FIELD;
}

