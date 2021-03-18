#ifndef TIMEING_H
#define TIMEING_H

typedef struct 
{
    int rider_no;
    uint64_t time; //ms
}HIBPTime;

extern int timeing_read(const char* fname, HIBPTime& t);

#endif/*TIMEING_H*/
