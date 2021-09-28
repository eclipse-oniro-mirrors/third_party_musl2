#include <stdarg.h>
#include <stdio.h>
#include "linker_logger.h"

int enable_log = 1;

MACRO_STR_T m_macro_str[] = {
	MACRO_STR(LOAD_LIB),
        MACRO_STR(FIND_SYM),
        MACRO_STR(DLS3),
        MACRO_STR(DL_OPEN),
        MACRO_STR(RELO),
        {-1, NULL}
};

const char* get_macro_name(MACRO_STR_T* table, int id){
	int i = 0;
	while(table[i].id != -1 && table[i].name != NULL){
		if (table[i].id == id) return table[i].name;
			i++;
	}
	return "";
}

int linker_logger(char* tag, int priority, char* format, ...){
	int ret;
	va_list ap;
	va_start(ap, format);
	fprintf(stdout, "[%-8s\tpriority: %d]:\t", tag, priority);
	ret = vfprintf(stdout, format, ap);
	va_end(ap);
	return ret;
}

int linker_logger_va_list(const char* tag, int priority, char* format, va_list ap){
	int ret;
	fprintf(stdout, "[%-8s\tpriority: %d]:\t", tag, priority);
	ret = vfprintf(stdout, format, ap);
	return ret;
}

int check_mods(int mod, int priority){
	if ((LINKER_DEBUG & enable_log) == 0){
		return 1;
	}
	if (((mod) & DEBUG_MOD) == 0){
		return 2;
	}
	if (DEBUG_LEVEL > priority){
		return 3;
	}
	return 0;
}

int printvf(int mod, int priority, char* format, ...){
	if (check_mods(mod, priority) != 0){
	return 1;
	}
        int ret;
        const char* name = get_macro_name(m_macro_str, mod);
        va_list ap;
        va_start(ap, format);
        ret = linker_logger_va_list(name, priority, format, ap);
        va_end(ap);
        return ret;
}

int printvf_va_list(int mod, int priority, char* format, va_list ap){
        if (check_mods(mod, priority) != 0){
	        return 1;
	}
	int ret;
	const char* name = get_macro_name(m_macro_str, mod);
        ret = linker_logger_va_list(name, priority, format, ap);

        return ret;
}

int error_log(int mod, char* format, ...){
        va_list ap;
        va_start(ap, format);
        int ret = printvf_va_list(mod, 4, format, ap);
        va_end(ap);
        return ret;
}

int warn_log(int mod, char* format, ...){
        va_list ap;
        va_start(ap, format);
        int ret = printvf_va_list(mod, 3, format, ap);
        va_end(ap);
        return ret;
}

int debug_log(int mod, char* format, ...){
        va_list ap;
        va_start(ap, format);
        int ret = printvf_va_list(mod, 2, format, ap);
        va_end(ap);
        return ret;
}

int info_log(int mod, char* format, ...){
        va_list ap;
        va_start(ap, format);
        int ret = printvf_va_list(mod, 1, format, ap);
        va_end(ap);
        return ret;
}
