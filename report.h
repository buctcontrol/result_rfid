///report.h

#ifndef REPORT_H
#define REPORT_H

#include "riders.h"
#include "results.h"

//////////////////////////////////////////////////////////////
typedef struct 
{
    HIBPRiderInfo* rider;
    Result* result;
	int rank;
	int score;
    //Additional* add;
}HIBPReportItem;


//////////////////////////////////////////////////////////////
typedef struct 
{
    HIBPReportItem* items;
    int nitems;
	int groups[10];
	int ngroups;
}HIBPReportView;

extern HIBPReportView* create_report_view(int nriders);

extern void stage_update_report(HIBPReportView* report, HIBPGroupList* groups, void* results);

#endif /*REPORT_H*/
