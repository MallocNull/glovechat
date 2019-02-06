#include "string.h"

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