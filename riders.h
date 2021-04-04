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
  	HIBPRiderInfo r_head;
  	int nriders;
}HIBPGroup;

extern HIBPGroup* create_group(int No);
///get a rider by rider's number
extern HIBPRiderInfo* get_rider(HIBPGroup* group, int No);
extern void add_rider(HIBPGroup* group, HIBPRiderInfo* r);

typedef struct
{
    HIBPGroup g_head;
    int ngroups;
}HIBPGroupList;

extern HIBPGroupList* create_grouplist();
extern HIBPGroupList* rider_load_all();

///get a group by group's number
extern HIBPGroup* get_group(HIBPGroupList* groups, int No);
///return the number of groups
extern int get_groups_count(HIBPGroupList* groups);
///add a group to group list
extern void add_group(HIBPGroupList* groups, HIBPGroup* group);

#endif /*RIDERS_H*/
