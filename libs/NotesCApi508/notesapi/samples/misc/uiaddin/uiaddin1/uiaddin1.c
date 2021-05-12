/****************************************************************************

    PROGRAM:    uiaddin1

    FILE:       uiaddin1.c

    SYNTAX:     This program is run from the Domino and Notes Workstation Menu

    PURPOSE:    Shows how to implement a Domino and Notes workstation menu add-in.

    DESCRIPTION:
        This program provides a procedure to handle the menu item
        "DOS Shell". Add this menu item to the Actions menu in Domino and Notes
        by setting the notes.ini file. When the Domino and Notes user picks 
		"DOS Shell" from the tools menu, this procedure executes the DOS command 
		shell.

****************************************************************************/

#include <windows.h>            /* required for all Windows apps */

/* Standard library include files */
#include <string.h>

/* Domino and Notes include files */
#include <global.h>
#include <addinmen.h> 

#define IDM_DOS_SHELL 0


NAMRESULT LNCALLBACK AddinMenuProc (WORD wMsg, LONG lParam)
{
   switch (wMsg)
   {
      case NAMM_INIT:
      {
         NAM_INIT_INFO *pInitInfo;

         /* lParam is a pointer to the NAM_INIT_INFO structure */
         pInitInfo = (NAM_INIT_INFO *)lParam;

         /* Add the menu item to the Domino and Notes Actions menu */
         /* Assign this menu item an id and a name */
         pInitInfo->wMenuID = IDM_DOS_SHELL;

         strcpy (pInitInfo->MenuItemName, "&DOS Shell");

         /* tell Domino and Notes that there are no more menu items to add */
         return (NAM_INIT_STOP);
      }

      case NAMM_COMMAND:
      {

         NAM_COMMAND_INFO *cmdInfo;
         WORD wSts;

         /* The addin menu item was chosen */
         /* lParam is a pointer to the NAM_COMMAND_INFO structure */
         cmdInfo = (NAM_COMMAND_INFO *)lParam;

         wSts = WinExec("command.com", SW_SHOWMAXIMIZED);
         if (wSts < 32 )
               MessageBox (cmdInfo->hNotesWnd, "Cannot execute this item", 
                           "Addin Error", MB_ICONHAND | MB_OK);
         return (NAM_NOERROR);
      }

      default:          /* default processing for all other messages */
         return (NAM_NOERROR);
   }
}


