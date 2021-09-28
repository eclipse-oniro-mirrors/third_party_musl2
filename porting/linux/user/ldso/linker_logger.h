#include <stdarg.h>
#include <stdio.h>

// whether enable debug 
#define LINKER_DEBUG        1
// debug priority
#define DEBUG_LEVEL         1
// enabled debug modules
#define DEBUG_MOD           0b11111

//------------------------------------------------
//Do not change anything below unless you 
//want to add more debug information
//
//Change the defines above to enable/disable 
//specific debug options
//------------------------------------------------

extern int enable_log;

int linker_logger(char* tag, int priority, char* format, ...);
int linker_logger_va_list(const char* tag, int priotiry, char* format, va_list ap);

#define LOAD_LIB     (1 << 0)
#define FIND_SYM     (1 << 1)
#define DLS3         (1 << 2)
#define DL_OPEN      (1 << 3)
#define RELO         (1 << 4)

#define MACRO_STR(x)  {x, #x}

typedef struct _macro_str {
	int id;
	char* name;
}MACRO_STR_T;

int printvf(int mod, int priority, char* format, ...);

int error_log(int mod, char* format, ...);

int warn_log(int mod, char* format, ...);

int debug_log(int mod, char* format, ...);

int info_log(int mod, char* format, ...);

#define ERROR(t, x...) \
	do { \
		if ((t) & DEBUG_MOD) printvf(t, 4, x); \
	}while(0)

#define WARN(t, x...) \
	do { \
		if ((t) & DEBUG_MOD) printvf(t, 3, x); \
	}while(0)

#define DEBUG(t, x...)  if ((t) & DEBUG_MOD) {printvf(t, 2, x);} 


#define INFO(t, x...)   if ((t) & DEBUG_MOD) {printvf(t, 1, x);}


