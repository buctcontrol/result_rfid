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

static void calc_time(HIBPTime* time)
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

static int compare_rider_time(const HIBPRiderInfo* src, const HIBPRiderInfo* dst)
{
	if(   (dst->results[0].pure_sec < src->results[0].pure_sec) 
	   || ((dst->results[0].pure_sec == src->results[0].pure_sec) && (dst->results[0].pure_msec < src->results[0].pure_msec))
	 )
	 {
	 	return 1;	
	 }

	 return 0;
}

static void sort_by_time(HIBPGroupRider* groups, int groups_count)
{
	sort_riders(groups, groups_count, compare_rider_time);
}

static void calc_gap_time(HIBPGroupRider* groups, int groups_count)
{
	int i;
	for(i=0; i<groups_count; i++){
		for(int j=0; j<groups[i].nriders; j++){
			HIBPRiderInfo* rider = &(groups[i].riders[j]);
			PINTERFACE pMax = groups[i].riders[0].results;
			PINTERFACE pCur = rider->results;
			if(pCur->pure_msec < pMax->pure_msec)
			{
				pCur->gap_sec = (pCur->pure_sec - 1) - pMax->pure_sec;
				pCur->gap_msec = 1000 + pCur->pure_msec - pMax->pure_msec;
			}
			else
			{
				pCur->gap_sec = pCur->pure_sec - pMax->pure_sec;
				pCur->gap_msec = pCur->pure_msec - pMax->pure_msec;
			}
		}
	}
}

void stage_on_recv_result(void* view, HIBPTime* t)
{
	HIBPStageReusltView* rview =(HIBPStageReusltView*)view;
	HIBPStageReuslt* item = stage_find_result(rview, t->stage, t->rider_no);
	if(item == NULL){
		item = alloc_result();	
		item->rider_no = t->rider_no;
		add_result(view, t->stage, t->rider_no, item);
	}

	item->update_time(item, t);

	//sort_by_time(get_groups(), get_groups_count());
	//calc_gap_time(get_groups(), get_groups_count());
}



void free_result(void* result)
{
	free(result);
}

////////////////////////////////////////////////////
//stage result operations
void stage_update_time(void* result, HIBPTime* t)
{
	HIBPStageReuslt* r = (HIBPStageReuslt*)result;
	r->rider_no = t->rider_no;
	r->stage = t->stage;
	if(t->is_start){
		if(t->is_transfer){
			r->transfer_result->start_time = t->time;
		}
		else{
			r->stage_result->start_time = t->time;
		}
	}
	else{
		if(t->is_transfer){
			r->transfer_result->end_time = t->time;
		}
		else{
			r->stage_result->end_time = t->time;
		}
	}

	if(r->transfer_result->start_time > 0 && t->transfer_result->end_time > 0){
		r->transfer_result->result_time = r->transfer_result->end_time - r->transfer_result->start_time;
	}

	if(r->stage_result->start_time > 0 && r->stage_result->end_time > 0){
		r->stage_result->result_time = r->stage_result->end_time - r->stage_result->start_time;
	}

}

void init_result(HIBPResult* r)
{
	r->start_time = 0;
	r->end_time = 0;
	r->reuslt_time = 0;
}

void init_stage_result(HIBPStageReuslt* r)
{
	r->rider_no = 0;
	r->stage = -1;
	init_result(&r->transer_result);	
	init_result(&r->stage_result);	
	r->update_time = stage_update_time;
}

HIBPReusltView* alloc_stage_result_view(int nrows, int ncols)
{
	HIBPReusltView* view = (HIBPReusltView*)malloc(sizeof(HIBPReusltView));
	view->nrows = nrows;
	view->rows = (HIBPReusltRow*)malloc(sizeof(HIBPReusltRow) * nrows);
	for(int i=0; i<rows; i++){
		HIBPReusltRow* row = view->rows+i;
		row->ncols = ncols;
		row->cols = (HIBPStageReuslt*)malloc(sizeof(HIBPStageReuslt) * ncols);
		for(int j=0; j<ncols; j++){
			init_stage_result( (HIBPStageReuslt*)(row->cols+i));
		}
	}
}
