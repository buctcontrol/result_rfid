///interface.c


#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "racing_info.h"
#include "results.h"
#include "report.h"

struct interface g_ife;

void process_transfer(int i)
{
	char fname_start[64];
	char fname_finish[64];
	char report_fname[64];

	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);

	sprintf(fname_start, "t%ds.txt", i+1);
	sprintf(fname_finish, "t%de.txt", i+1);
	read_start(fname_start);
	read_finish(fname_finish);

	calc_result();
	sprintf(report_fname, "result_transfer_%d.csv", i+1);
	save_report(get_groups(), get_groups_count(), report_fname);
}

void process_stage(int i)
{
	char fname_start[64];
	char fname_finish[64];

	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);

	sprintf(fname_start, "s%ds.txt", i+1);
	sprintf(fname_finish, "s%de.txt", i+1);
	read_start(fname_start);
	read_finish(fname_finish);

	calc_result();
	generate_report_stage(i+1);
}

int main(void)
{
	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);

	load_racing_info();	
	char* mode = racing_get_mode();
	if( strcmp(mode, "stage") == 0 )
	{
		for(int i=0; i<racing_get_stages(); i++)
		{
			init_riders();

			if(is_has_transfer(i+1))
				process_transfer(i);

			process_stage(i);
		}
	}
	else
	{
		fprintf(stderr, "[%s] not surpport!\n", mode);
	}

	return 0;
}

