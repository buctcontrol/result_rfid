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
