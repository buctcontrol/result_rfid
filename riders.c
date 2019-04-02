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

static HIBPRiderInfo riders[_MAX_RIDERS];
static int riders_count=0;

HIBPRiderInfo* get_rider_info(int No)
{
	for(int i=0; i<riders_count; i++)
	{
		if(riders[i].number == No)
			return riders+i;
	}

	return NULL; 
}

void read_all_riders()
{
}

void read_racing_riders()
{
}
