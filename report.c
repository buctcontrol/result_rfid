
#include "global.h"
#include "points_rule.h"
#include "racing_info.h"
#include "riders.h"
#include "utils.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void generate_report_stage();

void generate_report()
{
	const char* mode = racing_get_mode();
	if( strcmp(mode, "stage") == 0 )
		generate_report_stage(); 
	else
		fprintf(stderr, "mode[%s] not surpport!\n", mode);
}



typedef struct
{
	HIBPGroupRider groups[_MAX_GROUPS];	
}StageReport;


static int compare_rider_points(const HIBPRiderInfo* src, const HIBPRiderInfo* dst)
{
	if(dst->results[0].points < src->results[0].points) 
	 	return 1;	

	return 0;
}


static void sort_by_points(HIBPGroupRider* groups, int groups_count)
{
	sort_riders(groups, groups_count, compare_rider_points);
}

static void read_report(HIBPGroupRider* groups, const char* fname) 
{
}

static void calc_total_result(StageReport* stages, int nstages, int groups_count)
{
	int i,j,k;
	for(i=0; i<nstages; i++){
		for(j=0; j<groups_count; j++){
			for(k=0; k<stages[k].groups[j].nriders; k++){
				HIBPRiderInfo* srider= stages[i].groups[j].riders+k;
				HIBPRiderInfo* rider = get_rider_info(srider->number);
				if(rider != NULL) 
				{
					rider->results[0].points += srider->results[0].points;
					rider->results[i+1] = srider->results[0];
				}
			}
		}
	}


		
}

static char* get_headline_stage(char head[], int nstages)
{
	int i;
	sprintf(head, "Group,No,Name,Team");
	for(i=0; i<nstages; i++);
		sprintf(head, "%s,Stage%d,Stage%d Points", head, i+1, i+1);

	sprintf(head, "%s,Total Points\n", head);
	return head;
}

static void save_report_stage(HIBPGroupRider* groups, int groups_count, int nstages, const char* filename)
{
	char head[1024]; 
	int i,j,k;

	if(!file_open(filename, "w") )
	{
		fprintf(stderr, "report file[%s] open failed!", filename);
		return;
	}

	file_puts( get_headline_stage(head, nstages) );
	char buf[256];
	for(i=0; i<groups_count; i++){
		for(j=0; j<groups[i].nriders; j++){
			HIBPRiderInfo* r= groups[i].riders+j;
			sprintf(buf, "%s,%d,%s,%s", groupStr[r->group].str, r->number, r->name, r->team);
			for(k=0; k<nstages; k++){
				PINTERFACE p = r->results+k+1;
				sprintf(buf,"%s,%02d:%02d:%02d.%03d,%d", buf,
					(p->pure_sec/60/60)%24, (p->pure_sec/60)%60, (p->pure_sec%60), p->pure_msec,
					p->points);
			}
			
			sprintf(buf,"%s,%d\n", buf, r->results[0].points);
			file_puts(buf);
		}
	}

	file_close();
}

static char* get_headline(char head[])
{
	sprintf(head, "Group,Rank,No,Name,Team,SartTime,EndTime,ResultTime,GapTime");
	return head;
}

static void save_report(HIBPGroupRider* groups, int groups_count, const char* filename)
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
			sprintf(buf, "%s,%d,%03d,%s,%s", groupStr[r->group].str, j+1, r->number, r->name, r->team);
				PINTERFACE p = r->results;
				sprintf(buf,"%s,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%d", buf,
					(p->sec/60/60)%24, (p->sec/60)%60, (p->sec%60), p->msec,
					(p->pure_sec/60/60)%24, (p->pure_sec/60)%60, (p->pure_sec%60), p->pure_msec,
					(p->end_sec/60/60)%24, (p->end_sec/60)%60, (p->end_sec%60), p->end_msec,
					(p->gap_sec/60/60)%24, (p->gap_sec/60)%60, (p->gap_sec%60), p->gap_msec,
					p->points);

			file_puts(buf);
			}
	}

	file_close();
}

static void generate_report_stage()
{
	int stage=racing_get_curstage();
	int nstages=racing_get_stages();
	HIBPGroupRider* groups = get_groups(); 
	int groups_count = get_groups_count(); 

	StageReport* reports = (StageReport*)malloc(sizeof(StageReport)*nstages);
	int i=0;
	char fname[256];
	for(i=0; i<groups_count; i++){
		for(int j=0; j<groups[i].nriders; j++){
			groups[i].riders[j].results[0].points = get_points(groups[i].group, j);
		}
	}

	sprintf(fname, "result_stage_%d.csv", stage);
	save_report(groups, groups_count, fname);

	for(i=0; i<stage; i++){
		sprintf(fname, "result_stage_%d.csv", stage);
		read_report(reports[i].groups, fname); 
	}

	sprintf(fname, "result.csv");
	calc_total_result(reports, nstages, groups_count);
	sort_by_points(groups, groups_count);
	save_report_stage(groups, groups_count, nstages, fname);

	free(reports);
}


#include <stdio.h>
struct interface g_ife;

int main()
{
	memset(&g_ife, 0, sizeof(g_ife));
	INIT_LIST_HEAD(&g_ife.list);
	//read_start();
	//read_finish();
	//calc_result();
	save_report(get_groups(), get_groups_count(), "results.csv" );
	
	return 0;
}

