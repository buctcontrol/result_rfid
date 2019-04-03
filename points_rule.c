
int split (const char *txt, char delim, char ***tokens)
{
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}

char** strsplit(char* str, const char* delim, int *count){
    char** res = NULL;
    char*  part;
    int i = 0;

    char* aux = strdup(str);

    part = strdup(strtok(aux, delim));

    while(part){
        res = (char**)realloc(res, (i + 1) * sizeof(char*));
        *(res + i) = strdup(part);

        part = strdup(strtok(NULL, delim));
        i++;
    }

    res = (char**)realloc(res, i * sizeof(char*));
    *(res + i) = NULL;

    return res;
}

static void free_arr(void** arr, int n)
{
	for(i=0; i<n; i++)
		free(arr[i]);
	
	free(arr);
}

static int find_column(const char* buf, const char* key)
{
	int count=0;
	int i;
	char **fields = strsplit(buf, ",", &count);
	for(i=0; i<count; i++){
		if(strcmp(key, fields[i])==0){
			free(fields);
			return i;
		}
	}

	free(fields);
	return -1;
}

static int get_column_i(const char* buf, int idx) 
{
	int count=0;
	int val=-1;
	char **fields = strsplit(buf, ",", &count);
	if(idx < count)
		val = atoi(fields[idx]);	

	free(fields);
	return val;
}

int get_points(int position, int group)
{
	int points=0;
	int col;
	char buf[128];

	file_gets(buf);
	col =  find_column(buf, groupStr[group]);
	file_open("points_rule.csv", "r");
	while( file_gets(buf) != NULL)
	{
		if(position == get_column_i(buf, 0)){
			points = get_column_i(buf, col);
			break;
		}
	}

	return points;
}
