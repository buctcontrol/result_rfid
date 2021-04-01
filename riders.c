#include "utils.h"
#include "global.h"
#include <string.h>
#include "list.h"


static void read_all_riders(HIBPGroupList* groups )
HIBPGroupList* rider_load_all()
{
	HIBPGroupList* groups = (HIBPGroupList*)malloc(sizeof(HIBPGroupList));
	groups->ngroups=0;
	read_all_riders(groups);
}

static HIBPGROUP* get_group(HIBPGroupList* groups, int No)
{
	HIBPGROUP* group = NULL;
	struct list_head* pos = NULL;

	list_for_each(pos, &groups->groups.list)
	{
		group = list_entry(pos, HIBPGROUP, list);
		if(group->group_no = No)
			return group;
	}

	return NULL;
}

static HIBPGROUP* add_group(HIBPGroupList* groups, HIBPGroup* group)
{
	list_add_tail(&group->list, &groups->groups.list);
	groups->ngroups++;
}

static HIBPGROUP* add_rider(HIBPGroup* group, HIBPRiderInfo* r)
{
	list_add_tail(&r->list, &group.list);
	group->nriders++;
}

static void read_all_riders(HIBPGroupList* groups )
{
	char buf[128];
	int i=0;
	int riders_count=0;

	file_open(_PATH_RIDERS, "r");
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
			g = (HIBPGroup*)malloc(sizeof(HIBPGroup));
			g->nriders=0;
			g->group_no = rider->group;
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
