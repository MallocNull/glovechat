#include "ipaddr.h"

const ipaddr_t error_addr = {{0, 0, 0, 0, 0, 0, 0, 0}, -1};

ipaddr_t glv_ip_aton(const char* addr) {
    ipaddr_t addr_out = {{0, 0, 0, 0, 0, 0, 0, 0}, 0};
    char token[5] = {0, 0, 0, 0, 0};
    const int length = strlen(addr);
    int i, j = 0, k = 0, tmp;

    if(strchr(addr, ':') != NULL && strchr(addr, '.') != NULL)
        return error_addr;
    if(strcnt(addr, '/') > 1)
        return error_addr;

    if(strchr(addr, '.') != NULL) {
        if(strcnt(addr, '.') != 3)
            return error_addr;

        addr_out.addr[5] = 0xFFFF;
        for(i = 0; i < length; ++i) {
            if(addr[i] == ' ')
                continue;
            else if(addr[i] == '.' || addr[i] == '/' || i == length - 1) {
                if(j == 0)
                    return error_addr;

                token[j] = 0;
                if((tmp = atoi(token)) > 255)
                    return error_addr;

                if(k < 4) {
                    addr_out.addr[6 + (k / 2)] |=
                        (tmp << (k % 2 == 0 ? 8 : 0));
                    j = 0;
                    ++k;
                } else {
                    if(tmp > 32)
                        return error_addr;
                    addr_out.cidr = tmp;
                }

                if(addr[i] == '/' && k != 4)
                    return error_addr;
            } else if(addr[i] >= '0' && addr[i] <= '9') {
                if(j == 3)
                    return error_addr;
                token[j++] = addr[i];
            } else
                return error_addr;
        }
    } else {
        if(strcnt(addr, ':') > 7)
            return error_addr;


    }

    return addr_out;
}

ipaddr_t glv_ip_raw(const uint16_t* addr, uint8_t cidr) {
    ipaddr_t addr_out;
    memcpy(addr_out.addr, addr, 16);
    addr_out.cidr = cidr;

    return addr_out;
}

int glv_ip_valid(const ipaddr_t* addr) {
    return addr->cidr == -1;
}