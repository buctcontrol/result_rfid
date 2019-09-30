///global.c

#include "global.h"


HIBPGroup groupStr[] = {
    {"荣誉领骑"},
    {"新人组"},
    {"硬尾组"},
    {"女子组"},
    {"男子组"},
    {"大众组"},
    {"精英组"},
    {"大师组"},
    {"EBike"},
    {"体验组"},
    {"小野猫"},
    {"疯猫"}
};

HIBPTitle titleStr[] = {
    {"冠军"},
    {"亚军"},
    {"季军"}
};

char* GROUP_UNDEF="GROUP_UNDEF";

char* get_group_name(int group)
{
	if(group >= MAX)
		return GROUP_UNDEF;

	return groupStr[group].str;
}
