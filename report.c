
#include "global.h"
#include "points_rule.h"
#include "racing_info.h"
#include "riders.h"
#include "results.h"
#include "utils.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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

void read_report(HIBPGroupRider* groups, const char* fname) 
{
	char buf[256], tmp[64];
	int i=0;
	if( !file_open(fname, "r"))
		return;

	file_gets(buf, 256);//skip head line
	while( file_gets(buf, 256) != NULL)
	{
		int number = get_column_i  (buf, 3);
		HIBPRiderInfo* rider = get_rider_info(number);
		if(rider == NULL){
            continue;
        }

		strcpy(rider->start_time[0] 	    , get_column_str(buf, 6, tmp));
		strcpy(rider->end_time[0] 	        , get_column_str(buf, 7, tmp));
		strcpy(rider->result_time[0] 	    , get_column_str(buf, 8, tmp));
		rider->results[0].speed			    = get_column_f  (buf, 10);
		rider->results[0].points			= get_column_i  (buf, 11);
		if(strcmp(rider->result_time[0], "DNS")==0||
		    strcmp(rider->result_time[0], "DNF")==0||
		    strcmp(rider->result_time[0], "DNQ")==0
        ){
		    rider->results[0].pure_sec = INVALID_TIME;
            continue;
        }

		int sec, msec;
		to_time_sec(get_column_str(buf, 8, tmp), &sec, &msec);
		rider->results[0].pure_sec = sec;
		rider->results[0].pure_msec= msec;
        rider->results[0].end_filled = 1;
	}

	file_close();

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
			if(p->pure_sec ==INVALID_TIME ){
				sprintf(buf,"%s,-,-,DNS,DNS,0,0\n", buf);
			}
			else if(!p->end_filled){
				sprintf(buf,"%s,-,-,DNF,DNF,0,0\n", buf);
			}
			else{ 

				sprintf(buf,"%s,-,-,%02d:%02d:%02d.%03d,%02d:%02d:%02d.%03d,%.3f,%d\n",
					buf,
					//(p->sec/60/60+8)%24, (p->sec/60)%60, (p->sec%60), p->msec,
					//(p->end_sec/60/60+8)%24, (p->end_sec/60)%60, (p->end_sec%60), p->end_msec,
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
	HIBPGroupRider* groups = get_groups(); 
	int i=0;
	char fname[64];

    //生成本次stage 报表
	//1.计算积分
	for(i=0; i<MAX_GROUPS; i++){
		int no=0;
		for(int j=0; j<groups[i].nriders; j++){
			no++;
			groups[i].riders[j].results[0].points = get_points(no, groups[i].group);
		}
	}

	//保存报表
	sprintf(fname, "result.csv");
	sort_by_points(groups, MAX_GROUPS);
	save_report(groups, MAX_GROUPS, fname);
}


