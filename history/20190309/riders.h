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
#define _PATH_START		"/home/pi/autoresult.txt"
#define _PATH_END		"/home/pi/end_result.txt"
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
    {"张佳莉  ", "鬼魅仔车队              ",    WOMAN}, 
    {"郭金畅  ", "个人                    ",    HARDTAIL}, 
    {"钱俊    ", "鬼魅仔车队              ",    HARDTAIL}, 
    {"姜浩    ", "美好生活                ",    HARDTAIL}, 
    {"郁志程  ", "苏州天平山              ",    HARDTAIL},  
    {"祝宇升  ", "HIBP                    ",    HARDTAIL}, 
    {"林雨寒  ", "West coast x Gravity lab",    HARDTAIL}, 
    {"陈子炜  ", "个人                    ",    NEWBIE},   
    {"陈子祺  ", "个人                    ",    NEWBIE},   
    {"李怿满  ", "暂无                    ",    NEWBIE},     
    {"周炜恒  ", "西虹试飞客队            ",    NEWBIE},   
    {"吕阳    ", "HIBP                    ",    NEWBIE},   
    {"吕昊翔  ", "个人                    ",    NEWBIE},    
    {"周屹天  ", "苏州风行单车            ",    NEWBIE},   
    {"郑轶辉  ", "HangZhou Giant          ",    NEWBIE},
    {"喻杰    ", "HangZhou Giant          ",    NEWBIE},   
    {"郑杨    ", "小麒麟                  ",    NEWBIE},   
    {"桑悟超  ", "西虹试飞客队            ",    NEWBIE},   
    {"丁凯    ", "西虹试飞客队            ",    NEWBIE},   
    {"蒋永斌  ", "西虹试飞客队            ",    NEWBIE},   
    {"陈黎升  ", "鬼魅仔车队              ",    NEWBIE},
    {"叶万达  ", "鬼魅仔车队              ",    NEWBIE},
    {"周郑    ", "TREK杭州轮与路车队      ",    NEWBIE},   
    {"应明浩  ", "HIBP                    ",    NEWBIE},   
    {"王国栋  ", "个人                    ",    NEWBIE},   
    {"詹森    ", "鬼魅仔车队              ",    NEWBIE},   
    {"汪国瑞  ", "正儿八紧                ",    NEWBIE},
    {"尹璐鹏  ", "鬼魅仔车队              ",    NEWBIE},   
    {"顾超炬  ", "鬼魅仔车队              ",    NEWBIE},   
    {"程钢    ", "鬼魅仔车队              ",    NEWBIE},   
    {"吴志华  ", "鬼魅仔车队              ",    NEWBIE},   
    {"宗朝贤  ", "杭州捷奥山地车          ",    NEWBIE},   
    {"金也    ", "杭州捷奥山地车          ",    NEWBIE},   
    {"陆成涛  ", "杭州捷奥山地车          ",    NEWBIE},   
    {"沈陆晓冬", "合肥重车群              ",    NEWBIE},   
    {"任凯    ", "西虹试飞客队            ",    NEWBIE},   
    {"Ash     ", "HIBP                    ",    NEWBIE},   
    {"高逍遥  ", "West coast x Gravity lab",    NEWBIE},
    {"毕笑闻  ", "West coast x Gravity lab",    NEWBIE},
    {"王敏昂  ", "West coast x Gravity lab",    NEWBIE},
    {"梅子晗  ", "West coast x Gravity lab",    NEWBIE},
    {"许懿凡  ", "West coast x Gravity lab",    NEWBIE},   
    {"胡子杨  ", "West coast x Gravity lab",    NEWBIE},   
    {"胡清顺  ", "West coast x Gravity lab",    NEWBIE},   
    {"陈钰航  ", "West coast x Gravity lab",    NEWBIE},   
    {"郭俊翊  ", "West coast x Gravity lab",    NEWBIE},   
    {"雷周骏  ", "HIBP                    ",    OPEN},
    {"曾耿谆  ", "西虹试飞客队            ",    OPEN},     
    {"窦安强  ", "上海魅力单车            ",    OPEN},     
    {"张孙彦  ", "个人                    ",    OPEN},     
    {"俞琛阳  ", "Intense China           ",    OPEN},     
    {"朱雁青  ", "九骑户外                ",    OPEN},     
    {"马文博  ", "West coast x Gravity lab",    OPEN},     
    {"孙宇杰  ", "West coast x Gravity lab",    OPEN},     
    {"杨涛    ", "West coast x Gravity lab",    OPEN},     
    {"吴斌    ", "MUC-OFF杭州捷奥车队     ",    OPEN},     
    {"王力    ", "MUC-OFF杭州捷奥山地车   ",    OPEN},     
    {"陈曦    ", "阿里天驱                ",    OPEN},
    {"黄家琦  ", "阿里天驱                ",    OPEN},
    {"康宁    ", "河南窜山甲              ",    OPEN},
    {"施昊凡  ", "杭州捷奥山地车          ",    OPEN},   
    {"吴圣城  ", "HIBP                    ",    OPEN},
    {"戴一唯  ", "MUC-OFF 杭州捷奥山地车  ",    OPEN}, 
    {"吴双    ", "假日单车山地队          ",    OPEN},     
    {"潘云峰  ", "TREK杭州轮与路车队      ",    OPEN},     
    {"王日晗  ", "鬼魅仔车队              ",    OPEN},
    {"孔令帅  ", "九骑户外                ",    OPEN},     
    {"刘飞    ", "嘉兴陨石                ",    OPEN},
    {"曾杰    ", "西虹试飞客队            ",    OPEN},     
    {"刘皇皇  ", "正儿八紧车队            ",    OPEN},
    {"郎程威  ", "正儿八紧车队            ",    OPEN},     
    {"马琰    ", "假日单车山地队          ",    OPEN},     
    {"陈敏坤  ", "HIBP                    ",    OPEN},     
    {"俞斌    ", "追梦                    ",    OPEN},
    {"甄东旭  ", "West coast x Gravity lab",    OPEN},      
    {"何鑫    ", "West coast x Gravity lab",    OPEN},
    {"雷星    ", "HangZhou Giant Racing   ",    OPEN}, 
    {"夏永照  ", "西虹试飞客队            ",    MASTER},   
    {"林世忠  ", "27Bike                  ",    MASTER},   
    {"黃煥堂  ", "能量單車                ",    MASTER},   
    {"周军    ", "西虹试飞客队            ",    MASTER},   
    {"李清照  ", "暂无                    ",    MASTER},   
    {"楚雨润  ", "TREK杭州轮与路车队      ",    MASTER},     
    {"陈海川  ", "西虹试飞客队            ",    MASTER},   
    {"张秀标  ", "个人                    ",    MASTER},   
    {"高涛    ", "速降老男人              ",    MASTER},   
    {"刘涵    ", "杭州捷奥山地车          ",    ELITE},    
    {"梅雨龙  ", "假日单车山地队          ",    ELITE},    
    {"叶晨琦  ", "The King Of Fastest     ",    ELITE},    
    {"张剑飞  ", "HIBP                    ",    ELITE},    
    {"周晓龙  ", "双轮汇 SLH Racing       ",    ELITE},    
};
