PGM
     MONMSG MSGID(CPF2103)

     ADDLIBLE QNOTESAPI
     ADDLIBLE QNTCSDK

     CRTCMOD MODULE(QNTCSDK/ADDIN) +
          SRCFILE(QNTCSDK/ADDIN) +
          DBGVIEW(*ALL) +
          DEFINE(OS400)

     CRTPGM PGM(QNTCSDK/ADDIN) +
          MODULE(QNTCSDK/ADDIN QNOTESAPI/NOTESAI0) +
          ENTMOD(QNOTESAPI/NOTES0) +
          BNDSRVPGM(QNOTES/LIBNOTES QLIBASCII/LIBASCII) +
          DETAIL(*BASIC)

ENDPGM
