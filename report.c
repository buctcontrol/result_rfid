
#include "global.h"
#include "points_rule.h"
#include "racing_info.h"
#include "riders.h"
#include "utils.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
	HIBPGroupRider groups[_MAX_GROUPS];	
}StageReport;

static int compare_rider_points(const HIBPRiderInfo* src, const HIBPRiderInfo* dst)
{
	if(dst->results[0].points > src->results[0].points) 
	 	return 1;	

	if(dst->results[0].points == src->results[0].points){
		if( strcmp(racing_get_mode(), "stage") == 0 ){  
			int nstages = racing_get_stages();	
			if(dst->results[nstages].points > src->results[nstages].points){
				return 1;
			}
		}
	}

	return 0;
}


static void sort_by_points(HIBPGroupRider* groups, int groups_count)
{
	sort_riders(groups, groups_count, compare_rider_points);
}

static void read_report(HIBPGroupRider* groups, const char* fname) 
{
	char buf[256], tmp[64];
	int i=0;
	int gid_tmp=-1;
	if( !file_open(fname, "r"))
		return;

	file_gets(buf, 256);//skip head line
	while( file_gets(buf, 256) != NULL)
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

static void calc_total_result(StageReport* stages, int nstages, int groups_count)
{
	int i,j,k;
	for(i=0; i<nstages; i++){
		for(j=0; j<_MAX_GROUPS; j++){
			for(k=0; k<stages[i].groups[j].nriders; k++){
				HIBPRiderInfo* srider= stages[i].groups[j].riders+k;
				HIBPRiderInfo* rider = get_rider_info(srider->number);
				if(rider != NULL) {
					rider->results[0].points += srider->results[0].points;
					rider->results[i+1] = srider->results[0];
					strcpy(rider->start_time[i+1] , srider->start_time[0]);
					strcpy(rider->end_time[i+1] , srider->end_time[0]);
					strcpy(rider->result_time[i+1] , srider->result_time[0]);
				}
			}
		}
	}
}

static char* get_headline_stage(char* head, int nstages)
{
	sprintf(head, "Group,Rank,No,Name,Team");
	for(int i=0; i<nstages; i++){
		if(is_has_transfer(i+1) )
			sprintf(head, "%s,Transfer%d Start,Transfer%d End,Transfer%d Result", head, i+1, i+1, i+1);
		
		sprintf(head, "%s,Stage%d Start,Stage%d End,Stage%d Result,Stage%d Points", head, i+1, i+1, i+1, i+1);
	}

	sprintf(head, "%s,Points\n", head);
	return head;
}

static void read_transfer_report(HIBPGroupRider* groups, int stage, int is_copy) 
{
	char fname[16];
	sprintf(fname, "result_transfer_%d.csv", stage);
	HIBPGroupRider groups_t[_MAX_GROUPS];
	memset(groups_t, 0, sizeof(HIBPGroupRider)*_MAX_GROUPS);

	read_report(groups_t, fname);
	if(is_copy)
		memcpy(groups, groups_t, sizeof(HIBPGroupRider)*_MAX_GROUPS);

	for(int i=0; i<_MAX_GROUPS; i++){
		for(int j=0; j<groups_t[i].nriders; j++){
			HIBPRiderInfo* r= groups_t[i].riders+j;
			HIBPRiderInfo* rr = get_rider_info_g(groups, r->number);
			if( strcmp(r->result_time[stage-1], "DNS") == 0 
			   ||strcmp(r->result_time[stage-1], "NDF") == 0
			   ||strcmp(r->result_time[stage-1], get_transer_shut_time(stage)) > 0
			){
				rr->qualify_r = 0;
			}
			else
				rr->qualify_r = 1;

		}
	}
}

static void save_report_stage(HIBPGroupRider* groups, int groups_count, int nstages, const char* filename)
{
	char head[1024]; 
	FILE* fp = fopen(filename, "w");
	if(!fp)
	{
		fprintf(stderr, "report file[%s] open failed!", filename);
		return;
	}

	fputs(get_headline_stage(head, nstages), fp);
	char buf[256];
	for(int i=0; i<_MAX_GROUPS; i++){
		for(int j=0; j<groups[i].nriders; j++){
			HIBPRiderInfo* r= groups[i].riders+j;
			sprintf(buf, "%s,%d,%03d,%s,%s", groupStr[groups[i].group].str, j+1, r->number, r->name, r->team);
			for(int k=0; k<nstages; k++){
				PINTERFACE p = r->results+k+1;
				if(is_has_transfer(k+1)){
					
					HIBPGroupRider *groups_t = (HIBPGroupRider*)malloc(sizeof(HIBPGroupRider)*_MAX_GROUPS);
					read_transfer_report(groups_t, k+1, 1);
					HIBPRiderInfo* tr = get_rider_info_g(groups_t, r->number);
					if(tr == NULL){
						fprintf(stderr, "transfer rider not found");
						exit(1);
					}

					sprintf(buf,"%s,%s,%s,%s,%s,%s,%s,%d", buf,
						tr->start_time[0],
						tr->end_time[0],
						tr->qualify_r==1?tr->result_time[0]:"DNQ",
						r->start_time[k+1],
						r->end_time[k+1],
						tr->qualify_r==1?r->result_time[k+1]:"DNQ",
						p->points);
				}
				else{
					sprintf(buf,"%s,%s,%s,%s,%d", buf,
						r->start_time[k+1],
						r->end_time[k+1],
						r->result_time[k+1],
						p->points);
				}
			}
			
			sprintf(buf,"%s,%d\n", buf, r->results[0].points);
			fputs(buf, fp);
		}
	}

	fclose(fp);
}

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
				sprintf(buf,"%s,DNF,DNF,DNF,DNF,0,0\n", buf);
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

void generate_report_stage(int stage)
{
	int nstages=racing_get_stages();
	HIBPGroupRider* groups = get_groups(); 
	int groups_count = get_groups_count(); 

	StageReport* reports = (StageReport*)malloc(sizeof(StageReport)*nstages);
	int i=0;
	char fname[64];
	if(is_has_transfer(stage))
		read_transfer_report(groups, stage, 0); 

	for(i=0; i<groups_count; i++){
		for(int j=0; j<groups[i].nriders; j++){
			if(!is_has_transfer(stage))
				groups[i].riders[j].qualify_r = 1;

			if(groups[i].riders[j].results[0].end_filled
			  &&groups[i].riders[j].qualify_r
			){
				groups[i].riders[j].results[0].points = get_points(j+1, groups[i].group);
			}
		}
	}

	sprintf(fname, "result_stage_%d.csv", stage);
	save_report(groups, groups_count, fname);

	for(i=0; i<groups_count; i++){
		for(int j=0; j<groups[i].nriders; j++){
			groups[i].riders[j].results[0].points = 0;
		}
	}

	for(i=0; i<stage; i++){
		sprintf(fname, "result_stage_%d.csv", i+1);
		read_report(reports[i].groups, fname); 
	}

	sprintf(fname, "result.csv");
	calc_total_result(reports, nstages, groups_count);
	sort_by_points(groups, groups_count);
	save_report_stage(groups, groups_count, nstages, fname);

	free(reports);
}


/*
#include <stdio.h>
struct interface g_ife;

#include "results.h"

int main()
{
	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);
	read_start();
	read_finish();
	calc_result();
	save_report(get_groups(), get_groups_count(), "result_stage_1.csv" );

	HIBPGroupRider groups[_MAX_GROUPS];
	read_report(groups, "result_stage_1.csv");

	return 0;
}
*/
