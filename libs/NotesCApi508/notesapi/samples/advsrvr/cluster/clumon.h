/* miscellaneous constants */
#define CLUMON_TITLE    "Advanced Server Cluster Monitor Sample"
#define LINEOTEXT               256

/* Selected Database Mark Flags */
#define  MARK_IN_SERVICE     1
#define  MARK_OUT_SERVICE    2
#define  MARK_DELETE         4

/* Cluster Info Bit Flags */
#define NPN_CLU_SHOW_CLUNAME            0x0001
#define NPN_CLU_SHOW_LOAD                       0x0002
#define NPN_CLU_SHOW_CLUMATES           0x0004
#define NPN_CLU_SHOW_ALL                        0xFFFF

/* Application Error Codes */
#define NPNERR                                                  10000
#define NPNERR_BAD_PARAM                                NPNERR + 1
#define NPNERR_EXPECTED_FAILURE                 NPNERR + 2
#define NPNERR_NOT_CLUSTER_MEMBER               NPNERR + 3
#define NPNERR_GETTING_CLUSTER_NAME             NPNERR + 4
#define NPNERR_GETTING_CLUSTER_MATES    NPNERR + 5
#define NPNERR_BAD_INPUT                                NPNERR + 6
#define NPNERR_CANCELLED                    NPNERR + 11

/* Remote Console Command Strings */
#define RESTRICT_SERVER "Set Con SERVER_RESTRICTED="
#define GET_RESTRICT    "Show Con SERVER_RESTRICTED"
#define RESTRICTED      "SERVER_RESTRICTED=1"
#define SHUTDOWN_SERVER "Quit"
#define SET_THRESHOLD   "Set Con SERVER_AVAILABILITY_THRESHOLD="
#define GET_THRESHOLD   "Show Con SERVER_AVAILABILITY_THRESHOLD"
#define THRESHOLD               "SERVER_AVAILABILITY_THRESHOLD="
#define CON_ERROR               "Invalid value for command option"
