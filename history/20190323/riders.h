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
    {1,     "陈敏坤                         ", "HIBP                       ",    ELITE},
    {2,     "黄立观                         ", "Banshee Rock Team          ",    ELITE},
    {3,     "肖聪                           ", "GDR RACING TEAM            ",    ELITE},
    {4,     "唐梦麒                         ", "GDR RACING TEAM            ",    ELITE},
    {5,     "吴超                           ", "长沙顺时针车队             ",    ELITE},
    {6,     "叶晨琦                         ", "bking                      ",    ELITE},
    {7,     "李果                           ", "HIBP                       ",    ELITE},
    {8,     "张剑飞                         ", "soco极限单车               ",    ELITE},
    {9,     "叶正午                         ", "                           ",    ELITE},
    {10,    "刘楷杨                         ", "双轮汇SLH Racing           ",    ELITE},
    {11,    "丁再刚                         ", "勇峰自行车公园             ",    ELITE},
    {12,    "骆沙舟                         ", "杭州假日单车山地车队       ",    ELITE},
    {13,    "周吉强                         ", "杭州假日单车山地车队       ",    ELITE},
    {14,    "江思翰                         ", "歐亞馬小熊自行車隊         ",    ELITE},
    {15,    "周晓龙                         ", "双轮汇SLH Racing           ",    ELITE},
    {16,    "Yutaka Tamaru田丸裕            ", "Acciarpone Racing          ",    ELITE},
    {101,   "张佳莉                         ", "鬼魅仔                     ",    WOMAN},
    {102,   "杨书娜                         ", "前进俱乐部                 ",    WOMAN},
    {103,   "Danica Caiger-Smith            ", "双轮汇SLH Racing           ",    WOMAN},
    {104,   "周佩霓                         ", "闪电车队                   ",    WOMAN},
    {201,   "王利勇                         ", "个人                       ",    OPEN},
    {202,   "章丹枫                         ", "上虞拉轰战队               ",    OPEN},
    {203,   "张亮                           ", "中国杭州闪电中老年扛车队   ",    OPEN},
    {204,   "张程量                         ", "个人                       ",    OPEN},
    {205,   "文潇                           ", "个人                       ",    OPEN},
    {206,   "陆成涛                         ", "soco极限单车               ",    OPEN},
    {207,   "金也                           ", "soco极限单车               ",    OPEN},
    {208,   "刘文国                         ", "鬼魅仔                     ",    OPEN},
    {209,   "石振阳                         ", "个人                       ",    OPEN},
    {210,   "徐生                           ", "前进俱乐部                 ",    OPEN},
    {211,   "刘成路                         ", "前进俱乐部                 ",    OPEN},
    {212,   "沈周庸                         ", "腹肌bike                   ",    OPEN},
    {213,   "浦泽心                         ", "陕西秦兽速降车队           ",    OPEN},
    {214,   "林泽栋                         ", "深圳后山速降车队           ",    OPEN},
    {215,   "王浩哲                         ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {216,   "张鹤龄                         ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {217,   "荣康                           ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {218,   "何世雨                         ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {219,   "王从林                         ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {220,   "肖辉                           ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {221,   "吴观林                         ", "广西傲骑单车俱乐部         ",    OPEN},
    {222,   "冯舒文                         ", "上海魅力单车               ",    OPEN},
    {223,   "张孙彦                         ", "上海魅力单车               ",    OPEN},
    {224,   "李瑞杰                         ", "上海魅力单车               ",    OPEN},
    {225,   "鲍韦康                         ", "上海魅力单车               ",    OPEN},
    {226,   "马凌轩                         ", "上海魅力单车               ",    OPEN},
    {227,   "王舒                           ", "上海魅力单车               ",    OPEN},
    {228,   "赵宗麟                         ", "上海魅力单车               ",    OPEN},
    {229,   "窦安强                         ", "上海魅力单车               ",    OPEN},
    {230,   "戴乐鸣                         ", "上海魅力单车               ",    OPEN},
    {231,   "罗星                           ", "上海魅力单车               ",    OPEN},
    {232,   "沈豪                           ", "上海魅力单车               ",    OPEN},
    {233,   "曹彧鹏                         ", "厦门钢铁连                 ",    OPEN},
    {234,   "黄行健                         ", "厦门钢铁连                 ",    OPEN},
    {235,   "颜世顺                         ", "厦门钢铁连                 ",    OPEN},
    {236,   "陈嘉伟                         ", "厦门钢铁连                 ",    OPEN},
    {237,   "黄泽锋                         ", "厦门钢铁连                 ",    OPEN},
    {238,   "林世忠                         ", "西虹试飞客队               ",    OPEN},
    {239,   "曾杰                           ", "西虹试飞客队               ",    OPEN},
    {240,   "俞琛阳                         ", "Intense China              ",    OPEN},
    {241,   "李家成                         ", "双轮汇SLH Racing           ",    OPEN},
    {242,   "樊浩辰                         ", "双轮汇SLH Racing           ",    OPEN},
    {243,   "陆羽添                         ", "双轮汇SLH Racing           ",    OPEN},
    {244,   "林雨寒                         ", "West coast X Gravity lab   ",    OPEN},
    {245,   "马文博                         ", "West coast x Gravity lab   ",    OPEN},
    {246,   "周韬                           ", "West coast x Gravity lab   ",    OPEN},
    {247,   "王志明                         ", "West coast x Gravity lab   ",    OPEN},
    {248,   "梅子晗                         ", "West coast x Gravity lab   ",    OPEN},
    {249,   "胡清顺                         ", "West coast x Gravity lab   ",    OPEN},
    {250,   "贺子木                         ", "West coast x Gravity lab   ",    OPEN},
    {251,   "朱菊                           ", "个人                       ",    OPEN},
    {252,   "刘飞                           ", "嘉兴陨石                   ",    OPEN},
    {253,   "袁日境                         ", "HIBP                       ",    OPEN},
    {254,   "宗朝贤                         ", "个人                       ",    OPEN},
    {255,   "俞斌                           ", "鬼魅仔                     ",    OPEN},
    {256,   "戴一唯                         ", "soco极限单车               ",    OPEN},
    {257,   "甄东旭                         ", "West coast x Gravity lab   ",    OPEN},
    {258,   "何鑫                           ", "West coast x Gravity lab   ",    OPEN},
    {259,   "方子凡                         ", "双轮汇SLH Racing           ",    OPEN},
    {260,   "应礼筋                         ", "小溪速降                   ",    OPEN},
    {261,   "赵南                           ", "个人                       ",    OPEN},
    {262,   "周小焜                         ", "长沙CYCGO速行俱乐部        ",    OPEN},
    {263,   "雷星                           ", "HangZhou Giant Racing      ",    OPEN},
    {264,   "张祐纶                         ", "歐亞馬小熊自行車隊         ",    OPEN},
    {265,   "Baillod Yves Laurent Gabriel   ", "双轮汇SLH Racing           ",    OPEN},
    {266,   "Douglas-Jones Ian Neville      ", "双轮汇SLH Racing           ",    OPEN},
    {267,   "Paul McPherson                 ", "双轮汇SLH Racing           ",    OPEN},
    {268,   "李可轩                         ", "上虞跳跳驴                 ",    OPEN},
    {269,   "李星                           ", "上虞跳跳驴                 ",    OPEN},
};
