///results.h

#ifndef RESULTS_H
#define RESULTS_H

#include "timeing.h"
#include <stdint.h>


typedef struct 
{
    uint64_t start_time;  //ms
    uint64_t end_time;    //ms
    uint64_t result_time; //ms
}HIBPResult;

typedef void (*update_time_f)(void* result, HIBPTime* t);
typedef void (*on_recv_time_f)(void* result_view, HIBPTime* t);
void free_result(void* result);



//////////////////////////////////////////////////////////////
typedef struct
{
	void** cols;
	int ncols;
}HIBPResultRow;

typedef struct
{
	HIBPResultRow** rows;
	int nrows;
}HIBPResultTable;

extern HIBPResultTable* alloc_result_table(int nrows, int ncols);
extern HIBPResultRow* table_get_row(HIBPResultTable* view, int row);
extern void table_set_item(HIBPResultTable* view, int row, int col, void* value);
extern void* table_get_item(HIBPResultTable* view, int row, int col);



//////////////////////////////////////////////////////////////
typedef struct 
{
	//operations
	update_time_f update_time;

    HIBPResult transfer_result;
    HIBPResult stage_result;
	int score;
	int qualify;//qualify results, 0-normal, 1-dnq, 2-dns, 3->dnf
}HIBPStageResult;

typedef	struct {
		int rider_no;
		HIBPResultRow* row;
}Result;

typedef struct
{
	//operations
	on_recv_time_f on_recv_time;

	Result* results;	
	int nrows;

	HIBPResultTable *table;
}HIBPStageResultView;

extern void* alloc_stage_result_view(int nrows, int ncols);

#endif /*RESULTS_H*/
