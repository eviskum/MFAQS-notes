/***************************************************************************

     SENDMAIL.H

***************************************************************************/

#define TITLE_LEN            30
#define ERR_STR_LEN         256
#define SENDMAILERROR       1

void  LNPUBLIC  ProcessArgs(int, char *[], char *, char *, char *, char *);
int SendMailMainProc();
int QuitSendMail();
int SendMail();
void LNPUBLIC ConvertNewlinesToNulls(char *, int);
char *BuildErrStr(char *);
