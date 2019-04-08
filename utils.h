//utils.h

#ifndef UTILS_H
#define UTILS_H

///csv file operations
extern int find_column(const char* buf, const char* key);
extern int get_column_i(const char* buf, int idx); 
extern char* get_column_str(const char* buf, int idx, char val[]);


extern int file_open(const char* filename, const char* mode);
extern void file_puts(const char* buf);
extern char* file_gets(char* buf, int size);
extern void file_close();



extern struct interface * cliFindClassById(int nClsId);


#endif /*UTILS_H*/
