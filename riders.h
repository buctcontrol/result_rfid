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

#include "interface.h"

#define _MAX_RIDERS 1024
#define _MAX_GROUP 10


typedef struct
{
    unsigned int    number;
    char            name[64];
    char            team[128];
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

