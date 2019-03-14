#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <net/if.h>
#include "interface.h"
#include "riders.h"

#define WITH_POINTS     1
#define WITH_RFID       1

struct interface g_max[MAX];
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

int cliFindGroupById(uint nClsId)
{
	int rider_max = 0;
	int i;

	rider_max = sizeof(riders)/sizeof(HIBPRiderInfo);

    for(i = 0; i < rider_max; i++)
	{
		if(riders[i].number == nClsId)
			return riders[i].group;
	}

	return -1;
}

int cliFindIndexById(uint nClsId)
{
	int rider_max = 0;
	int i;

	rider_max = sizeof(riders)/sizeof(HIBPRiderInfo);

    for(i = 0; i < rider_max; i++)
	{
		if(riders[i].number == nClsId)
			return i;
	}

	return -1;
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
                sprintf(pTitle, "%s", "-");
            }
            else
            {
                if(order > 0 && order < 4)
                {
                    sprintf(pTitle, "%s", titleStr[order - 1].str);
                }
                else
                {
                    sprintf(pTitle, "%03d", order);
                }
            }
        }
        else
        {
            sprintf(pTitle, "%s", "-");
        }
    }

    return 0;
}

void init_group_rider(HIBPGroupRider group_riders[], HIBPRiderInfo riders[], int ngroups, int nriders)
{
	int i=0,j=0,k=0;
	for(j=0 ; j<nriders; j++)
	{
		if( j== 0 )
		{
			group_riders[i].group = riders[j].group;
		}

		if(group_riders[i].group == riders[j].group )
		{
			group_riders[i].riders[k] = riders[j].number;
			k++;
		}
		else
		{
			group_riders[i].nriders = k;
			i++;
			k=0;
			group_riders[i].riders[k] = riders[j].number;
			k++;
			group_riders[i].group = riders[j].group;
		}
	}
	group_riders[i].nriders = k;
}

void sort_riders(int riders_id[], int nriders)
{ 
	int i,j;
	struct interface *pi=NULL, *pj=NULL;
	for(i = 0; i< nriders-1; i++)
	{
		pi = cliFindClassById(riders_id[i]);
		if(pi == NULL)
			continue;

		for(j = i+1; j<nriders; j++)
		{
			pi = cliFindClassById(riders_id[i]);
			pj = cliFindClassById(riders_id[j]);
			if(pj!=NULL && pj->order < pi->order)
			{
				int tmp = riders_id[i];
				riders_id[i] = riders_id[j];
				riders_id[j] = tmp;
			}
		}
	}
}

void sort_groups(HIBPGroupRider group_riders[], int ngroups )
{
	int i;
	for(i = 0; i< ngroups; i++)
	{
		if(group_riders[i].nriders > 0 )
			sort_riders(group_riders[i].riders, group_riders[i].nriders);
	}
}

