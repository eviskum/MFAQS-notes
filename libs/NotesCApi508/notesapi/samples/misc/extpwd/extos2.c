#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef OS2_2x
#include <conio.h>
#include <os2.h>
#endif

#include <global.h>
#include <names.h>
#include <extmgr.h>
#include <bsafeerr.h>
#include <nsferr.h>

HEMREGISTRATION hHandler;

STATUS LNPUBLIC handler(EMRECORD *data);
STATUS LNPUBLIC MainEntryPoint();

STATUS LNPUBLIC handler(EMRECORD *data)
{
        VARARG_PTR              pArgs;
        DWORD                   MaxPwdLen;
        DWORD far *             retLength;
        char far *              retPassword;
        char far *              FileName;
        char far *              OwnerName;
        DWORD                   DataLen;
        BYTE far *              Data;
        int                     i=0;


        if (EM_GETPASSWORD != data->EId)
                return (ERR_EM_CONTINUE);

        /* Fetch the arguments */
        pArgs = data->Ap;
        MaxPwdLen = VARARG_GET (pArgs, DWORD);
        retLength = VARARG_GET (pArgs, DWORD far *);
        retPassword = VARARG_GET (pArgs, char far *);
        FileName = VARARG_GET (pArgs, char far *);
        OwnerName = VARARG_GET (pArgs, char far *);
        DataLen = VARARG_GET (pArgs, DWORD);
        Data = VARARG_GET (pArgs, BYTE far *);


	    printf("Please enter your password (Extension Manager Notification):  ");
        fflush (stdout); 

        /* get password but do not echo character to screen */
        while ( ((retPassword[i++] = _getch ()) != '\r') &&
                (i <= MAX_ID_PASSWORD));

        /* NULL terminate */
        retPassword[i - 1] = '\0';
 
	    *retLength = strlen(retPassword);

	    printf ("\n");

	    return ERR_BSAFE_EXTERNAL_PASSWORD;
}

STATUS LNPUBLIC MainEntryPoint()
{
	STATUS err;

	if(err=EMRegister(EM_GETPASSWORD, EM_REG_BEFORE, handler,0, &hHandler))
	    fprintf(stderr, "EMRegister failed.\n");

	return err;
}
