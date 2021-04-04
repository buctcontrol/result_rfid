//results.c
//

#include "global.h"
#include "utils.h"
#include "results.h"
#include "timeing.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static void calc_time(HIBPResult* time)
{
	time->result_time = time->end_time - time->start_time;
}

double to_seconds(uint64_t ms)
{
	return (double)ms/1000;
}

static double calc_speed(double length, uint64_t ms)
{
	return (length * 3.6) / to_seconds(ms);
}

static int compare_time(const HIBPStageResult* src, const HIBPStageResult* dst)
{
	if( src->stage_result.result_time < dst->stage_result.result_time ){
	 	return 1;	
	 }

	 return 0;
}

static void sort_by_time(HIBPStageResultView* view)
{
	//sort_riders(groups, groups_count, compare_rider_time);
}

static void calc_gap_time(HIBPStageResultView* view)
{
}



////////////////////////////////////////////////////////////////////////////////////////
HIBPResultTable* alloc_result_table(int nrows, int ncols)
{
	HIBPResultTable* view = (HIBPResultTable*)malloc(sizeof(HIBPResultTable));
	view->nrows = nrows;
	view->rows = (HIBPResultRow**)malloc(sizeof(HIBPResultRow)*nrows);
	for(int i=0; i<nrows; i++){
		HIBPResultRow* row = (HIBPResultRow*)malloc(sizeof(HIBPResultRow));
		view->rows[i] = row;
		row->cols = (void**)malloc(sizeof(long)*ncols);
		row->ncols = ncols;
	}

	return view;
}

void free_result_table(HIBPResultTable* view)
{
}

HIBPResultRow* table_get_row(HIBPResultTable* view, int row)
{
	if(row < 0 || row > view->nrows)
		return 0;

	return view->rows[row];
}

void table_set_item(HIBPResultTable* view, int row, int col, void* value)
{
	if(row < 0 || row > view->nrows)
		return ;

	HIBPResultRow* prow = view->rows[row];
	if(col < 0 || col > prow->ncols)
		return ;

	prow->cols[col] = value;
}

void* table_get_item(HIBPResultTable* view, int row, int col)
{
	if(row < 0 || row > view->nrows)
		return 0;

	HIBPResultRow* prow = view->rows[row];
	if(col < 0 || col > prow->ncols)
		return 0;

	return prow->cols[col];
}




////////////////////////////////////////////////////////////////////////////////////////////////
HIBPStageResult* stage_find_result(HIBPStageResultView* view, int rider_no, int stage);
void init_stage_result(HIBPStageResult* r);
void stage_add_result(HIBPStageResultView* view, int rider_no, int stage, HIBPStageResult* item);
void stage_on_recv_time(void* view, HIBPTime* t)
{
	HIBPStageResultView* rview =(HIBPStageResultView*)view;
	HIBPStageResult* item = stage_find_result(rview, t->stage, t->rider_no);
	if(item == NULL){
		return;
	}

	item->update_time(item, t);

	//sort_by_time(get_groups(), get_groups_count());
	//calc_gap_time(get_groups(), get_groups_count());
}

Result* stage_get_result_f(void* result_view, int rider_no)
{
	HIBPStageResultView* rview =(HIBPStageResultView*)view;
	for(int i=0; i<rview->nrows; i++){
       if(rview->results[i].rider_no == rider_no)
           return rview->results+i;
    }

    return NULL;
}

void free_result(void* result)
{
	free(result);
}

////////////////////////////////////////////////////
//stage result operations
void stage_update_time(void* result, HIBPTime* t)
{
	HIBPStageResult* r = (HIBPStageResult*)result;
	if(t->is_start){
		if(t->is_transfer){
			r->transfer_result.start_time = t->time;
		}
		else{
			r->stage_result.start_time = t->time;
		}
	}
	else{
		if(t->is_transfer){
			r->transfer_result.end_time = t->time;
		}
		else{
			r->stage_result.end_time = t->time;
		}
	}

	if(r->transfer_result.start_time > 0 && r->transfer_result.end_time > 0){
		r->transfer_result.result_time = r->transfer_result.end_time - r->transfer_result.start_time;
	}

	if(r->stage_result.start_time > 0 && r->stage_result.end_time > 0){
		r->stage_result.result_time = r->stage_result.end_time - r->stage_result.start_time;
	}

}

void init_result(HIBPResult* r)
{
	r->start_time = 0;
	r->end_time = 0;
	r->result_time = 0;
}

void init_stage_result(HIBPStageResult* r)
{
	init_result(&r->transfer_result);	
	init_result(&r->stage_result);	
	r->update_time = stage_update_time;
}

void* alloc_stage_result_view(int nrows, int ncols)
{
	HIBPResultTable* table = alloc_result_table(nrows, ncols);
	HIBPStageResultView* view = (HIBPStageResultView*)malloc(sizeof(HIBPStageResultView));
	view->on_recv_time = stage_on_recv_time;
	view->get_result = stage_get_result;
	view->nrows = nrows;
	view->results = (Result*)malloc(sizeof(Result)); 
	view->table = table;
	for(int i=0; i<nrows; i++){
		HIBPResultRow* row = table_get_row(table, i);
		for(int j=0; j<ncols; j++){
			HIBPStageResult* item = (HIBPStageResult*)malloc(sizeof(HIBPStageResult));
			init_stage_result(item);
			row->cols[j] = item; 
		}
		Result r = {-1, row};
		view->results[i] = r; 
	}
	return view;
}

HIBPStageResult* stage_find_result(HIBPStageResultView* view, int rider_no, int stage)
{
	HIBPStageResult* item = NULL; 
	for(int i=0; i<view->nrows; i++){
		if(view->results[i].rider_no == -1 || view->results[i].rider_no == rider_no){
			Result* r = view->results+i;
			if(stage>=0 && stage < r->row->ncols){
				item = (HIBPStageResult*)r->row->cols[stage];	
				break;
			}
		}
	}

	return item;
}

static const char* fname = "stages_result.csv";	
HIBPStageResult* stage_save_result(HIBPStageResultView* view)
{
}

HIBPStageResult* stage_load_result(HIBPStageResultView* view)
{
	
}
