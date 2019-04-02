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


typedef struct
{
    unsigned int    number;
    char            name[64];
    char            team[128];
    unsigned int    group;
}HIBPRiderInfo;

typedef struct
{
	int group;
	int riders[_MAX_RIDERS];
	int nriders;
}HIBPGroupRider;

///get riders info by rider's number
extern HIBPRiderInfo* get_rider_info(int No);

