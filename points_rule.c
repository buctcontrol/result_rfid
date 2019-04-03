
int get_points(int position, int group)
{
	int points=0;
	int col;
	char buf[128];

	file_gets(buf);
	col =  find_column(buf, groupStr[group]);
	file_open("points_rule.csv", "r");
	while( file_gets(buf) != NULL)
	{
		if(position == get_column_i(buf, 0){
			points = get_column_i(buf, col);
			break;
		}
	}

	return points;
}
