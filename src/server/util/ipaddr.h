#ifndef GLV_UTIL_IPADDR_H
#define GLV_UTIL_IPADDR_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "util/string.h"

typedef struct {
    uint16_t addr[8];
    uint8_t cidr;
} ipaddr_t;

ipaddr_t glv_ip_aton(const char* addr);
ipaddr_t glv_ip_raw(const uint16_t* addr, uint8_t cidr);
int glv_ip_check(const char* addr);

int glv_ip_compare(const ipaddr_t* lhs, const ipaddr_t* rhs);
int glv_ip_identical(const ipaddr_t* lhs, const ipaddr_t* rhs);
int glv_ip_isv4(const ipaddr_t* addr);
int glv_ip_valid(const ipaddr_t* addr);

char* glv_ip_ntoa(const ipaddr_t* addr);
char* glv_ipv6_ntoa(const ipaddr_t* addr);

#endif