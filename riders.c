/*
 * =====================================================================================
 *
 *       Filename:  riders.c
 *
 *    Description: riders info manager 
 *
 *        Version:  1.0
 *        Created:  2019年4月2日 
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "global.h"

#define _PATH_RIDERS "./riders_info.csv"
#define _MAX_RIDERS=1024;


HIBPGroupRider groups[_MAX_GROUPS];
static int group_count=0;

HIBPRiderInfo* get_rider_info(int No)
{
	if(group_count == 0 )
		read_all_riders();

	for(int i=0; i<group_count; i++){
		for(int j=0; j<group[i].nriders; j++){
			if(group[i].riders[j].number == No)
				return group[i].riders+j;
		}
	}

	return NULL; 
}

HIBPGroupRider* get_groups()
{
	return groups;
}

int get_groups_count()
{
	return group_count;
}

static void sort_by_group(HIBPRiderInfo riders[], int nriders)
{
}

static void copy_rider(HIBPRiderInfo* src, HIBPRiderInfo* dst)
{
	if(src == dst)
		return;

	src->number = dst->number;
	src->group= dst->group;
	strcpy(src->name, dst->name);
	strcpy(src->team, dst->team);
}

static void init_group_rider(HIBPGroupRider group_riders[], HIBPRiderInfo riders[], int nriders)
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
			copy_rider(&group_riders[i].riders[k] ,&riders[j]);
			k++;
		}
		else
		{
			group_riders[i].nriders = k;
			i++;
			k=0;
			copy_rider(&group_riders[i].riders[k] ,&riders[j]);
			k++;
			group_riders[i].group = riders[j].group;
		}
	}
	group_riders[i].nriders = k;
	groups_count = i;
}

static void read_all_riders()
{
	char buf[128];
	char name[64], team[128];
	int num=-1, group=-1;
	int i=0,j=0,k=0;
	HIBPRiderInfo riders[_MAX_RIDERS];
	int riders_count=0;

	memset(&groups, 0, sizeof(groups));

	file_open("rider_info.csv", "r");
	while( file_gets(buf) != NULL)
	{
		sscanf(buf, "%d,%s,%s,%d", &num, name, team, &group);
		riders[i].number = num;
		riders[i].group = group;
		strcpy(riders[i].name, name);
		strcpy(riders[i].team, team);
		i++;
	}
	riders_count=i;

	sort_by_group(riders);
	init_group_rider(groups, riders, riders_count);
	file_close();
}


static void read_racing_riders()
{
}
