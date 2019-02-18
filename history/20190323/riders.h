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
#define _PATH_START		"./autoresult.txt"
#define _PATH_END		"./end_result.txt"

HIBPRiderInfo riders[] = {
    {1,     "陈敏坤  ", "HIBP                       ",    ELITE},
    {2,     "黄立观  ", "Banshee Rock Team          ",    ELITE},
    {3,     "肖聪    ", "GDR RACING TEAM            ",    ELITE},
    {4,     "唐梦麒  ", "GDR RACING TEAM            ",    ELITE},
    {5,     "吴超    ", "长沙顺时针车队             ",    ELITE},
    {6,     "叶晨琦  ", "bking                      ",    ELITE},
    {7,     "李果    ", "HIBP                       ",    ELITE},
    {8,     "张剑飞  ", "soco极限单车               ",    ELITE},
    {9,     "叶正午  ", "                           ",    ELITE},
    {10,    "刘楷杨  ", "双轮汇SLH Racing           ",    ELITE},
    {11,    "丁再刚  ", "勇峰自行车公园             ",    ELITE},
    {12,    "骆沙舟  ", "杭州假日单车山地车队       ",    ELITE},
    {13,    "周吉强  ", "杭州假日单车山地车队       ",    ELITE},
    {14,    "江思翰  ", "歐亞馬小熊自行車隊         ",    ELITE},
    {15,    "周晓龙  ", "双轮汇SLH Racing           ",    ELITE},
    {101,   "张佳莉  ", "鬼魅仔                     ",    WOMAN},
    {102,   "杨书娜  ", "前进俱乐部                 ",    WOMAN},
    {201,   "王利勇  ", "个人                       ",    OPEN},
    {202,   "章丹枫  ", "上虞拉轰战队               ",    OPEN},
    {203,   "张亮    ", "中国杭州闪电中老年扛车队   ",    OPEN},
    {204,   "陆成涛  ", "soco极限单车               ",    OPEN},
    {205,   "金也    ", "soco极限单车               ",    OPEN},
    {206,   "刘文国  ", "鬼魅仔                     ",    OPEN},
    {207,   "石振阳  ", "个人                       ",    OPEN},
    {208,   "徐生    ", "前进俱乐部                 ",    OPEN},
    {209,   "刘成路  ", "前进俱乐部                 ",    OPEN},
    {210,   "沈周庸  ", "腹肌bike                   ",    OPEN},
    {211,   "浦泽心  ", "陕西秦兽速降车队           ",    OPEN},
    {212,   "林泽栋  ", "深圳后山速降车队           ",    OPEN},
    {213,   "张鹤龄  ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {214,   "荣康    ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {215,   "何世雨  ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {216,   "王从林  ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {217,   "肖辉    ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {218,   "冯舒文  ", "上海魅力单车               ",    OPEN},
    {219,   "张孙彦  ", "上海魅力单车               ",    OPEN},
    {220,   "李瑞杰  ", "上海魅力单车               ",    OPEN},
    {221,   "鲍韦康  ", "上海魅力单车               ",    OPEN},
    {222,   "马凌轩  ", "上海魅力单车               ",    OPEN},
    {223,   "王舒    ", "上海魅力单车               ",    OPEN},
    {224,   "赵宗麟  ", "上海魅力单车               ",    OPEN},
    {225,   "窦安强  ", "上海魅力单车               ",    OPEN},
    {226,   "戴乐鸣  ", "上海魅力单车               ",    OPEN},
    {227,   "罗星    ", "上海魅力单车               ",    OPEN},
    {228,   "沈豪    ", "上海魅力单车               ",    OPEN},
    {229,   "黄行健  ", "厦门钢铁连                 ",    OPEN},
    {230,   "颜世顺  ", "厦门钢铁连                 ",    OPEN},
    {231,   "陈嘉伟  ", "厦门钢铁连                 ",    OPEN},
    {232,   "黄泽锋  ", "厦门钢铁连                 ",    OPEN},
    {233,   "曾杰    ", "飞客                       ",    OPEN},
    {234,   "俞琛阳  ", "Intense China              ",    OPEN},
    {235,   "樊浩辰  ", "双轮汇SLH Racing           ",    OPEN},
    {236,   "陆羽添  ", "双轮汇SLH Racing           ",    OPEN},
    {237,   "林雨寒  ", "West coast X Gravity lab   ",    OPEN},
    {238,   "马文博  ", "West coast x Gravity lab   ",    OPEN},
    {239,   "周韬    ", "West coast x Gravity lab   ",    OPEN},
    {240,   "王志明  ", "West coast x Gravity lab   ",    OPEN},
    {241,   "梅子晗  ", "West coast x Gravity lab   ",    OPEN},
    {242,   "胡清顺  ", "West coast x Gravity lab   ",    OPEN},
    {243,   "贺子木  ", "West coast x Gravity lab   ",    OPEN},
    {244,   "朱菊    ", "个人                       ",    OPEN},
    {245,   "刘飞    ", "嘉兴陨石                   ",    OPEN},
    {246,   "袁日境  ", "HIBP                       ",    OPEN},
    {247,   "宗朝贤  ", "个人                       ",    OPEN},
    {248,   "俞斌    ", "鬼魅仔                     ",    OPEN},
    {249,   "戴一唯  ", "soco极限单车               ",    OPEN},
    {250,   "甄东旭  ", "West coast x Gravity lab   ",    OPEN},
    {251,   "何鑫    ", "West coast x Gravity lab   ",    OPEN},
    {252,   "方子凡  ", "双轮汇SLH Racing           ",    OPEN},
    {253,   "应礼筋  ", "小溪速降                   ",    OPEN},
    {254,   "赵南    ", "个人                       ",    OPEN},
    {255,   "周小焜  ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {256,   "雷星    ", "HangZhou Giant Racing      ",    OPEN},
};
