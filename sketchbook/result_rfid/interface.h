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
    unsigned int gap_sec;   /* gap seconds */
    unsigned int gap_msec;  /* gap millisecond */
    unsigned int order;     /* order */
    unsigned int end_filled;/* we have filled the end time */
};

int get_dev_fields(char *bp, struct interface *ife, int type);
struct interface * cliFindClassById(uint nClsId);

