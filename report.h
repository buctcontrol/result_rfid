///report.h

#ifndef REPORT_H
#define REPORT_H

#include "riders.h"

extern void generate_report_stage(int stage); 
extern void save_report(HIBPGroupRider* groups, int groups_count, const char* filename);

#endif /*REPORT_H*/
