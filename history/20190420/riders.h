/*
 * =====================================================================================
 *
 *       Filename:  riders.h
 *
 *    Description:  用户名单预置表
 *
 *        Version:  1.0
 *        Created:  2018年12月17日 12时40分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#define _PATH_START		"./autoresult.txt"
#define _PATH_END		"./end_result.txt"
enum
{
    CLEANER     = 0,
    NEWBIE      = 1,
    HARDTAIL    = 2,
    WOMAN       = 3,
    MAN         = 4,
    OPEN        = 5,
    ELITE       = 6,
    MASTER      = 7,
    EBIKE       = 8,
};

typedef struct
{
    char    str[32];
}HIBPGroup;

typedef struct
{
    char    str[32];
}HIBPTitle;

HIBPGroup groupStr[] = {
    {"清道夫"},
    {"新人组"},
    {"硬尾组"},
    {"女子组"},
    {"男子组"},
    {"大众组"},
    {"精英组"},
    {"大师组"},
    {"EBike"}
};

HIBPTitle titleStr[] = {
    {"冠军"},
    {"亚军"},
    {"季军"}
};

typedef struct
{
    char            name[32];
    char            team[128];
    unsigned int    group;
}HIBPRiderInfo;

HIBPRiderInfo riders[] = {
    {"楼文钧         ", "假日单车                ",    EBIKE  },
    {"章子俊         ", "石舌章队                ",    EBIKE  },
    {"姜波           ", "摩嗨轻蜂                ",    EBIKE  },
    {"雷星           ", "HangZhou Giant Racing   ",    MAN    },
    {"周小焜         ", "长沙CYCGO速行俱乐部     ",    MAN    },
    {"周吉强         ", "杭州假日山地车队        ",    MAN    },
    {"梅雨龙         ", "假日单车山地车队        ",    MAN    },
    {"马琰           ", "假日单车山地车队        ",    MAN    },
    {"俞斌           ", "鬼魅仔车队              ",    MAN    },
    {"马力           ", "漫奇车队                ",    MAN    },
    {"Anton Chalov   ", "Team Fuzzy Balls        ",    MAN    },
    {"Erik           ", "Team Fuzzy Balls        ",    MAN    },
    {"喻杰           ", "HangZhou Giant          ",    MAN    },
    {"黄俊熙         ", "长沙半小时车队          ",    MAN    },
    {"谭钊           ", "长沙半小时车队          ",    MAN    },
    {"洪辉熊         ", "长沙半小时车队          ",    MAN    },
    {"周王忍         ", "长沙半小时车队          ",    MAN    },
    {"徐鑫           ", "长沙半小时车队          ",    MAN    },
    {"欧阳一茗       ", "长沙半小时车队          ",    MAN    },
    {"黄浩           ", "天空穿越车队            ",    MAN    },
    {"王宇           ", "个人                    ",    MAN    },
    {"王国栋         ", "Byron                   ",    MAN    },
    {"应明浩         ", "HIBP                    ",    MAN    },
    {"常容涛         ", "mcc club                ",    MAN    },
    {"叶万达         ", "鬼魅仔车队              ",    MAN    },
    {"王杜           ", "天空穿越车队            ",    MASTER },
    {"陈海川         ", "山里人                  ",    MASTER },
    {"吴双           ", "假日单车山地车队        ",    MASTER },
    {"Mathieu        ", "Team Fuzzy Balls        ",    MASTER },
    {"ian legend     ", "Team Fuzzy Balls        ",    MASTER },
    {"Johannes       ", "Team Fuzzy Balls        ",    MASTER },
    {"Andreas        ", "Team Fuzzy Balls        ",    MASTER },
    {"Woon Hon Siong ", "鬼魅仔车队              ",    MASTER },
    {"Peter Grogan   ", "Independent             ",    MASTER },
    {"孙卫红         ", "个人                    ",    MASTER },
    {"夏永照         ", "飞客                    ",    MASTER },
    {"林正峯         ", "飞客                    ",    MASTER },
    {"陈黎升         ", "鬼魅仔车队              ",    MASTER },
    {"ASH/阿什       ", "HIBP                    ",    MASTER },
};
