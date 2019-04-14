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

#include "riders.h"
#include "utils.h"
#include <string.h>



HIBPGroupRider groups[_MAX_GROUPS];
static int groups_count=0;

static void read_all_riders();
void init_riders()
{
	read_all_riders();
}


HIBPRiderInfo* get_rider_info(int No)
{
	return get_rider_info_g(groups, No);
}

HIBPRiderInfo* get_rider_info_g(HIBPGroupRider* groups, int No)
{
	for(int i=0; i<_MAX_GROUPS; i++){
		for(int j=0; j<groups[i].nriders; j++){
			if(groups[i].riders[j].number == No)
				return groups[i].riders+j;
		}
	}

	return 0; 
}

HIBPGroupRider* get_groups()
{
	return groups;
}

int get_groups_count()
{
	return groups_count;
}

void sort_riders(HIBPGroupRider* groups, int groups_count, fcompare_rider fcompare)
{
	HIBPRiderInfo* min = NULL;
	for(int i=0; i<groups_count; i++){
		for(int j=0; j<groups[i].nriders; j++){
				HIBPRiderInfo* cur = &(groups[i].riders[j]);
				min = cur;
			for(int k=j+1; k<groups[i].nriders; k++){
				HIBPRiderInfo* rider = &(groups[i].riders[k]);
				if( fcompare(min, rider) ) 
					min = rider;
			}

			if(min != cur )
				swap_rider(min, cur);
				
		}
	}

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
	memcpy(src->results, dst->results, sizeof(dst->results));
	strcpy(src->name, dst->name);
	strcpy(src->team, dst->team);
	memcpy(src->result_time, dst->result_time, sizeof(dst->result_time));
}

void swap_rider(HIBPRiderInfo* src, HIBPRiderInfo* dst)
{
	if(src == dst)
		return;

	HIBPRiderInfo tmp;
	copy_rider(&tmp, src);
	copy_rider(src, dst);
	copy_rider(dst, &tmp);
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
	groups_count = i+1;
}

static void read_all_riders()
{
	char buf[128];
	int i=0;
	HIBPRiderInfo riders[_MAX_RIDERS];
	int riders_count=0;

	memset(&groups, 0, sizeof(groups));

	file_open(_PATH_RIDERS, "r");
	char val[128]={0};
	while( file_gets(buf, 127) != NULL)
	{
		riders[i].number = get_column_i(buf, 0);
		riders[i].group = get_column_i(buf, 3);
		strcpy(riders[i].name, get_column_str(buf, 1, val));
		strcpy(riders[i].team, get_column_str(buf, 2, val));
        	riders[i].results[0].pure_sec  = 86399;
        	riders[i].results[0].pure_msec = 999;
        	riders[i].results[0].sec  = 0;
        	riders[i].results[0].msec = 0;
        	riders[i].results[0].end_sec  = 0;
        	riders[i].results[0].end_msec = 0;
		i++;
	}
	riders_count=i;

	sort_by_group(riders, riders_count);
	init_group_rider(groups, riders, riders_count);
	file_close();
}


/*#include <stdio.h>

int main()
{
	read_all_riders();
	HIBPRiderInfo *r = get_rider_info(0);
	HIBPRiderInfo *r2 = get_rider_info(116);
	return 0;
}
*/
