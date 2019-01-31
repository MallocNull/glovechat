#include <stdio.h>
#include "util/ipaddr.h"

int main(int argc, char** argv) {
    ipaddr_t test = glv_ip_aton("1234::/64");
    return 0;
}