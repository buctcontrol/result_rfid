///interface.h

#ifndef INTERFACE_H
#define INTERFACE_H

#include "list.h"

typedef struct interface {
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
    	float speed;            /* speed of km/h */
    	unsigned int points;
}INTERFACE, *PINTERFACE;

extern struct interface g_ife;


#endif /*INTERFACE_H*/
