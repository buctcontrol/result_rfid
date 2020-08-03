///racing_info.h
//
//

extern void load_racing_info();
extern char* racing_get_mode();

//return > 0 yes ==0 no
extern int is_has_transfer(int stage);
extern int is_has_transfer_group(int group);
extern char* get_transer_shut_time(int group, int stage);

//extern int racing_get_curstage();
extern int racing_get_stages();

extern int racing_get_curround();
