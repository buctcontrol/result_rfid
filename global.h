#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* 通用的错误码 */
#define    APP_OK                            0
#define    APP_SUCCESS                       0
#define    APP_FAIL                        (-1)

#define  WITH_RFID
#define  TYPE_START 	0
#define  TYPE_END	1
#define  _PATH_START	"./autoresult.txt"
#define  _PATH_END	"./end_result.txt"
#define  LENGTH         1350

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short int ushort;
typedef unsigned long int ulong;
typedef unsigned long long int ullong;
typedef long long int llong;

enum
{
    FATAL = 1, /**<KIT_DEBUG_LEVEL_FATAL*/
    WARN,      /**<KIT_DEBUG_LEVEL_WARNING*/
    TRACE,     /**<KIT_DEBUG_LEVEL_TRACE*/
    DETAIL,    /**<KIT_DEBUG_LEVEL_DETAIL*/
    FORCE,     /**<KIT_DEBUG_LEVEL_FORCE*/
};

#define dbgPrint(lev, fmt, args...)\
do{\
    printf(fmt, ##args);\
}while(0)

#define dbgPrintfl(lev, fmt, args...)\
do{\
    printf("%s:%d ", __FILE__, __LINE__);\
    printf(fmt, ##args);\
}while(0)

#define dbgAssert(x) assert(x)

/*
 * rider infos
 */
typedef struct
{
    char    str[32];
}HIBPGroupName;

typedef struct
{
    char    str[32];
}HIBPTitle;

enum
{
    CLEANER     = 0,
    NEWBIE      = 1,
    HARDTAIL    = 2,
    WOMAN       = 3,
    MAN         = 4,
    OPEN        = 5,
    ELITE       = 6,
    MASTERA     = 7,
    EBIKE       = 8,
    FREY        = 9,
    MASTERB     = 10,
    MAX_GROUPS 	= 11
};

extern HIBPGroupName groupStr[];

extern HIBPTitle titleStr[];

#endif

