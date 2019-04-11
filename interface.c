///interface.c


#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "racing_info.h"
#include "results.h"
#include "report.h"

struct interface g_ife;


int main(void)
{
	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);

	load_racing_info();	
	char* mode = racing_get_mode();
	if( strcmp(mode, "stage") == 0 )
	{
		char fname_start[64];
		char fname_finish[64];
		for(int i=0; i<racing_get_stages(); i++)
		{
			memset(&g_ife, 0, sizeof(g_ife));
			INIT_LIST_HEAD(&g_ife.list);
			init_riders();

			sprintf(fname_start, "stage%d_start.txt", i+1);
			sprintf(fname_finish, "stage%d_end.txt", i+1);
			if( read_start(fname_start) < 0 )
				continue;

			read_finish(fname_finish);

			calc_result();

			generate_report_stage(i+1);
		}
	}
	else
	{
		fprintf(stderr, "[%s] not surpport!\n", mode);
	}

	return 0;
}

