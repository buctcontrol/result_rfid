///interface.c


#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "racing_info.h"
#include "results.h"
#include "report.h"
#include <sys/resource.h>

struct interface g_ife;
static char* result_file = "end_result_superpi_001.txt";

void process_stage()
{
	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);

	init_riders();
	read_start(result_file);

	calc_result();
	generate_report_stage(1);
}

int main(int argc, char** argv)
{
	struct rlimit r;
	r.rlim_cur= 8*1024*1024*10;//stack size 80MB
	setrlimit(RLIMIT_STACK, &r);
	getrlimit(RLIMIT_STACK, &r);
	printf("stack limit:cur=%ld\n", r.rlim_cur);

	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);

	load_racing_info();	
	process_stage();

	return 0;
}

