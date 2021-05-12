# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#		Makefile for mail/readmail API for the AS/400.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

!include "..\..\..\as400\setup.mak"

# The name of the program.
PROGNAME = readmail

ICCAS_ARGS = $(ICCAS_ARGS) \
  		/B"CRTPGM PGM($(NOTESSDK)/$(PROGNAME)) \
		   BNDSRVPGM($(QNOTES)/$(LIBNOTES) $(QLIBASCII)/$(LIBASCII)) \
                   ENTMOD($(NOTESAPILIB)/$(NOTES0)) \
		   DETAIL(*BASIC)" \
		$(PROGNAME).c

main:  
  @echo .
  @echo $(PROGNAME) build started.
  @echo .
  - cttconn /h$(HOST)
  ctttime sync
  $(CC) $(ICCAS_ARGS)
  cttdis
  @echo .
  @echo $(PROGNAME) build completed/targets up-to-date
  @echo .