///racing_info.h
//
//

extern void load_racing_info();
extern char* racing_get_mode();

//stage start from 1.
//return > 0 yes ==0 no
extern int is_has_transfer(int stage);
extern char* get_transer_shut_time(int stage);

//extern int racing_get_curstage();
extern int racing_get_stages();

//stage start from 1.
//return > 0 yes ==0 no
extern int isLastStage(int stage);

extern int racing_get_curround();
