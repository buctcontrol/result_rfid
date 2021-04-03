#ifndef RIDERS_H
#define RIDERS_H

#define _PATH_RIDERS 	"./riders_info.csv"

#include "interface.h"

typedef struct _rider
{
	struct list_head list;
    unsigned int    number;
    char            name[64];
    char            team[128];
    int 	    	group;
    char            group_name[128];
}HIBPRiderInfo;


typedef struct 
{
	struct list_head list;
	int group_no;
  	HIBPRiderInfo riders;
  	int nriders;
}HIBPGroup;

///get a rider by rider's number
extern HIBPRiderInfo* get_rider(HIBPGroup* group, int No);
extern void add_rider(HIBPGroup* group, HIBPRiderInfo* r);

typedef struct
{
    HIBPGroup groups;
    int ngroups;
}HIBPGroupList;

extern HIBPGroupList* rider_load_all();

///get a group by group's number
extern HIBPGroup* get_group(HIBPGroupList* groups, int No);
///return the number of groups
extern int get_groups_count(HIBPGroupList* groups);
///add a group to group list
extern void add_group(HIBPGroupList* groups, HIBPGroup* group);

///if @return 1 so swap src and dst, if return 0 do not swap them. 
//typedef int (*fcompare_rider)(const HIBPRiderInfo* src, const HIBPRiderInfo* dst);
//extern void sort_riders(HIBPGroupRider* groups, int groups_count, fcompare_rider fcompare);

#endif /*RIDERS_H*/
