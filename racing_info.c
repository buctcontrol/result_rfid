///racing_info.c
//
//

#include <string.h>
#include <stdio.h>
#include "global.h"
#include "riders.h"

#define MAX_STAGES 10

typedef struct
{
	char mode[8];
	union{
		struct {
			int total_stages; //max 10 stages
			char transfer_shut[MAX_GROUPS][MAX_STAGES][16];// group-stage transfer shut time
		}stage;

		struct {
			int cur_round;
		}round;
	};

}RacingInfo;

static RacingInfo info;


char* racing_get_mode()
{
	return info.mode;
}

int is_has_transfer_group(int group)
{
	if(group == EBIKE)
		return 0;

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

char* get_transer_shut_time(int group, int stage)
{
	if(group >= MAX_GROUPS){
		fprintf(stderr, "get_transfer_shut_time: group out idx");
		exit(1);
	}

	if(stage > MAX_STAGES){
		fprintf(stderr, "get_transfer_shut_time: stage out idx");
		exit(1);
	}

	return info.stage.transfer_shut[group][stage-1];
}

int racing_get_curstage()
{
	return 0;
}

int racing_get_stages()
{
	return info.stage.total_stages;
}

int racing_get_curround()
{
	return info.round.cur_round;
}

void load_racing_info()
{
	strcpy(info.mode, "stage");
	info.stage.total_stages = 2;
	strcpy(info.stage.transfer_shut[CAT][0], "01:00:00");
}
