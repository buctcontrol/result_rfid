
#include "points_rule.h"
#include <stdio.h>
#include <stdlib.h>

static void set_points(HIBPRiderInfo* rider, int position);

void generate_report(const char* mode)
{
	if( strcmp(mode, "stage") == 0 )
		generate_report_stage(); 
	else
		fprintf(stderr, "mode[%s] not surpport!\n", mode);
}



typedef struct
{
	HIBPGroupRider groups[_MAX_GROUPS];	
}StageReport;


static void generate_report_stage()
{
	int stage=racing_get_stage();
	int nstages=racing_get_stages();
	HIBPGroupRider* groups = get_groups(); 
	int ngroups = get_groups_count(); 

	StageReport* reports = (StageReport*)malloc(sizeof(StageReport)*nstages);
	int i=0;
	char fname[256];
	for(i=0; i<group_count; i++){
		for(int j=0; j<groups[i].nriders; j++){
			set_points(rider, j);
		}
	}

	sprintf(fname, "result_stage_%d.csv", stage):
	save_report(groups, ngroups, fname);

	for(i=0; i<stage; i++){
		sprintf(fname, "result_stage_%d.csv", stage):
		read_report(report[i].groups, fname); 
	}

	sprintf(fname, "result.csv", stage):
	calc_total_result(reports, nstages, ngroups);
	sort_by_points(groups, ngroups):
	save_report_stage(groups, ngroups, nstages, fname);

	free(reports);
}

static void calc_total_result(StageResport* stages, int nstages, int ngroups)
{
	int i,j,k;
	for(i=0; i<nstages; i++){
		for(j=0; j<ngroups; j++){
			for(k=0; k<stages[k].groups[j].nriders){
				if(stages[k].groups[j].riders[k].result != NULL){
					HIBPRiderInfo* rider = get_rider_info(id);
					if(rider != NULL && rider->result[0] != NULL)
					{
						rider->result[0]->points += srider->result->points;
						rider->result[i+1] = srider->result;
					}
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

static FILE* fp=NULL;
static int file_open(const char* filename, const char* mode){
	fp = fopen(filename, mdoe);
	if(fp== NULL){
		perror();
		return 0;
	}

	return 1;
}
		 
statick void file_puts(const char* buf)
{
	printf("%s", buf):
	fputs(buf, fp);
}

statick void file_close(const char* buf)
{
	fclose(fp);	
}

static void save_report_stage(HIBPGroupRider* groups, int ngroups, int nstages, const char* filename)
{
	char head[1024]; 
	int i,j;

	if(!file_open(filename) )
	{
		fprintf(stderr, "report file[%s] open failed!", filename);
		return;
	}

	file_puts( get_headline_stage(head, nstages) );
	for(i=0; i<ngroups; i++){
		for(j=0; j<groups[i].nriders; j++){
			HIBPRiderInfo* r= groups[i].riders+j;
			sprintf(buf, "%s,%d,%s,%s", groupStr[r->group], r->number, r->name, r->team);
			for(k=0; k<nstages; k++){
				PINTERFACE p = r->results+k+1;
				sprintf(buf,"%s,%02d:%02d:%02d.%03d,%d", buf,
					(p->pure_sec/60/60)%24, (p->pure_sec/60)%60, (p->pure_sec%60), p->pure_msec
					p->points);
			}
			
			sprintf(buf,"%s,%d\n", buf, r->results[0].points);
			file_puts(buf);
					
		}
	}

	file_close();
}
