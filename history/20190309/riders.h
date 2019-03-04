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
#include "global.h"
#define _PATH_START		"/home/pi/autoresult_nespi_001.txt"
#define _PATH_END		"/home/pi/end_result_superpi_002.txt"

HIBPRiderInfo riders[] = {
    {1,     "张佳莉        ", "鬼魅仔车队              ",    WOMAN}, 
    {2,     "杨婵琳        ", "鬼魅仔车队              ",    WOMAN}, 
    {3,     "浦慧菁        ", "西虹试飞客队            ",    WOMAN}, 
    {101,   "赵仁仁        ", "个人                    ",    HARDTAIL}, 
    {102,   "郭金畅        ", "个人                    ",    HARDTAIL}, 
    {103,   "钱俊          ", "鬼魅仔车队              ",    HARDTAIL}, 
    {104,   "姜浩          ", "美好生活                ",    HARDTAIL}, 
    {105,   "郁志程        ", "苏州天平山              ",    HARDTAIL},  
    {106,   "祝宇升        ", "鬼魅仔车队              ",    HARDTAIL}, 
    {107,   "林雨寒        ", "West coast x Gravity lab",    HARDTAIL}, 
    {201,   "陈子炜        ", "个人                    ",    NEWBIE},   
    {202,   "陈子祺        ", "个人                    ",    NEWBIE},   
    {203,   "李怿满        ", "暂无                    ",    NEWBIE},     
    {204,   "周炜恒        ", "西虹试飞客队            ",    NEWBIE},   
    {205,   "吕阳          ", "HIBP                    ",    NEWBIE},   
    {206,   "吕昊翔        ", "个人                    ",    NEWBIE},    
    {207,   "王顺晨        ", "个人                    ",    NEWBIE},    
    {208,   "苏来曼·达古提 ", "个人                    ",    NEWBIE},    
    {209,   "常容涛        ", "MCC club                ",    NEWBIE},    
    {210,   "黄嘉朋        ", "dirt kids               ",    NEWBIE},    
    {211,   "周屹天        ", "苏州风行单车            ",    NEWBIE},   
    {212,   "江子越        ", "顽啤车队                ",    NEWBIE},   
    {214,   "沈一凡        ", "顽啤车队                ",    NEWBIE},   
    {215,   "郑轶辉        ", "HangZhou Giant          ",    NEWBIE},
    {216,   "喻杰          ", "HangZhou Giant          ",    NEWBIE},   
    {217,   "桑悟超        ", "西虹试飞客队            ",    NEWBIE},   
    {218,   "丁凯          ", "西虹试飞客队            ",    NEWBIE},   
    {219,   "蒋永斌        ", "西虹试飞客队            ",    NEWBIE},   
    {220,   "陈黎升        ", "鬼魅仔车队              ",    NEWBIE},
    {221,   "叶万达        ", "鬼魅仔车队              ",    NEWBIE},
    {222,   "周郑          ", "TREK杭州轮与路车队      ",    NEWBIE},   
    {223,   "应明浩        ", "HIBP                    ",    NEWBIE},   
    {224,   "王国栋        ", "个人                    ",    NEWBIE},   
    {225,   "詹森          ", "鬼魅仔车队              ",    NEWBIE},   
    {226,   "汪国瑞        ", "正儿八紧                ",    NEWBIE},
    {227,   "尹璐鹏        ", "鬼魅仔车队              ",    NEWBIE},   
    {228,   "顾超炬        ", "鬼魅仔车队              ",    NEWBIE},   
    {229,   "程钢          ", "鬼魅仔车队              ",    NEWBIE},   
    {230,   "吴志华        ", "鬼魅仔车队              ",    NEWBIE},   
    {231,   "金也          ", "杭州捷奥山地车          ",    NEWBIE},   
    {232,   "陆成涛        ", "杭州捷奥山地车          ",    NEWBIE},   
    {233,   "沈陆晓冬      ", "合肥重车群              ",    NEWBIE},   
    {234,   "任凯          ", "西虹试飞客队            ",    NEWBIE},   
    {235,   "Ash           ", "HIBP                    ",    NEWBIE},   
    {236,   "郑杨          ", "小麒麟                  ",    NEWBIE},   
    {237,   "高逍遥        ", "West coast x Gravity lab",    NEWBIE},
    {238,   "毕笑闻        ", "West coast x Gravity lab",    NEWBIE},
    {239,   "王敏昂        ", "West coast x Gravity lab",    NEWBIE},
    {240,   "梅子晗        ", "West coast x Gravity lab",    NEWBIE},
    {241,   "许懿凡        ", "West coast x Gravity lab",    NEWBIE},   
    {242,   "胡子杨        ", "West coast x Gravity lab",    NEWBIE},   
    {243,   "胡清顺        ", "West coast x Gravity lab",    NEWBIE},   
    {244,   "陈钰航        ", "West coast x Gravity lab",    NEWBIE},   
    {245,   "郭俊翊        ", "West coast x Gravity lab",    NEWBIE},   
    {246,   "宗朝贤        ", "杭州捷奥山地车          ",    NEWBIE},   
    {301,   "张贺          ", "中国北方联队            ",    OPEN},     
    {302,   "石鋆          ", "个人                    ",    OPEN},     
    {303,   "曾耿谆        ", "西虹试飞客队            ",    OPEN},     
    {304,   "窦安强        ", "上海魅力单车            ",    OPEN},     
    {305,   "张孙彦        ", "个人                    ",    OPEN},     
    {306,   "俞琛阳        ", "Intense China           ",    OPEN},     
    {307,   "朱雁青        ", "鬼魅仔车队              ",    OPEN},     
    {308,   "马文博        ", "West coast x Gravity lab",    OPEN},     
    {309,   "孙宇杰        ", "West coast x Gravity lab",    OPEN},     
    {310,   "杨涛          ", "West coast x Gravity lab",    OPEN},     
    {311,   "吴斌          ", "MUC-OFF杭州捷奥车队     ",    OPEN},     
    {312,   "王力          ", "MUC-OFF杭州捷奥山地车   ",    OPEN},     
    {313,   "陈曦          ", "阿里天驱                ",    OPEN},
    {314,   "黄家琦        ", "阿里天驱                ",    OPEN},
    {315,   "康宁          ", "河南窜山甲              ",    OPEN},
    {316,   "艾铅坤        ", "济南NoisyKids           ",    OPEN},
    {317,   "王逸豪        ", "顽啤车队                ",    OPEN},   
    {318,   "施昊凡        ", "杭州捷奥山地车          ",    OPEN},   
    {319,   "吴圣城        ", "HIBP                    ",    OPEN},
    {320,   "戴一唯        ", "MUC-OFF 杭州捷奥山地车  ",    OPEN}, 
    {321,   "吴双          ", "假日单车山地队          ",    OPEN},     
    {322,   "潘云峰        ", "TREK杭州轮与路车队      ",    OPEN},     
    {323,   "袁日境        ", "个人                    ",    OPEN},
    {324,   "王日晗        ", "鬼魅仔车队              ",    OPEN},
    {325,   "孔令帅        ", "九骑户外                ",    OPEN},     
    {326,   "刘飞          ", "嘉兴陨石                ",    OPEN},
    {327,   "曾杰          ", "西虹试飞客队            ",    OPEN},     
    {328,   "金玉青        ", "正儿八紧车队            ",    OPEN},
    {329,   "刘皇皇        ", "正儿八紧车队            ",    OPEN},
    {330,   "郎程威        ", "正儿八紧车队            ",    OPEN},     
    {331,   "马琰          ", "假日单车山地队          ",    OPEN},     
    {332,   "陈敏坤        ", "HIBP                    ",    OPEN},     
    {333,   "应礼筋        ", "小溪速降                ",    OPEN},     
    {334,   "俞斌          ", "鬼魅仔车队              ",    OPEN},
    {335,   "甄东旭        ", "West coast x Gravity lab",    OPEN},      
    {336,   "何鑫          ", "West coast x Gravity lab",    OPEN},
    {337,   "雷星          ", "HangZhou Giant Racing   ",    OPEN}, 
    {401,   "夏永照        ", "西虹试飞客队            ",    MASTER},   
    {402,   "林世忠        ", "西虹试飞客队            ",    MASTER},   
    {403,   "黃煥堂        ", "能量單車                ",    MASTER},   
    {404,   "周军          ", "西虹试飞客队            ",    MASTER},   
    {405,   "李清照        ", "暂无                    ",    MASTER},   
    {406,   "张亮          ", "闪电中国杭州中老年扛车队",    MASTER},   
    {407,   "楚雨润        ", "TREK杭州轮与路车队      ",    MASTER},     
    {408,   "陈海川        ", "西虹试飞客队            ",    MASTER},   
    {409,   "孟虎          ", "mtbmagasia              ",    MASTER},   
    {410,   "张秀标        ", "个人                    ",    MASTER},   
    {411,   "高涛          ", "速降老男人              ",    MASTER},   
    {501,   "刘涵          ", "杭州捷奥山地车          ",    ELITE},    
    {502,   "方子凡        ", "双轮汇 SLH Racing       ",    ELITE},    
    {503,   "赵南          ", "个人                    ",    ELITE},    
    {504,   "黄立观        ", "Banshee Rock Team       ",    ELITE},    
    {505,   "梅雨龙        ", "假日单车山地队          ",    ELITE},    
    {506,   "叶晨琦        ", "The King Of Fastest     ",    ELITE},    
    {507,   "张剑飞        ", "HIBP                    ",    ELITE},    
    {508,   "周晓龙        ", "双轮汇 SLH Racing       ",    ELITE},    
};
