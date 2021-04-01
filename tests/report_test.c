
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

HIBPStageResult* stage_find_result(HIBPStageResultView* view, int rider_no, int stage);
void init_stage_result(HIBPStageResult* r);

int main()
{
	printf("test report...\n");
	HIBPReportView* view = create_report_view(3);
	assert(view->nitems == 3 );


	return 0;
}
