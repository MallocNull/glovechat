#include <stdio.h>
#include "util/ipaddr.h"

int main(int argc, char** argv) {
    ipaddr_t a = glv_ip_aton("127.0.0.1/24");
    ipaddr_t b = glv_ip_aton("1234:5678::b00b:b00b:def0");
    char* out = glv_ipv6_ntoa(&a);
    return 0;
}