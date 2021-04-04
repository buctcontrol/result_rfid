
#include "riders.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int main()
{
	printf("test riders...\n");

	HIBPGroupList* groups = create_grouplist();

	HIBPGroup* g = create_group(0);
	add_group(groups, g);
	assert(get_groups_count(groups)==1);
	HIBPGroup* pg = get_group(groups, 0);
	assert(pg == g);

    HIBPRiderInfo r1;
    r1.number = 100;
    add_rider(g, &r1);
    assert(g->nriders == 1);
    assert(get_rider(g, 100) == &r1);

    HIBPRiderInfo r2;
    r2.number = 101;
    add_rider(g, &r2);
    assert(g->nriders == 2);
    assert(get_rider(g, 101) == &r2);

    free(groups);
    free(g);


	groups = rider_load_all();
    assert(groups!=NULL);
	g = get_group(groups, 0);
    assert(g==NULL);
	g = get_group(groups, 4);
    assert(g->nriders == 4);
    HIBPRiderInfo* r3 = get_rider(g, 602);
    assert(r3!=NULL);
    assert(r3->number == 602);
    printf("rider{%d,%s,%s,%d,%s}\n", r3->number,r3->name,r3->team,r3->group,r3->group_name);

    //free_grouplist(groups);

	return 0;
}
