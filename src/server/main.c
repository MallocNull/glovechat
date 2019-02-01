#include <stdio.h>
#include "util/ipaddr.h"

int main(int argc, char** argv) {
    ipaddr_t a = glv_ip_aton("1234:5678::b00b:d00d:def0/62");
    ipaddr_t b = glv_ip_aton("1234:5678::b00b:b00b:def0");
    char* out = glv_ip_ntoa(&a);
    return 0;
}