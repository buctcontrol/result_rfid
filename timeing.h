#ifndef TIMEING_H
#define TIMEING_H

#include <stdint.h>

typedef struct 
{
    int rider_no;
	int stage;
	int is_start;
	int is_transfer;
    uint64_t time; //ms
}HIBPTime;

extern int timeing_read(const char* fname, HIBPTime* t);

#endif/*TIMEING_H*/
