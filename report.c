
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "utils.h"
#include <string.h>

HIBPReportView* create_report_view(int nriders)
{
	HIBPReportView* view = (HIBPReportView*)malloc(sizeof(HIBPReportView));
	view->nitems = nriders;
	view->items = (HIBPReportItem*)malloc(sizeof(HIBPReportItem*)*nriders); 
}

typedef int (*compare_f)(const HIBPReportItem* src, const HIBPReportItem* dst);
static int stage_compare_rider_score(const HIBPReportItem* src, const HIBPReportItem* dst);
static void stage_sort_report(HIBPReportView* report, compare_f fcompare);
static void rank_report(HIBPReportView* report);
static void stage_save_report(HIBPReportView* report, const char* filename);
static int stage_calc_total_score(Result* result);
void stage_update_report(HIBPReportView* report, HIBPGroupList* groups, void* results)
{
	HIBPStageResultView* result_view = (HIBPStageResultView*)results;
	int k=0;
	struct list_head* pos = NULL;
	list_for_each(pos, &groups->g_head.list)
	{
		HIBPGroup* group = list_entry(pos, HIBPGroup, list);
		struct list_head* posr = NULL;
		list_for_each(posr, &group->r_head.list)
		{
			HIBPRiderInfo* rider = list_entry(posr, HIBPRiderInfo, list);
			report->items[k].rider = rider;
			report->items[k].result = result_view->get_result(result_view, rider->number);
			report->items[k].score = stage_calc_total_score(report->items[k].result);
			k++;
		}
	}

	stage_sort_report(report, stage_compare_rider_score);
	rank_report(report);
	stage_save_report(report, "result.csv");
}

static int stage_calc_total_score(Result* result)
{
    int score=0;
    int nstages = result->row->ncols;
	for(int k=0; k<nstages; k++){
	    HIBPStageResult* r = (HIBPStageResult*)result->row->cols[k];
        score += r->score;
    }

    return score;
}

static int stage_compare_rider_score(const HIBPReportItem* src, const HIBPReportItem* dst)
{
	if(dst->score > src->score) 
	 	return 1;	

    int last_stage = dst->result->row->ncols-2;
	HIBPStageResult* src_r = (HIBPStageResult*)src->result->row->cols[last_stage];
	HIBPStageResult* dst_r = (HIBPStageResult*)dst->result->row->cols[last_stage];
	if(dst->score == src->score){ 
		if(dst_r->score > src_r->score)
		{
			return 1;
		}
	}

	return 0;
}

static void swap_item(HIBPReportItem* src, HIBPReportItem* dst)
{
	HIBPReportItem tmp = *src;
	*src = *dst;
	*dst = tmp;
}

static void stage_sort_report(HIBPReportView* report, compare_f fcompare)
{
	HIBPReportItem* min = NULL;
	int n=0;
	for(int i=0; i<report->ngroups; i++){
		for(int j=0; j<report->groups[i]; j++){
			HIBPReportItem* cur = report->items+n;
			n++;
			min = cur;
			for(int k=n+1; k<report->groups[i]; k++){
				HIBPReportItem* item = report->items+k;
				if( fcompare(min, item) ) 
					min = item;
			}

			if(min != cur )
				swap_item(min, cur);
		}
	}

}

static void rank_report(HIBPReportView* report)
{
	HIBPRiderInfo* min = NULL;
	int n=0;
	for(int i=0; i<report->ngroups; i++){
		for(int j=0; j<report->groups[i]; j++){
			HIBPReportItem* cur = report->items+n;
			cur->rank = n+1;
			n++;
		}
	}

}
static void stage_save_report(HIBPReportView* report, const char* filename)
{
	char certify[128]={0};
	FILE* fp = fopen(filename, "w");
	if(!fp)
	{
		fprintf(stderr, "report file[%s] open failed!", filename);
		return;
	}

	char buf[1024];
	for(int i=0; i<report->nitems; i++){
		HIBPRiderInfo* r= report->items[i].rider;
		HIBPReportItem* ritem = report->items+i;
		char rank[4]="-";
		if(report->items[i].score > 0 )
			sprintf(rank,"%d", ritem->rank); 

		sprintf(buf, "%s,%s,%03d,%s,%s", r->group_name, rank, r->number, r->name, r->team);
		int nstages = ritem->result->row->ncols;
		for(int k=0; k<nstages; k++){
			HIBPStageResult* sr = (HIBPStageResult*)ritem->result->row->cols[k];
			sprintf(buf,"%s,%s,%s,%s,%s,%s,%s,%d", buf,
				to_timestr(sr->transfer_result.start_time),
				to_timestr(sr->transfer_result.end_time),
				sr->qualify==0?"DNQ":to_timestr(sr->transfer_result.result_time),
				to_timestr(sr->stage_result.start_time),
				to_timestr(sr->stage_result.end_time),
				to_timestr(sr->stage_result.result_time),
				sr->score);
				
		}

		//cut from fisrt space
		char* idx = strstr(r->name, " ");
		if(idx)
			*idx='\0';

		sprintf(certify, "%d-%s.png", i, r->name);	
		sprintf(buf,"%s,%s,%d\n", buf, certify, ritem->score);
		fputs(buf, fp);
	}

	fclose(fp);
}


