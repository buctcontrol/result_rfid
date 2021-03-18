///racing_info.h
//
//

typedef void (*ceate_result_view_f)(void* racing);
typedef void (*load_info_f)(void* racing);
typedef void (*process_racing_f)(void* racing)

typedef struct
{
	///operations
	load_info_f load_info;
	ceate_result_view_f create_result_view;
	process_racing_f process;

	char* mode;
}HIBPRacing;

extern HIBPRacing* create_racing_info();
extern void release_racing_info(void* racing);
extern void load_racing_info(HIBPRacing* racing);
extern void process_racing(HIBPRacing* racing);
extern char* get_racing_mode(HIBPRacing* racing);

