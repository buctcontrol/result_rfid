///results.h

#ifndef RESULTS_H
#define RESULTS_H

#include "timeing.h"


typedef struct 
{
    uint64_t start_time;  //ms
    uint64_t end_time;    //ms
    uint64_t result_time; //ms
}HIBPResult;

typedef void (*update_time_f)(void* result, HIBPTime* t);
void free_result(void* result);

//////////////////////////////////////////////////////////////
typedef struct 
{
	//operations
	update_time_f update_time;

    int rider_no;
	int stage;//stage No.
    HIBPResult transfer_result;
    HIBPResult state_result;

}HIBPStageReuslt;

typedef sturct
{
	void* results;
	int rider_no;
	int ncloumns;
}HIBPResultRow;

typedef struct
{
	HIBPResultRow* results;
	int nrows;
}HIBPReusltView;

HIBPReusltView* alloc_stage_result_view(int nstages);


extern void on_recv_time(HIBPStageReusltView* view, HIBPTime* t);

#endif /*RESULTS_H*/
