///point_rule.c

#include "global.h"
#include "utils.h"


int get_points(int position, int group)
{
	int points=0;
	int col;
	char buf[128];

	file_gets(buf, 128);
	//col =  find_column(buf, groupStr[group].str);
	if(group == WOMAN)
		col =  find_column(buf,"Woman");
	else
		col =  find_column(buf, "Man");
		
	file_open("points_rule.csv", "r");
	while( file_gets(buf, 128) != NULL)
	{
		if(position == get_column_i(buf, 0)){
			points = get_column_i(buf, col);
			break;
		}
	}

	return points;
}
