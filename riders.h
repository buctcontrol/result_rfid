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
    ELETE       = 6,
    MASTER      = 7,
    MAX         = 8
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
    {"荣誉领骑"},
    {"新人组"},
    {"硬尾组"},
    {"女子组"},
    {"男子组"},
    {"大众组"},
    {"精英组"},
    {"大师组"}
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
    {"夜雪  ",  "杭州捷奥山地车   ",    CLEANER},
    {"鬼魅仔",  "鬼魅仔车队       ",    WOMAN},
    {"文潇  ",  "无               ",    OPEN},
    {"朱雁青",  "九骑户外         ",    OPEN},
    {"吴圣城",  "HIBP             ",    OPEN},
    {"孔令帅",  "九骑户外         ",    OPEN},
    {"马琰  ",  "假日单车山地队   ",    OPEN},
    {"雷星  ",  "中国全圣德车队   ",    OPEN},
    {"黄立观",  "Banshee Rock Team",    OPEN},
    {"梅雨龙",  "假日单车山地队   ",    OPEN},
    {"周吉强",  "假日单车山地队   ",    OPEN},
    {"连侃  ",  "虬龙             ",    OPEN},
    {"董凌  ",  "假日单车山地队   ",    OPEN},
    {"陈儒斌",  "KonaChina        ",    OPEN},
    {"高涛  ",  "速降老男人       ",    OPEN},
    {"田帅  ",  "酷乐骑行特训营   ",    OPEN},
    {"陈敏坤",  "HIBP             ",    OPEN},
    {"蒋思源",  "假日单车山地队   ",    OPEN},
    {"骆沙舟",  "假日单车山地队   ",    OPEN}
};
