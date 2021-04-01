///racing_info.c
//
//

#include <string.h>
#include <stdio.h>
#include "global.h"
#include "riders.h"
#include "results.h"
#include "report.h"

#define MAX_STAGES 10

char* get_racing_mode(void* racing)
{
	HIBPRacing* rm = (HIBPRacing*)racing;
	return rm->mode;
}

HIBPRacing* create_racing_info()
{
	char mode = conf_get_field_str("Racing");
	if(strcmp(mode, "stage") == 0){
    	return (HIBPRacing*)alloc_stage_racing();
	}

	return NULL;
}

void delete_racing_info(void* racing)
{
    free(racing);
}

void load_racing_info(HIBPRacing* racing)
{
	racing->load_info(racing);
	racing->create_result_view(racing);
}

void process_racing(HIBPRacing* racing)
{
	racing->process(racing);
}



////////////////////////////////////////////////////////////////////////
//stage mode
typedef struct
{
	///operations
	load_info_f load_info;
	ceate_result_view_f create_result_view;
	process_racing_f process;

	HIBPGroupList* groups;
	HIBPStageResultView* result_view;

	const char* mode="stage";
	int nstages; //number of stages
	struct{
		struct{
			int transfer_shut;//transfer shut time in seconds
		}shut[MAX_GROUPS];
	}stags[MAX_STAGES];

}HIBPRacing_Stage;

HIBPRacing_Stage* alloc_stage_racing()
{
	HIBPRacing_Stage* r = (HIBPRacing_Stage*)malloc(sizeof(HIBPRacing_Stage));
	r->laod_info = load_stage_racing_info;
	r->create_result_view = create_stage_results_view;
	r->process = stage_process_racing;
}

void load_transfer_shut(HIBPRacing_Stage* r, char* file);
void load_stage_racing_info(void* racing)
{
	HIBPRacing_Stage* r = (HIBPRacing_Stage*)racing;	
	r->nstages = conf_get_field_int("Stage", "stage");
	load_transfer_shut(r, conf_get_field_str("Stage", "transfer_shut"));
	groups = rider_load_all();
}

void create_stage_result_view(void* racing)
{
	HIBPRacing_Stage* r = (HIBPRacing_Stage*)racing;	
	r->result_view = alloc_stage_result_view(r->nstages);
}

//int is_has_transfer(int stage);
//void process_transfer(int i);
//void process_transfer(int i);
void stage_process_racing(void* racing)
{
	HIBPRacing_Stage* r = (HIBPRacing_Stage*)racing;	
	for(int i=0; i<r->nstages; i++){
		if(is_has_transfer(i) ){
			process_transfer(r, i);
		}
		process_stage(r, i);
	}
}

void load_transfer_shut(HIBPRacing_Stage* r, char* file)
{
}

int is_has_transfer_group(int group)
{
	return 1;
}

int is_has_transfer(int stage)
{
	char fname[64];
	sprintf(fname, "t%ds.txt", stage);
	FILE* fp = fopen(fname, "r");
	if(fp)
		fclose(fp);

	return fp!=NULL?1:0;
}

int get_transer_shut_time(void* racing, int group, int stage)
{
	if(group >= MAX_GROUPS){
		fprintf(stderr, "get_transfer_shut_time: group out idx");
		exit(1);
	}

	if(stage > MAX_STAGES){
		fprintf(stderr, "get_transfer_shut_time: stage out idx");
		exit(1);
	}

	HIBPRacing_Stage* r = (HIBPRacing_Stage*)racing;	
	return r->stages[stage].transfer_shut[group].shut;
}

void process_transfer(HIBPRacing_Stage* racing, int i)
{
	char fname_start[64];
	char fname_finish[64];
	char report_fname[64];

	sprintf(fname_start, "t%ds.txt", i+1);
	sprintf(fname_finish, "t%de.txt", i+1);
	sprintf(report_fname, "result_transfer_%d.csv", i+1);
	process_result(racing, fname_start, fname_finish, report_name);
}

void process_stage(HIBPRacing_Stage* racing, int i)
{
	char fname_start[64];
	char fname_finish[64];
	char report_fname[64];
	sprintf(fname_start, "s%ds.txt", i+1);
	sprintf(fname_finish, "s%de.txt", i+1);
	sprintf(report_fname, "result_stage_%d.csv", i+1);
	process_result(racing, fname_start, fname_finish, report_name);
}


void process_result(HIBPRacing_Stage* racing,
	char fname_start[64],
	char fname_finish[64],
	char report_fname[64]
)
{
	HIBPTime stime;
	while(true){
		int r = timeing_read(fname_start, &stime);
		if( r == 0){
			break;
		}
		racing->results_view->on_recv_result(racing->results_view, &stime);
	}

	while(true){
		int r = timeing_read(fname_finish, &stime);
		if( r == 0){
			break;
		}
		racing->results_view->on_recv_result(racing->results_view, &stime);
	}

	sprintf(report_fname, "result_transfer_%d.csv", i+1);
	report_update(racing->groups, racing->result_view, report_fname);
}



////////////////////////////////////////////////////////////////////////
//round mode
typedef struct{
	///operations
	load_info_f load_info;
	ceate_result_view_f create_result_view;
	process_racing_f process;

	const char* mode="stage";
	int nrounds;
	int cur_round;
}HIBPRacing_Round;