void generate_result_rider(int rider_id[], int nriders)
{
	int i;
    int j;
    int index;
    int count = 0;
	char cmd[512];
    char cmd_csv[512];
	char title[128];
	struct interface *pCls = NULL;
	for(i=0; i<nriders; i++)
	{
		pCls = cliFindClassById(rider_id[i]);
		memset(cmd, 0, sizeof(cmd));
		memset(cmd_csv, 0, sizeof(cmd_csv));
		memset(title, 0, sizeof(title));
		if(pCls != NULL)
		{
            index = cliFindIndexById(rider_id[i]);
            if(index < 0)
            {
                printf("%s, %d, rider_id: %03d find index err!\n", __FILE__, __LINE__, rider_id[i]);
                continue;
            }
            else
            {
                makeTitle(title, riders[index].group, pCls, pCls->order, nriders);
                if((pCls->pure_sec == 86399) && (pCls->pure_msec == 999))
                {
                    printf("HIBP: %03d  %s  %s  %02d:%02d:%02d.%03d  DNF          -> %s     0\n", pCls->id, \
                            riders[index].name, \
                            riders[index].team, \
                            (pCls->sec/60/60+8)%24, (pCls->sec/60)%60, pCls->sec%60, pCls->msec,\
                            title);
                    sprintf(cmd, "echo '<tr><td>%s</td><td>%03d</td><td>%s</td><td>%s</td><td>%02d:%02d:%02d.%03d</td><td>-</td><td>DNF</td><td>-</td>i<td>0</td></tr>' >> ./result.html", \
                            title, pCls->id,\
                            riders[index].name,\
                            riders[index].team,\
                            (pCls->sec/60/60+8)%24, (pCls->sec/60)%60, pCls->sec%60, pCls->msec);
                    sprintf(cmd_csv,"echo '%s,%s,%03d,%s,%s,%02d:%02d:%02d.%03d,-,-,DNF,-' >> ./result.csv",\
                            groupStr[riders[index].group].str, \
                            title, pCls->id, \
                            riders[index].name, \
                            riders[index].team, \
                            (pCls->sec/60/60+8)%24, (pCls->sec/60)%60, pCls->sec%60, pCls->msec);
                }
                else
                {
                    if((riders[index].group == ELITE) || (riders[index].group == WOMAN))
                    {
                        switch(pCls->order)
                        {
                            case 1:
                                count = 200;
                                break;

                            case 2:
                                count = 160;
                                break;

                            case 3:
                                count = 140;
                                break;

                            case 4:
                                count = 120;
                                break;

                            case 5:
                                count = 100;
                                break;

                            case 6:
                            case 7:
                            case 8:
                            case 9:
                            case 10:
                            case 11:
                                count = 100 - 5 * (pCls->order - 5);
                                break;

                            case 12:
                            case 13:
                            case 14:
                            case 15:
                            case 16:
                                count = 70 - 2 * (pCls->order - 11);
                                break;

                            case 17:
                            case 18:
                            case 19:
                            case 20:
                                count = 60 - 10 * (pCls->order - 16);
                                break;

                            default:
                                count = 10;
                                break;

                        }

                    }
                    else
                    {
                        switch(pCls->order)
                        {
                            case 1:
                                count = 60;
                                break;

                            case 2:
                                count = 50;
                                break;

                            case 3:
                                count = 45;
                                break;

                            case 4:
                                count = 40;
                                break;

                            case 5:
                                count = 35;
                                break;

                            case 6:
                                count = 30;
                                break;

                            case 7:
                            case 8:
                            case 9:
                            case 10:
                                count = 30 - (pCls->order - 6);
                                break;

                            case 11:
                            case 12:
                            case 13:
                            case 14:
                            case 15:
                            case 16:
                            case 17:
                            case 18:
                            case 19:
                            case 20:
                                count = 21 - (pCls->order - 11);
                                break;

                            case 21:
                            case 22:
                            case 23:
                            case 24:
                            case 25:
                            case 26:
                            case 27:
                            case 28:
                            case 29:
                            case 30:
                                count = 10;
                                break;

                            default:
                                count = 5;
                                break;
                        }
                    }
                    printf("HIBP: %03d  %s  %s  %02d:%02d:%02d.%03d    %02d:%02d:%02d.%03d    %02d:%02d:%02d.%03d    +%02d:%02d:%02d.%03d ->  %s    %d\n", pCls->id,\
                            riders[index].name, \
                            riders[index].team, \
                            (pCls->sec/60/60+8)%24, (pCls->sec/60)%60, pCls->sec%60, pCls->msec,\
                            (pCls->end_sec/60/60+8)%24, (pCls->end_sec/60)%60, pCls->end_sec%60, pCls->end_msec,\
                            (pCls->pure_sec/60/60)%24, (pCls->pure_sec/60)%60, (pCls->pure_sec%60), pCls->pure_msec,\
                            (pCls->gap_sec/60/60)%24, (pCls->gap_sec/60)%60, pCls->gap_sec%60, pCls->gap_msec,\
                            title, \
                            count);
#ifdef  WITH_POINTS
                    sprintf(cmd, "echo '<tr><td>%s</td><td>%03d</td><td>%s</td><td>%s</td><td>%02d:%02d:%02d.%03d</td><td>%02d:%02d:%02d.%03d</td><td><a rel='certy' href='../certs/sy0324/%d-%s.jpg'>%02d:%02d:%02d.%03d</a> </td><td>+%02d:%02d:%02d.%03d</td><td>%d</td></tr>' >> ./result.html",\
                            title, pCls->id,\
                            riders[index].name, \
                            riders[index].team, \
                            (pCls->sec/60/60+8)%24, (pCls->sec/60)%60, pCls->sec%60, pCls->msec,\
                            (pCls->end_sec/60/60+8)%24, (pCls->end_sec/60)%60, pCls->end_sec%60, pCls->end_msec,\
                            pCls->order, \
                            riders[index].name, \
                            (pCls->pure_sec/60/60)%24, (pCls->pure_sec/60)%60, (pCls->pure_sec%60), pCls->pure_msec,\
                            (pCls->gap_sec/60/60)%24, (pCls->gap_sec/60)%60, pCls->gap_sec%60, pCls->gap_msec,\
                            count);
#else
                    sprintf(cmd, "echo '<tr><td>%s</td><td>%03d</td><td>%s</td><td>%s</td><td>%02d:%02d:%02d.%03d</td><td>%02d:%02d:%02d.%03d</td><td><a rel='certy' href='../certs/sy0324/%d-%s.jpg'>%02d:%02d:%02d.%03d</a> </td><td>+%02d:%02d:%02d.%03d</td></tr>' >> ./result.html",\
                            title, pCls->id,\
                            riders[index].name, \
                            riders[index].team, \
                            (pCls->sec/60/60+8)%24, (pCls->sec/60)%60, pCls->sec%60, pCls->msec,\
                            (pCls->end_sec/60/60+8)%24, (pCls->end_sec/60)%60, pCls->end_sec%60, pCls->end_msec,\
                            pCls->order, \
                            riders[index].name, \
                            (pCls->pure_sec/60/60)%24, (pCls->pure_sec/60)%60, (pCls->pure_sec%60), pCls->pure_msec,\
                            (pCls->gap_sec/60/60)%24, (pCls->gap_sec/60)%60, pCls->gap_sec%60, pCls->gap_msec\
                           );
#endif
                    for(j = 0; j < sizeof(riders[index].name); j++)
                    {
                        if(riders[index].name[j] == ' ')
                        {
                            riders[index].name[j] = '\0';
                        }
                    }
                    sprintf(cmd_csv,"echo '%s,%s,%03d,%s,%s,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%d-%s.jpg,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d' >> ./result.csv",\
                            groupStr[riders[index].group].str, \
                            title, pCls->id,\
                            riders[index].name, \
                            riders[index].team, \
                            (pCls->sec/60/60+8)%24, (pCls->sec/60)%60, pCls->sec%60, pCls->msec,\
                            (pCls->end_sec/60/60+8)%24, (pCls->end_sec/60)%60, pCls->end_sec%60, pCls->end_msec,\
                            pCls->order, \
                            riders[index].name, \
                            (pCls->pure_sec/60/60)%24, (pCls->pure_sec/60)%60, (pCls->pure_sec%60), pCls->pure_msec,\
                            (pCls->gap_sec/60/60)%24, (pCls->gap_sec/60)%60, pCls->gap_sec%60, pCls->gap_msec);
                }
            }
		}
		system(cmd);
		system(cmd_csv);
	}

	for(i=0; i<nriders; i++)
	{
		pCls = cliFindClassById(rider_id[i]);
		memset(cmd, 0, sizeof(cmd));
		memset(cmd_csv, 0, sizeof(cmd_csv));
		if(pCls == NULL)
		{
            index = cliFindIndexById(rider_id[i]);
            if(index < 0)
            {
                printf("%s, %d, rider_id: %03d find index err!\n", __FILE__, __LINE__, rider_id[i]);
                continue;
            }
            else
            {
                printf("HIBP: %03d  %s  %s  DNS          -> -   0\n", riders[index].number,\
                        riders[index].name,\
                        riders[index].team\
                      );
                sprintf(cmd, "echo '<tr><td>-</td><td>%03d</td><td>%s</td><td>%s</td><td>-</td><td>-</td><td>DNS</td><td>-</td><td>0</td></tr>' >> ./result.html", riders[index].number,\
                        riders[index].name,\
                        riders[index].team\
                       );
                sprintf(cmd_csv,"echo '%s,-,%03d,%s,%s,-,-,-,DNS,-,' >> ./result.csv",\
                        groupStr[riders[index].group].str, \
                        riders[index].number,\
                        riders[index].name, \
                        riders[index].team);
                system(cmd);
                system(cmd_csv);
            }
		}

	}
}

