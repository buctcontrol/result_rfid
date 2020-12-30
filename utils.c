///utils.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

char** strsplit(const char* str, const char* delim, int *count)
{
    	char** res = NULL;
    	char*  part;
    	int i = 0;

    	char* aux = strdup(str);

    	part = strtok(aux, delim);

    	while(part){
    	    res = (char**)realloc(res, (i + 1) * sizeof(char*));
    	    *(res + i) = strdup(part);

    	    part = strtok(NULL, delim);
    	    i++;
    	}

    	*count = i;
        free(aux);
    	return res;
}

static void free_arr(char** arr, int n)
{
	int i;
	for(i=0; i<n; i++)
		free(arr[i]);
	
	free(arr);
}
int find_column(const char* buf, const char* key)
{
	int count=0;
	int i;
	char **fields = strsplit(buf, ",", &count);
	for(i=0; i<count; i++){
		if(strstr(fields[i], key) != NULL){
			free_arr(fields, count);
			return i;
		}
	}

	free_arr(fields, count);
	return -1;
}

int get_column_i(const char* buf, int idx) 
{
	int count=0;
	int val=-1;
	char **fields = strsplit(buf, ",", &count);
	if(idx < count)
		val = atoi(fields[idx]);	

	free_arr(fields, count);
	return val;
}


int get_column_f(const char* buf, int idx) 
{
	int count=0;
	int val=-1;
	char **fields = strsplit(buf, ",", &count);
	if(idx < count)
		val = atof(fields[idx]);	

	free_arr(fields, count);
	return val;
}

char* get_column_str(const char* buf, int idx, char val[]) 
{
	int count=0;
	char **fields = strsplit(buf, ",", &count);
	if(idx < count)
		strcpy(val, fields[idx]);	

	free_arr(fields, count);
	return val;
}



static FILE* fp=NULL;
int file_open(const char* filename, const char* mode){
	fp = fopen(filename, mode);
	if(fp== NULL){
		perror("fopen");
		return 0;
	}

	return 1;
}
		 
void file_puts(const char* buf)
{
	printf("%s", buf);
	fputs(buf, fp);
}

char* file_gets(char* buf, int size)
{
	return fgets(buf, size, fp);
}

void file_close()
{
	fclose(fp);	
}




struct interface * cliFindClassById(int nClsId)
{
	struct interface  *pCls = NULL;
	struct list_head* pPos = NULL;

	list_for_each(pPos, &g_ife.list)
	{
		pCls = list_entry(pPos, struct interface, list);
		if(pCls->id == nClsId)
			return pCls;
	}

	return NULL;
}

///time format hh:mm:ss.ms
void to_time_str(char* str, int sec, int msec)
{
	sprintf(str, "%02d:%02d:%02d.%03d", 
		(sec/60/60)%24, (sec/60)%60, (sec%60), msec
	);
}


///time format hh:mm:ss.ms
void to_time_sec(char* str, int* sec, int* msec)
{
	char**ss;
	int count;
	ss = strsplit(str, ".", &count);
	if(count !=2 ){
		*sec = -1;
		*msec = -1;
		return;
	}

	char *sec_str = ss[0];
	char *msec_str = ss[1];
	*msec = atoi(msec_str);
	ss = strsplit(sec_str, ":", &count);
	if(count !=3 ){
		*sec = -1;
		*msec = -1;
		return;
	}
	
	
	char *h_str = ss[0];
	char *m_str = ss[1];
	char *s_str = ss[2];
	*sec = atoi(h_str)*60*60 + atoi(m_str)*60 + atoi(s_str);
}


