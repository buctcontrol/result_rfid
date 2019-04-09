#include <string.h>
#include "interface.h"
#include "racing_info.h"
#include "riders.h"
#include "results.h"
#include "report.h"

struct interface g_ife;


int main(void)
{
	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);

	read_start();
	read_finish();

	calc_result();

	generate_report();

	return 0;
}

