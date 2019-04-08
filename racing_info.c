///racing_info.c
//
//

typedef struct
{
	char mode[8];
	int cur_stage;
	int total_stages;
	int cur_round;
}RacingInfo;

static RacingInfo info={
	{"stage"},
	1,
	3
};

char* racing_get_mode()
{
	return info.mode;
}

int racing_get_curstage()
{
	return info.cur_stage;
}

int racing_get_stages()
{
	return info.total_stages;
}

int racing_get_curround()
{
	return info.cur_round;
}

static void load_racing_info()
{
}
