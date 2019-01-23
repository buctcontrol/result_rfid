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
#define _PATH_START		"/home/pi/autoresult_zero_w_002.txt"
#define _PATH_END		"/home/pi/end_result.txt"
enum
{
    CLEANER     = 0,
    NEWBIE      = 1,
    HARDTAIL    = 2,
    WOMAN       = 3,
    OPEN        = 4,
    ELITE       = 5,
    MASTER      = 6,
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
    {"吕阳    ", "HIBP                    ",    MASTER}, 
    {"杨立忠  ", "HIBP                    ",    MASTER}, 
    {"詹森    ", "鬼魅仔车队              ",    MASTER}, 
    {"张亮    ", "中国闪电杭州中老年扛车队",    MASTER},   
    {"黄家琦  ", "阿里天驱                ",    MASTER},   
    {"陆成涛  ", "杭州捷奥山地车          ",    MASTER},   
    {"吴斌    ", "杭州捷奥山地车          ",    MASTER},   
    {"宗朝贤  ", "杭州捷奥山地车          ",    MASTER},   
    {"王力    ", "杭州捷奥山地车          ",    MASTER},   
    {"施昊凡  ", "杭州捷奥山地车          ",    MASTER},   
    {"戴一唯  ", "杭州捷奥山地车          ",    MASTER},   
    {"吴圣城  ", "HIBP                    ",    MASTER},   
    {"刘涵    ", "杭州捷奥山地车          ",    MASTER},   
    {"张剑飞  ", "HIBP                    ",    MASTER},   
    {"卓宁    ", "GDR Racing Team         ",    MASTER},   
    {"黄立观  ", "Banshee Rock Team       ",    MASTER},    
    {"雷星    ", "HangZhou Giant Racing   ",    MASTER},    
};