void generate_result(HIBPGroupRider group_riders[], int ngroups )
{
	int i;
	char cmd[512];
	system("rm -rf ./result.html");
    system("rm -rf ./result.csv");
	for(i = 0; i< ngroups; i++)
	{
		if(group_riders[i].nriders == 0 )
			continue;

		printf("\nHIBP: %s\n", groupStr[group_riders[i].group].str);
		sprintf(cmd, "echo '<center><font size=\"5\">%s</font></center>' >> ./result.html", groupStr[group_riders[i].group].str);
		system(cmd);
		sprintf(cmd, "echo '</table> <br/>' >> ./result.html");
		system(cmd);
#ifdef  WITH_POINTS
		sprintf(cmd, "echo '<table id=\"t01\"> <tr><th style=\"width:7%\">排名</th><th style=\"width:5%\">号码</th><th style=\"width:12%\">姓名</th><th style=\"width:20%\">车队</th><th style=\"width:13%\">发车时间</th><th style=\"width:13%\">到达时间</th><th style=\"width:13%\">成绩</th><th style=\"width:13%\">时间差</th><th style=\"width:4%\">积分</th></tr>' >> result.html");
#else
		sprintf(cmd, "echo '<table id=\"t01\"> <tr><th style=\"width:7%\">排名</th><th style=\"width:5%\">号码</th><th style=\"width:12%\">姓名</th><th style=\"width:20%\">车队</th><th style=\"width:14%\">发车时间</th><th style=\"width:14%\">到达时间</th><th style=\"width:14%\">成绩</th><th style=\"width:14%\">时间差</th></tr>' >> result.html");
#endif
		system(cmd);
		generate_result_rider(group_riders[i].riders, group_riders[i].nriders);
		sprintf(cmd, "echo '</table> <br/>' >> ./result.html");
		system(cmd);
	}
}

