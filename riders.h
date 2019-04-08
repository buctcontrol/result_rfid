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

#ifndef RIDERS_H
#define RIDERS_H

#define _MAX_RIDERS	512
#define _PATH_RIDERS 	"./riders_info.csv"
#define _MAX_GROUPS 	10

#include "interface.h"



typedef struct
{
    unsigned int    number;
    char            name[64];
    char            team[128];
    char 	    result_time[16];//hh:mm:ss.mmm
    int 	    group;
    INTERFACE	    results[10];//results[0] is the final result
}HIBPRiderInfo;

typedef struct
{
	int group;
	HIBPRiderInfo riders[_MAX_RIDERS];
	int nriders;
}HIBPGroupRider;


///get riders info by rider's number
extern HIBPRiderInfo* get_rider_info(int No);
extern HIBPGroupRider* get_groups();
extern int get_groups_count();
extern void swap_rider(HIBPRiderInfo* src, HIBPRiderInfo* dst);

///if @return 1 so swap src and dst, if return 0 do not swap them. 
typedef int (*fcompare_rider)(const HIBPRiderInfo* src, const HIBPRiderInfo* dst);
extern void sort_riders(HIBPGroupRider* groups, int groups_count, fcompare_rider fcompare);

#endif /*RIDERS_H*/
