# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#		Makefile for server/addin API for the AS/400.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

!include "..\..\..\as400\setup.mak"

# The name of the program.
PROGNAME = addin

ICCAS_ARGS = $(ICCAS_ARGS) /C+ /Q+ \
  		/B"CRTPGM PGM($(NOTESSDK)/$(PROGNAME)) \
		   BNDSRVPGM($(QNOTES)/$(LIBNOTES) $(QLIBASCII)/$(LIBASCII)) \
                   ENTMOD($(NOTESAPILIB)/$(NOTES0)) \
		   DETAIL(*BASIC)" \
		$(PROGNAME).c

LINK_ARGS = CRTPGM PGM($(NOTESSDK)/$(PROGNAME)) \
		   BNDSRVPGM($(QNOTES)/$(LIBNOTES)) \
		   MODULE($(NOTESSDK)/$(PROGNAME) $(NOTESAPILIB)/notesai0) \
                   ENTMOD($(NOTESAPILIB)/$(NOTES0)) \
		   DETAIL(*BASIC)


main:  
  @echo .
  @echo $(PROGNAME) build started.
  @echo .

  - cttconn /h$(HOST) /ASn$(CONNAME)
  ctttime sync
  $(CC) $(ICCAS_ARGS)
  ctthcmd /ASn$(CONNAME) /Q $(LINK_ARGS)
  cttdis

  @echo .
  @echo $(PROGNAME) build completed/targets up-to-date
  @echo .