#include "etc.h"

#include <string.h>
#include <ctype.h>

int axtoi(const char* str) {
    int value = 0, i;
    for(i = 0; i < strlen(str); ++i) {
        value *= 16;
        if(str[i] >= '0' && str[i] <= '9')
            value += str[i] - '0';
        else if(str[i] >= 'a' && str[i] <= 'f')
            value += (str[i] - 'a') + 10;
        else if(str[i] >= 'A' && str[i] <= 'F')
            value += (str[i] - 'A') + 10;
    }

    return value;
}

int strcnt(const char* str, char c) {
    int cnt = 0, i;
    for(i = 0; i < strlen(str); ++i)
        if(str[i] == c)
            ++cnt;

    return cnt;
}

char* strtrans(char* str, trans_func_t func) {
    int length = strlen(str), i;
    for(i = 0; i < length; ++i)
        str[i] = func(str[i]);

    return str;
}

char* strlower(char* str) {
    return strtrans(str, tolower);
}

char* strupper(char* str) {
    return strtrans(str, toupper);
}

char* ltrim(char* str) {
    int length = strlen(str), i;
    for(i = 0; i < length; ++i)
        if(str[i] > ' ')
            break;
    if(i > 0)
        strcpy(str, str + i);

    return str;
}

char* rtrim(char* str) {
    int length = strlen(str), i;
    for(i = length - 1; i >= 0; --i) {
        if(str[i] <= ' ')
            str[i] = '\0';
        else
            break;
    }

    return str;
}

char* trim(char* str) {
    return ltrim(rtrim(str));
}