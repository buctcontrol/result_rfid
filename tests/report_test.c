
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	printf("test report...\n");
	HIBPReportView* view = create_report_view(3);
	assert(view->nitems == 3 );


	return 0;
}
