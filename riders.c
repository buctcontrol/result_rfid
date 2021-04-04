#include "riders.h"
#include "utils.h"
#include "global.h"
#include <string.h>
#include "list.h"


HIBPGroupList* create_grouplist()
{
	HIBPGroupList* groups = (HIBPGroupList*)malloc(sizeof(HIBPGroupList));
	INIT_LIST_HEAD(&groups->g_head.list);
	INIT_LIST_HEAD(&groups->g_head.r_head.list);
    groups->g_head.r_head.number=-1;
    groups->g_head.group_no=-1;
	groups->ngroups=0;
    return groups;
}

HIBPGroup* create_group(int No)
{
	HIBPGroup* g = (HIBPGroup*)malloc(sizeof(HIBPGroup));
	INIT_LIST_HEAD(&g->r_head.list);
    g->r_head.number=-1;
	g->nriders=0;
	g->group_no = No;
    return g;
}

void read_all_riders(HIBPGroupList* groups );
HIBPGroupList* rider_load_all()
{
    HIBPGroupList* groups = create_grouplist();
    read_all_riders(groups);
    return groups;
}

int get_groups_count(HIBPGroupList* groups)
{
	return groups->ngroups;
}

HIBPGroup* get_group(HIBPGroupList* groups, int No)
{
    if(groups == NULL)
        return NULL;

	HIBPGroup* group = NULL;
	struct list_head* pos = NULL;

	list_for_each(pos, &groups->g_head.list)
	{
		group = list_entry(pos, HIBPGroup, list);
		if(group->group_no == No)
			return group;
	}

	return NULL;
}

void add_group(HIBPGroupList* groups, HIBPGroup* group)
{
	list_add_tail(&group->list, &groups->g_head.list);
	groups->ngroups++;
}

void add_rider(HIBPGroup* group, HIBPRiderInfo* r)
{
	list_add_tail(&r->list, &group->r_head.list);
	group->nriders++;
}

HIBPRiderInfo* get_rider(HIBPGroup* group, int No)
{
	HIBPRiderInfo* rider = NULL;
	struct list_head* pos = NULL;

	list_for_each(pos, &group->r_head.list)
	{
		rider = list_entry(pos, HIBPRiderInfo, list);
		if(rider->number == No)
			return rider;
	}

	return NULL;
}

void set_group_name(char* name, int group_no)
{
    strcpy(name, groupStr[group_no].str);
}

void read_all_riders(HIBPGroupList* groups )
{
	char buf[128];
	int i=0;
	int riders_count=0;

	if( !file_open(_PATH_RIDERS, "r") ){
        printf("file{%s] open failed.", _PATH_RIDERS);
        return;
    }
	char val[128]={0};
	while( file_gets(buf, 127) != NULL)
	{
		HIBPRiderInfo* rider = (HIBPRiderInfo*)malloc(sizeof(HIBPRiderInfo));
		rider->number = get_column_i(buf, 0);
		rider->group = get_column_i(buf, 3);
		strcpy(rider->name, get_column_str(buf, 1, val));
		strcpy(rider->team, get_column_str(buf, 2, val));
		set_group_name(rider->group_name, rider->group);
		i++;
		HIBPGroup* g = get_group(groups, rider->group);	
		if(g == NULL){
			g = create_group(rider->group);
			add_group(groups, g);
		}
		add_rider(g, rider);

	}

	file_close();
}

/*
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
*/
