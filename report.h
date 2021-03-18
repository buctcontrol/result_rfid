///report.h

#ifndef REPORT_H
#define REPORT_H

#include "riders.h"

//////////////////////////////////////////////////////////////
typedef struct 
{
    int rider_no;
    HIBPStageReuslt* results;
    int nresults;
    //ADDITIONAL_T add;
}HIBPReportItem;

HIBPReportItem* alloc_result();
void free_result(HIBPReportItem* result);


//////////////////////////////////////////////////////////////
typedef struct 
{
    int group_no;
    HIBPReportItem* items;
    int nitems;
}HIBPReport;

HIBPReport* alloc_result();
void free_result(HIBPReport* result);


//////////////////////////////////////////////////////////////
typedef struct 
{
    HIBPReport* reports;
    int nreports;
}HIBPReportView;

HIBPReportView* create_report_view(int n);
void load_report_view(HIBPReportView* view);
void save_report_view(HIBPReportView* view);
HIBPReport* get_report(int group_no);

extern void generate_report_stage(int stage); 
extern void save_report(HIBPGroupRider* groups, int groups_count, const char* filename);

#endif /*REPORT_H*/