/*
static void stage_read_report(HIBPStageResult* result, const char* fname) 
{
	char buf[1024], tmp[64];
	int i=0;
	int gid_tmp=-1;
	if( !file_open(fname, "r"))
		return;

	file_gets(buf, 1024);//skip head line
	while( file_gets(buf, 1024) != NULL)
	{
		int gid = get_column_i(buf, 0);
		if(gid != gid_tmp){
			if(gid_tmp != -1)
				groups[gid_tmp].nriders = i;
			i=0;
			gid_tmp = gid;
		}
		groups[gid].group=gid;
		groups[gid].riders[i].number 				= get_column_i  (buf, 3);
		strcpy(groups[gid].riders[i].name   			, get_column_str(buf, 4, tmp));
		strcpy(groups[gid].riders[i].team   			, get_column_str(buf, 5, tmp));
		strcpy(groups[gid].riders[i].start_time[0] 	        , get_column_str(buf, 6, tmp));
		strcpy(groups[gid].riders[i].end_time[0] 	        , get_column_str(buf, 7, tmp));
		strcpy(groups[gid].riders[i].result_time[0] 	        , get_column_str(buf, 8, tmp));
		groups[gid].riders[i].results[0].speed			= get_column_f  (buf, 10);
		groups[gid].riders[i].results[0].points			= get_column_i  (buf, 11);
		
		i++;
	}

	groups[gid_tmp].nriders = i;
	file_close();
}
*/

/*
static char* get_headline(char head[])
{
	sprintf(head, "Group,GroupName,Rank,No,Name,Team,SartTime,EndTime,ResultTime,GapTime,AvgSpeed,Points\n");
	return head;
}

void save_report(HIBPGroupRider* groups, int groups_count, const char* filename)
{
	char head[1024]; 
	int i,j;

	if(!file_open(filename, "w") )
	{
		fprintf(stderr, "report file[%s] open failed!", filename);
		return;
	}

	//Group,Rank,No.,Name,Team, StartTime,EndTime,PureTime,GapTime,Points
	file_puts( get_headline(head) );
	char buf[256];
	for(i=0; i<groups_count; i++){
		for(j=0; j<groups[i].nriders; j++){
			HIBPRiderInfo* r= groups[i].riders+j;
			sprintf(buf, "%d,%s,%d,%03d,%s,%s", 
				groups[i].group, groupStr[groups[i].group].str, j+1, r->number, r->name, r->team);

			PINTERFACE p = r->results;
			if(p->sec == 0){
				sprintf(buf,"%s,DNS,DNS,DNS,DNS,0,0\n", buf);
			}
			else if(!p->end_filled){
				sprintf(buf,"%s,%02d:%02d:%02d.%03d,DNF,DNF,DNF,0,0\n", buf, 
					(p->sec/60/60+8)%24, (p->sec/60)%60, (p->sec%60), p->msec
				);
			}
			else{ 

				sprintf(buf,"%s,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%.3f,%d\n",
					buf,
					(p->sec/60/60+8)%24, (p->sec/60)%60, (p->sec%60), p->msec,
					(p->end_sec/60/60+8)%24, (p->end_sec/60)%60, (p->end_sec%60), p->end_msec,
					(p->pure_sec/60/60)%24, (p->pure_sec/60)%60, (p->pure_sec%60), p->pure_msec,
					(p->gap_sec/60/60)%24, (p->gap_sec/60)%60, (p->gap_sec%60), p->gap_msec,
					p->speed, p->points);
			}

			file_puts(buf);
		}
	}

	file_close();
}

*/
