/*
 * =====================================================================================
 *
 *       Filename:  riders.h
 *
 *    Description:  用户名单预置表
 *
 *        Version:  1.0
 *        Created:  2018年12月17日 12时40分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef RIDERS_H
#define RIDERS_H

#define _MAX_RIDERS	512
#define _PATH_RIDERS 	"./riders_info.csv"

#include "interface.h"

extern void init_riders();
extern int get_total_groups();
extern int get_total_riders();

typedef struct
{
    unsigned int    number;
    char            name[64];
    char            team[128];
    int 	    	group;
    char qualify_r;//qualify results, 0-normal, 1-dnq, 2-dns, 3->dnf
}HIBPRiderInfo;

typedef struct
{
  HIBPRiderInfo* riders;
  int nriders;
}HIBPRiderList;

///get a rider by rider's number
static HIBPRiderInfo* get_rider(HIBPRiderList* list, int No);
static int get_total_riders(HIBPRiderList* list);
static void add_rider(HIBPRiderList* list, HIBPRiderInfo* r);


typedef struct
{
	int group_no;
	HIBPRiderList riders;
}HIBPGroup;

typedef struct
{
    HIBPGroup* groups;
    int ngroups;
}HIBPGroupList;

///get a group by group's number
static HIBPGROUP* get_group(HIBPGroupList* groups, int No);
///return the number of groups
static int get_groups_count(HIBPGroupList* groups);
///add a group to group list
static void add_group(HIBPGroupList* groups, HIBPGROUP* group);

///if @return 1 so swap src and dst, if return 0 do not swap them. 
//typedef int (*fcompare_rider)(const HIBPRiderInfo* src, const HIBPRiderInfo* dst);
//extern void sort_riders(HIBPGroupRider* groups, int groups_count, fcompare_rider fcompare);

#endif /*RIDERS_H*/
