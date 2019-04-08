#include <stdio.h>
#include "interface.h"
#include "racing_info.h"
#include "riders.h"
#include "results.h"
#include "report.h"

#define WITH_POINTS     1
#define WITH_RFID       1

struct interface g_max[MAX];
struct interface g_ife;




int main(void)
{
	read_start();
	read_end();

	calc_result();
	sort_result();

	generate_report(mode, param);

	return 0;
}

