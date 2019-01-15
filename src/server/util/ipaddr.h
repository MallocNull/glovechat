#ifndef GLV_UTIL_IPADDR_H
#define GLV_UTIL_IPADDR_H

#include <stdint.h>

typedef struct {
    uint8_t addr[16];
    uint8_t cidr;
} ipaddr_t;

ipaddr_t glv_ip_aton(char* addr, int length);
ipaddr_t glv_ip_raw(uint8_t* addr, uint8_t cidr);

int glv_ip_compare(ipaddr_t* lhs, ipaddr_t* rhs);
int glv_ip_identical(ipaddr_t* lhs, ipaddr_t* rhs);
int glv_ip_isv4(ipaddr_t* addr);

int glv_ip_ntoa(ipaddr_t* addr, char* out);

#endif