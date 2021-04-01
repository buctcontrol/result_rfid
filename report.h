///report.h

#ifndef REPORT_H
#define REPORT_H

#include "riders.h"

//////////////////////////////////////////////////////////////
typedef struct 
{
    HIBPRiderInfo* rider;
    Reuslt* result;
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

extern void update_report(HIBPRacing* racing);

#endif /*REPORT_H*/
