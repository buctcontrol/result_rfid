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
    {1,     "楼文钧                      ", "假日单车                                 ",             EBIKE },
    {2,     "章子俊                      ", "石舌章队                                 ",             EBIKE },
    {3,     "刘卓                        ", "虬龙科技                                 ",             EBIKE },
    {4,     "姜波                        ", "轻蜂摩嗨                                 ",             EBIKE },
    {5,     "姚路                        ", "轻蜂                                     ",             EBIKE },
    {6,     "王蒙                        ", "杭州Trek                                 ",             EBIKE },
    {7,     "仰海龙                      ", "蛟龙                                     ",             EBIKE },
    {101,   "雷星                        ", "HangZhou Giant Racing                    ",             MAN   },
    {102,   "吴超                        ", "长沙顺时针车队                           ",             MAN   },
    {103,   "周小焜                      ", "长沙CYCGO速行俱乐部                      ",             MAN   },
    {104,   "肖聪                        ", "北京GDR Racing Team                      ",             MAN   },
    {105,   "周吉强                      ", "杭州假日山地车队                         ",             MAN   },
    {106,   "黄立观                      ", "个人                                     ",             MAN   },
    {107,   "梅雨龙                      ", "假日单车山地车队                         ",             MAN   },
    {108,   "马琰                        ", "假日单车山地队                           ",             MAN   },
    {109,   "杜芳旭                      ", "CYCGO速行车队 兼长沙迪卡侬旗舰店运动大使 ",             MAN   },
    {110,   "宗朝贤                      ", "个人                                     ",             MAN   },
    {111,   "俞斌                        ", "鬼魅仔车队                               ",             MAN   },
    {112,   "杨琦                        ", "能量单车                                 ",             MAN   },
    {113,   "Anton Chalov                ", "Team Fuzzy Balls                         ",             MAN   }, 
    {114,   "Erik                        ", "Team Fuzzy Balls                         ",             MAN   }, 
    {115,   "Jethro Kang                 ", "Rehau                                    ",             MAN   }, 
    {116,   "黄俊熙                      ", "长沙半小时车队                           ",             MAN   },
    {117,   "谭钊                        ", "长沙半小时车队                           ",             MAN   },
    {118,   "洪辉熊                      ", "长沙半小时车队                           ",             MAN   },
    {119,   "周王忍                      ", "长沙半小时车队                           ",             MAN   },
    {120,   "徐鑫                        ", "长沙半小时车队                           ",             MAN   },
    {121,   "欧阳一茗                    ", "长沙半小时车队                           ",             MAN   },
    {122,   "李祖彜/Barry Lee            ", "西虹试飞客队                             ",             MAN   },
    {123,   "邓科                        ", "西虹试飞客队                             ",             MAN   },
    {124,   "黄浩                        ", "天空穿越车队                             ",             MAN   },
    {125,   "周鹰                        ", "天空穿越车队                             ",             MAN   },
    {126,   "黄乐                        ", "天空穿越车队                             ",             MAN   },
    {127,   "许中柱                      ", "天空穿越车队                             ",             MAN   },
    {128,   "李俊                        ", "天空穿越车队                             ",             MAN   },
    {129,   "王舒                        ", "上海魅力单车                             ",             MAN   },
    {130,   "Baillod Yves Laurent Gabriel", "上海魅力单车                             ",             MAN   },
    {131,   "马凌轩                      ", "上海魅力单车                             ",             MAN   },
    {132,   "彭先元                      ", "上海魅力单车                             ",             MAN   },
    {133,   "许皓                        ", "上海魅力单车                             ",             MAN   },
    {134,   "罗磊                        ", "蓝色单车                                 ",             MAN   },
    {135,   "周智文                      ", "蓝色单车                                 ",             MAN   },
    {136,   "金鑫越                      ", "上虞跳跳驴                               ",             MAN   },
    {137,   "陈南剑                      ", "蜗牛队                                   ",             MAN   },
    {138,   "张代行                      ", "蜗牛队                                   ",             MAN   },
    {139,   "喻杰                        ", "HangZhou Giant                           ",             MAN   },
    {140,   "马力                        ", "漫奇车队                                 ",             MAN   },
    {141,   "王宇                        ", "个人                                     ",             MAN   },
    {142,   "常容涛                      ", "mcc club                                 ",             MAN   },
    {143,   "王国栋                      ", "Byron                                    ",             MAN   },
    {144,   "应明浩                      ", "HIBP                                     ",             MAN   },
    {145,   "叶万达                      ", "鬼魅仔车队                               ",             MAN   },
    {201,   "浦慧菁                      ", "能量单车                                 ",             WOMAN },
    {202,   "陈海玲                      ", "能量单车                                 ",             WOMAN },
    {301,   "张洪豪                      ", "个人                                     ",             TASTE }, 
    {302,   "窦安强                      ", "上海魅力单车                             ",             TASTE }, 
    {303,   "项明                        ", "上海魅力单车                             ",             TASTE }, 
    {304,   "李程                        ", "省直机关自行车队                         ",             TASTE }, 
    {401,   "王杜                        ", "天空穿越车队                             ",             MASTER},
    {402,   "陈海川                      ", "西虹试飞客队                             ",             MASTER},
    {403,   "高一洋                      ", "上海魅力单车                             ",             MASTER},
    {404,   "戴乐鸣                      ", "上海魅力单车                             ",             MASTER},
    {405,   "ASH / 阿什                  ", "HIBP                                     ",             MASTER},
    {406,   "Mesum Verma                 ", "mtbmagasia                               ",             MASTER}, 
    {407,   "Peter Grogan                ", "Independent                              ",             MASTER}, 
    {408,   "Ian Douglas-Jones           ", "Team Fuzzy Balls                         ",             MASTER}, 
    {409,   "Mathieu                     ", "Team Fuzzy Balls                         ",             MASTER}, 
    {410,   "ian legend                  ", "Team Fuzzy Balls                         ",             MASTER}, 
    {411,   "Johannes                    ", "Team Fuzzy Balls                         ",             MASTER}, 
    {412,   "Andreas                     ", "Team Fuzzy Balls                         ",             MASTER}, 
    {413,   "肖庆                        ", "上海魅力单车                             ",             MASTER},
    {414,   "彭惟礼                      ", "上海魅力单车                             ",             MASTER},
    {415,   "严俊                        ", "上海魅力单车                             ",             MASTER},
    {416,   "赵翔                        ", "上海魅力单车                             ",             MASTER},
    {417,   "周辰烨                      ", "上海魅力单车                             ",             MASTER},
    {418,   "唐陈                        ", "上海魅力单车                             ",             MASTER},
    {419,   "朱陈华                      ", "上海魅力单车                             ",             MASTER},
    {420,   "徐煜寰                      ", "上海魅力单车                             ",             MASTER},
    {421,   "周炅闻                      ", "天空穿越车队                             ",             MASTER},
    {422,   "谢东珂                      ", "天空穿越车队                             ",             MASTER},
    {423,   "夏永照                      ", "西虹试飞客队                             ",             MASTER},
    {424,   "林正峯                      ", "西虹试飞客队                             ",             MASTER},
    {425,   "刘怡                        ", "省级机关自行车队                         ",             MASTER},
    {426,   "范旻                        ", "省级机关自行车队                         ",             MASTER},
    {427,   "朱嘉钧                      ", "能量单车                                 ",             MASTER},
    {428,   "林世忠                      ", "能量单车                                 ",             MASTER},
    {429,   "沈振亮                      ", "能量单车                                 ",             MASTER},
    {430,   "孙卫红                      ", "个人                                     ",             MASTER},
    {431,   "陈黎升                      ", "鬼魅仔车队                               ",             MASTER},
    {432,   "Woon Hon Siong              ", "鬼魅仔车队                               ",             MASTER},
    {433,   "吴双                        ", "假日单车山地队                           ",             MASTER},
};
