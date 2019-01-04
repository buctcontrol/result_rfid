#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <net/if.h>
#include "interface.h"
#include "riders.h"

struct interface g_ife;

char *get_name(char *name, char *p)
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

int get_dev_fields(char *bp, struct interface *ife, int type)
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

static int if_readlist_proc(char *target, int type)
{
    FILE *fh;
    char buf[512];
    struct interface *ife;
    struct interface *pCur = &g_ife;
    int err;
    int count = 0;

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
        //ife->id = count;
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
                pCur = cliFindClassById(ife->end_id);
                if(pCur != NULL)
                {
                    pCur->end_sec = ife->end_sec;
                    pCur->end_msec = ife->end_msec;
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

struct interface * cliFindClassById(uint nClsId)
{
	struct interface  *pCls = NULL;
	struct list_head* pPos = NULL;

	list_for_each(pPos, &g_ife.list)
	{
		pCls = list_entry(pPos, struct interface, list);
		if(pCls->id == nClsId)
			return pCls;
	}

	return NULL;
}

int makeTitle(char* pTitle, unsigned int group, struct interface *pCls, unsigned int order, unsigned int rider_num)
{
    if(!group)
    {
        sprintf(pTitle, "%s", groupStr[group].str);
    }
    else
    {
        if(order <= rider_num)
        {
            if((pCls->pure_sec == 86399) && (pCls->pure_msec == 999))
            {
                sprintf(pTitle, "%s", groupStr[group].str);
            }
            else
            {
                if(order > 0 && order < 4)
                {
                    sprintf(pTitle, "%s%s", groupStr[group].str, titleStr[order - 1].str);
                }
                else
                {
                    sprintf(pTitle, "%s%03d", groupStr[group].str, order);
                }
            }
        }
        else
        {
            sprintf(pTitle, "%s", groupStr[group].str);
        }
    }

    return 0;
}

int main(void)
{
	struct interface *pCls = NULL;
	struct list_head *pPos = NULL;
    struct interface *pCur = &g_ife;
    char cmd[256];
    char title[128];
    int rider_num = 0;
    int rider_max = 0;
    int i;

    rider_max = sizeof(riders)/sizeof(HIBPRiderInfo);
	memset(&g_ife, 0, sizeof(g_ife));

	INIT_LIST_HEAD(&g_ife.list);
    if_readlist_proc("HIBP", TYPE_START);
    if_readlist_proc("HIBP", TYPE_END);
	list_for_each(pPos, &g_ife.list)
	{
        pCls = list_entry(pPos, struct interface, list);
        pCls->group = riders[rider_num].group;
        rider_num++;
    }
    printf("We have %d riders, register %d riders!\n", rider_num, rider_max);
    for(i = 0; i< rider_num; i++)
    {
        pCur = cliFindClassById(i+1);
        pCur->order = 1;
        list_for_each(pPos, &g_ife.list)
        {
            pCls = list_entry(pPos, struct interface, list);
            if((pCls->group == pCur->group) && ((pCur->pure_sec > pCls->pure_sec) || ((pCur->pure_sec == pCls->pure_sec) && (pCur->pure_msec > pCls->pure_msec))))
            {
                pCur->order++;
            }
        }
    }

    system("rm -rf ./result.html");
    for(i = 0; i< rider_max; i++)
	{
        pCls = cliFindClassById(i+1);
        memset(cmd, 0, sizeof(cmd));
        memset(title, 0, sizeof(title));
        if(i < rider_num)
        {
            makeTitle(title, riders[i].group, pCls, pCls->order, rider_num);
            if((pCls->pure_sec == 86399) && (pCls->pure_msec == 999))
            {
                printf("HIBP: %03d  %s  %s  DNF          -> %s\n", i+1, 
                       riders[i].name, \
                       riders[i].team, \
                       title);
                sprintf(cmd, "echo '<tr><td>%03d</td><td>%s</td><td>%s</td><td>DNS</td><td>%s</td></tr>' >> ./result.html", i+1, 
                        riders[i].name, \
                        riders[i].team, \
                        title);
            }
            else
            {
                printf("HIBP: %03d  %s  %s  %02d:%02d:%02d.%03d -> %s\n", pCls->id, 
                       riders[i].name, \
                       riders[i].team, \
                       (pCls->pure_sec/60/60)%24, \
                       (pCls->pure_sec/60)%60, \
                       (pCls->pure_sec%60), \
                       pCls->pure_msec, \
                       title);
                sprintf(cmd, "echo '<tr><td>%03d</td><td>%s</td><td>%s</td><td>%02d:%02d:%02d.%03d</td><td>%s</td></tr>' >> ./result.html", pCls->id, 
                        riders[i].name, \
                        riders[i].team, \
                        (pCls->pure_sec/60/60)%24, \
                        (pCls->pure_sec/60)%60, \
                        (pCls->pure_sec%60), \
                        pCls->pure_msec, \
                        title);
            }
        }
        else
        {
            makeTitle(title, riders[i].group, pCls, rider_max+1, rider_num);
            printf("HIBP: %03d  %s  %s  DNS          -> %s\n", i+1, 
                    riders[i].name, \
                    riders[i].team, \
                    title);
            sprintf(cmd, "echo '<tr><td>%03d</td><td>%s</td><td>%s</td><td>DNS</td><td>%s</td></tr>' >> ./result.html", i+1, 
                    riders[i].name, \
                    riders[i].team, \
                    title);
        }
        system(cmd);
	}

    return 0;
}