int main(void)
{
	struct interface *pCls = NULL;
	struct list_head *pPos = NULL;
	struct interface *pCur = &g_ife;
	unsigned int rider_id[512];	    /* rider id */
	HIBPGroupRider group_riders[MAX];	  
	int rider_num = 0;
	int rider_max = 0;
    int group = 0;
	int i;

	rider_max = sizeof(riders)/sizeof(HIBPRiderInfo);
	memset(&g_ife, 0, sizeof(g_ife));
	memset(&rider_id, 0 ,sizeof(rider_id));
	memset(&group_riders, 0 ,sizeof(group_riders));
	init_group_rider(group_riders, riders, MAX, rider_max);

	INIT_LIST_HEAD(&g_ife.list);
	if_readlist_proc("HIBP", TYPE_START);
	if_readlist_proc("HIBP", TYPE_END);
	list_for_each(pPos, &g_ife.list)
	{
		pCls = list_entry(pPos, struct interface, list);
        group = cliFindGroupById(pCls->id);
        if(group < 0)
        {
			printf("rider id:%d error!\n", pCls->id);
			continue;
        }

		pCls->group = group;
		rider_id[rider_num] = pCls->id;
		rider_num++;
	}


	printf("We have %d riders, register %d riders!\n", rider_num, rider_max);
	for(i = 0; i< rider_num; i++)
	{
		pCur = cliFindClassById(rider_id[i]);
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


	for(i = 0; i< rider_num; i++)
	{
		pCur = cliFindClassById(rider_id[i]);
		if(pCur->order == 1)
		{
			memcpy(&g_max[pCur->group], pCur, sizeof(struct interface));
			printf("HIBP: %03d  %02d:%02d:%02d.%03d    %02d:%02d:%02d.%03d    %02d:%02d:%02d.%03d\n", pCur->id,\
					(pCur->sec/60/60+8)%24, (pCur->sec/60)%60, pCur->sec%60, pCur->msec,\
					(pCur->end_sec/60/60+8)%24, (pCur->end_sec/60)%60, pCur->end_sec%60, pCur->end_msec,\
					(pCur->pure_sec/60/60)%24,\
					(pCur->pure_sec/60)%60,\
					(pCur->pure_sec%60),\
					pCur->pure_msec);
		}
	}


	for(i = 0; i< rider_num; i++)
	{
		pCur = cliFindClassById(rider_id[i]);
		if(pCur->pure_msec < g_max[pCur->group].pure_msec)
		{
			pCur->gap_sec = (pCur->pure_sec - 1) - g_max[pCur->group].pure_sec;
			pCur->gap_msec = 1000 + pCur->pure_msec - g_max[pCur->group].pure_msec;
		}
		else
		{
			pCur->gap_sec = pCur->pure_sec - g_max[pCur->group].pure_sec;
			pCur->gap_msec = pCur->pure_msec - g_max[pCur->group].pure_msec;
		}
	}

	sort_groups(group_riders, MAX);
	generate_result(group_riders, MAX);

	return 0;
}
