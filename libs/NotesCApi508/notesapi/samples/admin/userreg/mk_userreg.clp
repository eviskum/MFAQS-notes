PGM
     MONMSG MSGID(CPF2103)

     ADDLIBLE QNOTESAPI
     ADDLIBLE QNTCSDK

     CRTCMOD MODULE(QNTCSDK/USERREG) +
          SRCFILE(QNTCSDK/USERREG) +
          DBGVIEW(*ALL) +
          DEFINE(OS400)

     CRTPGM PGM(QNTCSDK/USERREG) +
          MODULE(*PGM) +
          ENTMOD(QNOTESAPI/NOTES0) +
          BNDSRVPGM(QNOTES/LIBNOTES QLIBASCII/LIBASCII) +
          DETAIL(*BASIC)

ENDPGM