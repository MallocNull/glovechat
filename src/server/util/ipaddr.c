#include "ipaddr.h"

const ipaddr_t error_addr = {{0, 0, 0, 0, 0, 0, 0, 0}, -1};

ipaddr_t glv_ip_aton(const char* addr) {
    const int length = strlen(addr);
    ipaddr_t addr_out = {{0, 0, 0, 0, 0, 0, 0, 0}, 128};
    char token[5] = {0, 0, 0, 0, 0};
    int i, j = 0, k = 0, cidr = 0, gap = -1, valid, tmp;

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
            valid = 0;

            if(isdigit(addr[i])) {
                valid = 1;
                if(j == 3)
                    return error_addr;
                token[j++] = addr[i];
            }

            if(addr[i] == '.' || addr[i] == '/' || i == length - 1) {
                valid = 1;
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
                    addr_out.cidr = tmp + 96;
                }

                if(addr[i] == '/' && k != 4)
                    return error_addr;
            }

            if(!valid)
                return error_addr;
        }
    } else {
        if(strcnt(addr, ':') > 7)
            return error_addr;

        for(i = 0; i < length; ++i) {
            if(addr[i] == ' ')
                continue;
            valid = 0;

            if((isxdigit(addr[i]) && !cidr) || (isdigit(addr[i]) && cidr)) {
                valid = 1;
                if(j == 4)
                    return error_addr;
                token[j++] = addr[i];
            }

            if(addr[i] == ':' || addr[i] == '/' || i == length - 1) {
                valid = 1;
                if(j == 0 && !(k == 0 && i != length - 1 && addr[i + 1] == ':'))
                    return error_addr;

                token[j] = 0;
                tmp = cidr ? atoi(token) : axtoi(token);

                if(cidr) {
                    if(tmp > 128)
                        return error_addr;
                    addr_out.cidr = tmp;
                } else {
                    addr_out.addr[k] = tmp;
                    j = 0;
                    ++k;
                }

                if(addr[i] == '/')
                    cidr = 1;
                if(addr[i] == ':') {
                    if(cidr)
                        return error_addr;
                    if(i == length - 1)
                        return error_addr;
                    if(addr[i + 1] == ':') {
                        if(gap == -1) {
                            ++i;
                            gap = k - 1;
                            continue;
                        } else
                            return error_addr;
                    }
                }
            }

            if(!valid)
                return error_addr;
        }
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