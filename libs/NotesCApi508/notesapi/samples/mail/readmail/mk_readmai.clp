PGM
     MONMSG MSGID(CPF2103)

     ADDLIBLE QNOTESAPI
     ADDLIBLE QNTCSDK

     CRTCMOD MODULE(QNTCSDK/READMAIL) +
          SRCFILE(QNTCSDK/READMAIL) +
          DBGVIEW(*ALL) +
          DEFINE(OS400)

     CRTPGM PGM(QNTCSDK/READMAIL) +
          MODULE(*PGM) +
          ENTMOD(QNOTESAPI/NOTES0) +
          BNDSRVPGM(QNOTES/LIBNOTES QLIBASCII/LIBASCII) +
          DETAIL(*BASIC)

ENDPGM
