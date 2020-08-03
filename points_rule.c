///point_rule.c

#include "global.h"
#include "utils.h"

#define POINTS_FILE "points_rule.csv"

int get_points(int position, int group)
{
	int points=0;
	int col;
	char buf[128];

	if( !file_open(POINTS_FILE, "r") )
		return 0;

	file_gets(buf, 128);
	//col =  find_column(buf, groupStr[group].str);
	if(group == WOMAN)
		col =  find_column(buf,"Woman");
	else
		col =  find_column(buf, "Man");
		
	if(col < 0 )
		return 0;

	while( file_gets(buf, 128) != NULL)
	{
		if(position == get_column_i(buf, 0)){
			points = get_column_i(buf, col);
			break;
		}
	}

	return points;
}

/*
#include <stdio.h>
#include "interface.h"
struct interface g_ife;

int main()
{
	int p = get_points(1, WOMAN);
	printf("%d\n", p);
	p = get_points(20, WOMAN);
	printf("%d\n", p);
	p = get_points(100, WOMAN);
	printf("%d\n", p);
	p = get_points(101, WOMAN);
	printf("%d\n", p);
	p = get_points(3, NEWBIE);
	printf("%d\n", p);
	p = get_points(30, ELITE);
	printf("%d\n", p);
	return 0;
}
*/
