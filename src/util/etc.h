#ifndef GLV_UTIL_STRING_H
#define GLV_UTIL_STRING_H

#define MAX(X,Y) (((X)>(Y))?(X):(Y))
#define MIN(X,Y) (((X)<(Y))?(X):(Y))

// STDOUT DEFS
#define GLV_INFO    "[ INFO ] "
#define GLV_WARN    "[ WARN ] "
#define GLV_ERR     "[ ERROR ] "
#define GLV_CRIT    "[ CRITICAL ] "

// AUX STRING FUNCS
#define GLV_STRLEN 0

typedef char(*trans_func_t)(char);

char* strtrans(char* str, trans_func_t func);
char* strlower(char* str);
char* strupper(char* str);

int axtoi(const char* str);
int strcnt(const char* str, char c);

char* ltrim(char* str);
char* rtrim(char* str);
char* trim(char* str);

#endif
