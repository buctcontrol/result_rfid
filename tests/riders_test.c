
#include "riders.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


void set_group_name(char* gname, int No)
{
	strcpy(gname, "test group");
}
int main()
{
	printf("test riders...\n");

	HIBPGroupList groups;

	HIBPGroup g;
	g.group_no=0;
	add_group(&groups, &g);
	assert(get_groups_count(&groups)==1);
	HIBPGroup* pg = get_group(&groups, 0);
	assert(pg == &g);



	return 0;
}
