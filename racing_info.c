///racing_info.c
//
//

#include <string.h>

#define MAX_STAGES 10

typedef struct
{
	char mode[8];
	union{
		struct {
			int total_stages; //max 10 stages
			int need_transfer[MAX_STAGES];
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
	info.stage.total_stages = 3;
	info.stage.need_transfer[0] = 1;
	info.stage.need_transfer[1] = 0;
	info.stage.need_transfer[2] = 0;
}
