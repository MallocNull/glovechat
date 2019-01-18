#include <stdio.h>
#include "util/ipaddr.h"

int main(int argc, char** argv) {
    ipaddr_t test = glv_ip_aton("192.168.1.150/24");
    return 0;
}