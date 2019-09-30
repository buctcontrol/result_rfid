///racing_info.c
//
//

#include <string.h>
#include <stdio.h>

#define MAX_STAGES 10

typedef struct
{
	char mode[8];
	union{
		struct {
			int total_stages; //max 10 stages
			char transfer_shut[10][16];//transfer shut time
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

int is_has_transfer(int stage)
{
	char* mode = racing_get_mode();
	if( strcmp(mode, "round") == 0 )
		return 0;

	char fname[64];
	sprintf(fname, "t%ds.txt", stage);
	FILE* fp = fopen(fname, "r");
	if(fp)
		fclose(fp);

	return fp!=NULL?1:0;
}

char* get_transer_shut_time(int stage)
{
	return info.stage.transfer_shut[stage-1];
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
	strcpy(info.mode, "round");
	info.stage.total_stages = 2;
	strcpy(info.stage.transfer_shut[0], "00:02:00");
}

int isLastStage(int stage)
{
	return stage == racing_get_stages();
}

