///interface.c


#include <stdio.h>
#include "racing_info.h"
#include <sys/resource.h>

int main(void)
{
	struct rlimit r;
	r.rlim_cur= 8*1024*1024*10;//stack size 80MB
	setrlimit(RLIMIT_STACK, &r);
	getrlimit(RLIMIT_STACK, &r);
	printf("stack limit:cur=%ld\n", r.rlim_cur);

	HIBPRacing* racing = create_racing_info();	
    load_racing_info(racing);
	char* mode = get_racing_mode(racing);
    printf("process [%s] racing mode.\n", mode);
    process_racing(racing);
    printf("finished process racing.\n");
	delete_racing_info(racing);

	return 0;
}

