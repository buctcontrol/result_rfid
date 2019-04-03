//
//

#include "interface.h"
#include "riders.h"

static int get_dev_fields(char *bp, struct interface *ife, int type)
{
    if(type == TYPE_START)
    {
        sscanf(bp,
                "%u %u %u",
                &ife->id,
                &ife->sec,
                &ife->msec);
    }
    else if(type == TYPE_END)
    {
        sscanf(bp,
                "%u %u %u",
                &ife->end_id,
                &ife->end_sec,
                &ife->end_msec);
    }
    else
    {
        printf("wrong type: %d\n", type);
        return -1;
    }
    return 0;
}

static char *get_name(char *name, char *p)
{
    while (isspace(*p))
	p++;
    while (*p) {
	if (isspace(*p))
	    break;
	if (*p == ':') {	/* could be an alias */
		char *dot = p++;
 		while (*p && isdigit(*p)) p++;
		if (*p == ':') {
			/* Yes it is, backup and copy it. */
			p = dot;
			*name++ = *p++;
			while (*p && isdigit(*p)) {
				*name++ = *p++;
			}
		} else {
			/* No, it isn't */
			p = dot;
	    }
	    p++;
	    break;
	}
	*name++ = *p++;
    }
    *name++ = '\0';
    return p;
}

static int if_readlist_proc(char *target, int type)
{
    FILE *fh;
    char buf[512];
    struct interface *ife;
    struct interface *pCur = &g_ife;
    int err;
    int count = 0;
    float float_time;

    if(type == TYPE_START)
    {
        fh = fopen(_PATH_START, "r");
    }
    else if(type == TYPE_END)
    {
        fh = fopen(_PATH_END, "r");
    }
    else
    {
        printf("wrong type: %d\n", type);
        return -1;
    }
    if (!fh) {
	fprintf(stderr, "Warning: cannot open %d (%s). Limited output.\n",
	type, strerror(errno)); 
	return -2;
    }	

    err = 0;
    while(fgets(buf, sizeof buf, fh)){
        count++;
        char *s, name[IFNAMSIZ];
        s = get_name(name, buf);    
        ife = (struct interface *)malloc(sizeof(struct interface));
        memset(ife, sizeof(struct interface), 1);
        ife->pure_sec  = 86399;
        ife->pure_msec = 999;
        get_dev_fields(s, ife, type);
        if (target && strcmp(target,name))
        {
            printf("strcmp err, break\n");
            break;
        }
        switch(type)
        {
            case TYPE_START:
                list_add_tail(&ife->list, &pCur->list);
                break;

            case TYPE_END:
#ifdef WITH_RFID
                pCur = cliFindClassById(ife->end_id);
#else
                pCur = cliFindClassById(count);
#endif
                if((pCur != NULL) && (!pCur->end_filled))
                {
                    pCur->end_sec = ife->end_sec;
                    pCur->end_msec = ife->end_msec;
                    pCur->end_filled = 1;   //for drop dup
                }
                break;

            default:
                printf("wong type: %d\n", type);
                break;
        }
    }

    if (ferror(fh)) {
        //perror(type);
        err = -1;
    }

    fclose(fh);
    return err;
}

void read_start()
{
	if_readlist_proc("HIBP", TYPE_START);
}

void read_finish()
{
	if_readlist_proc("HIBP", TYPE_END);
}

static int calc_time(PINTERFACE* pCur)
{
	if(pCur->end_msec < pCur->msec)
	{
	    	pCur->pure_sec = (pCur->end_sec - 1) - pCur->sec;
	    	pCur->pure_msec = 1000 + pCur->end_msec - pCur->msec;
	}
	else
	{
	    	pCur->pure_sec = pCur->end_sec - pCur->sec;
	    	pCur->pure_msec = pCur->end_msec - pCur->msec;
	}
}

static int calc_speed(PINTERFACE* pCur)
{
      	float float_time = pCur->pure_sec + pCur->pure_msec/1000;
	pCur->speed = (LENGTH * 3.6) / float_time;
}

void calc_result()
{
	struct interface  *pCur = NULL;
	struct list_head* pPos = NULL;

	list_for_each(pPos, &g_ife.list)
	{
		pCur = list_entry(pPos, struct interface, list);
                if(!pCur->end_filled)
                {
		    	calc_time(pCur);
		    	clac_speed(pCur);
                }

		HIBPRiderInfo* rider = get_rider_info(pCur->id);
		if(rider != NULL)
			rider->results[0]= *pCur;
	}

	sort_by_time(get_groups(), get_groups_count()):
}

void sort_by_time(HIBPGroupRider* groups, int ngroups)
{
}
