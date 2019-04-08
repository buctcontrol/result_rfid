//
//

#include "global.h"
#include "interface.h"
#include "riders.h"
#include "utils.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <net/if.h>
#include <ctype.h>


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

static int calc_time(PINTERFACE pCur)
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


static int calc_speed(PINTERFACE pCur)
{
      	float float_time = pCur->pure_sec + pCur->pure_msec/1000;
	pCur->speed = (LENGTH * 3.6) / float_time;
}

static int compare_rider_time(const HIBPRiderInfo* src, const HIBPRiderInfo* dst)
{
	if(   (dst->results[0].pure_sec < src->results[0].pure_sec) 
	   || ((dst->results[0].pure_sec == src->results[0].pure_sec) && (dst->results[0].pure_msec < src->results[0].pure_msec))
	 )
	 {
	 	return 1;	
	 }

	 return 0;
}

static void sort_by_time(HIBPGroupRider* groups, int groups_count)
{
	sort_riders(groups, groups_count, compare_rider_time);
}

static void calc_gap_time(HIBPGroupRider* groups, int groups_count)
{
	int i,j;
	for(i=0; i<groups_count; i++){
		for(int j=0; j<groups[i].nriders; j++){
			HIBPRiderInfo* rider = &(groups[i].riders[j]);
			PINTERFACE pMax = groups[i].riders[0].results;
			PINTERFACE pCur = rider->results;
			if(pCur->pure_msec < pMax->pure_msec)
			{
				pCur->gap_sec = (pCur->pure_sec - 1) - pMax->pure_sec;
				pCur->gap_msec = 1000 + pCur->pure_msec - pMax->pure_msec;
			}
			else
			{
				pCur->gap_sec = pCur->pure_sec - pMax->pure_sec;
				pCur->gap_msec = pCur->pure_msec - pMax->pure_msec;
			}
		}
	}
}

void calc_result()
{
	struct interface  *pCur = NULL;
	struct list_head* pPos = NULL;

	list_for_each(pPos, &g_ife.list)
	{
		pCur = list_entry(pPos, struct interface, list);
                if(pCur->end_filled)
                {
		    	calc_time(pCur);
		    	calc_speed(pCur);
                }

		HIBPRiderInfo* rider = get_rider_info(pCur->id);
		if(rider != NULL)
			rider->results[0]= *pCur;
	}

	sort_by_time(get_groups(), get_groups_count());
	calc_gap_time(get_groups(), get_groups_count());
}




/*#include <stdio.h>

struct interface g_ife;

int main()
{
	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);
	read_start();
	read_finish();
	calc_result();

	HIBPGroupRider* groups=get_groups();
	char buf[256]={0};
	for(int i=0; i<get_groups_count(); i++){
		for(int j=0; j<groups[i].nriders; j++){
			HIBPRiderInfo* r= groups[i].riders+j;
			sprintf(buf, "%s,%d,%03d,%s,%s", groupStr[r->group].str, j+1, r->number, r->name, r->team);
				PINTERFACE p = r->results;
				sprintf(buf,"%s,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%d", buf,
					(p->sec/60/60+8)%24, (p->sec/60)%60, (p->sec%60), p->msec,
					(p->end_sec/60/60+8)%24, (p->end_sec/60)%60, (p->end_sec%60), p->end_msec,
					(p->pure_sec/60/60)%24, (p->pure_sec/60)%60, (p->pure_sec%60), p->pure_msec,
					(p->gap_sec/60/60)%24, (p->gap_sec/60)%60, (p->gap_sec%60), p->gap_msec,
					p->points);

			printf("%s\n", buf);
		}
			
	}
	
	return 0;
}
*/
