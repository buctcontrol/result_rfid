#include "list.h"
#define     TYPE_START  1
#define     TYPE_END    2
struct interface {
	struct list_head list;
    unsigned int id;	    /* rider id */
    unsigned int end_id;	/* rider end id, maybe diff */
    unsigned int group;     /* rider group info */
    unsigned int sec;		/* seconds */
    unsigned int msec;		/* millisecond */
    unsigned int end_sec;	/* end seconds */
    unsigned int end_msec;	/* end millisecond */
    unsigned int pure_sec;	/* pure seconds */
    unsigned int pure_msec;	/* pure millisecond */
    unsigned int order;     /* order */
};

int get_dev_fields(char *bp, struct interface *ife, int type);
struct interface * cliFindClassById(uint nClsId);

#define _PATH_START		"./autoresult.txt"
#define _PATH_END		"./end_result.txt"
