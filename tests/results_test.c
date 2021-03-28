
#include "results.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

HIBPStageResult* stage_find_result(HIBPStageResultView* view, int rider_no, int stage);
void init_stage_result(HIBPStageResult* r);

int main()
{
	printf("test table...\n");
	int row=0, col=0;
	HIBPResultTable* tb1 = alloc_result_table(1,1);
	int item=101;
	table_set_item(tb1, row, col, &item);
	int* value = (int*)table_get_item(tb1, row, col);
	assert(*value==101);

	printf("test HIBPStageResult...\n");
	HIBPStageResult* r = (HIBPStageResult*)malloc(sizeof(HIBPStageResult));
	init_stage_result(r);
	HIBPTime t={};
	t.is_transfer=1;
	t.is_start=1;
	t.time = 1000;
	r->update_time(r, &t);
	assert(r->transfer_result.start_time==1000);
	HIBPTime t1={};
	t1.is_transfer=1;
	t1.is_start=0;
	t1.time = 2000;
	r->update_time(r, &t1);
	assert(r->transfer_result.start_time==1000);
	assert(r->transfer_result.end_time==2000);
	assert(r->transfer_result.result_time==1000);
	HIBPTime t2={};
	t2.is_transfer=0;
	t2.is_start=1;
	t2.time = 2000;
	r->update_time(r, &t2);
	assert(r->transfer_result.start_time==1000);
	assert(r->transfer_result.end_time==2000);
	assert(r->transfer_result.result_time==1000);
	assert(r->stage_result.start_time==2000);
	assert(r->stage_result.end_time==0);
	assert(r->stage_result.result_time==0);
	HIBPTime t3={};
	t3.is_transfer=0;
	t3.is_start=0;
	t3.time = 4000;
	r->update_time(r, &t3);
	assert(r->transfer_result.start_time==1000);
	assert(r->transfer_result.end_time==2000);
	assert(r->transfer_result.result_time==1000);
	assert(r->stage_result.start_time==2000);
	assert(r->stage_result.end_time==4000);
	assert(r->stage_result.result_time==2000);

	printf("test HIBPStageResultView...\n");
	HIBPStageResultView* v = alloc_stage_result_view(2, 2);
	assert(v->nrows==2);
	assert(v->results[0].row==v->table->rows[0]);
	assert(v->results[1].row==v->table->rows[1]);
	assert(v->results[0].rider_no==-1);
	assert(v->results[1].rider_no==-1);
	HIBPStageResult* sr =(HIBPStageResult*)v->results[0].row->cols[0];
	assert(sr->stage_result.result_time==0);
	sr = stage_find_result(v, 101, 2);
	assert(sr == NULL);
	sr = stage_find_result(v, 101, -1);
	assert(sr == NULL);
	sr = stage_find_result(v, 101, 1);
	assert(sr != NULL);
	assert(sr->stage_result.result_time==0);

	HIBPTime t4={};
	t4.rider_no=101;
	t4.stage=101;
	t4.is_transfer=0;
	t4.is_start=0;
	t4.time = 4000;
	v->on_recv_time(v, &t4);
	sr = stage_find_result(v, 101, 1);
	assert(sr != NULL);
	assert(sr->stage_result.end_time==0);


	return 0;
}
