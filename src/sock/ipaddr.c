#include "ipaddr.h"

const ipaddr_t error_addr = {{0, 0, 0, 0, 0, 0, 0, 0}, -1};

ipaddr_t glv_ip_aton(const char* addr) {
    const int length = strlen(addr);
    ipaddr_t addr_out = {{0, 0, 0, 0, 0, 0, 0, 0}, 128};
    char token[5] = {0, 0, 0, 0, 0};
    int i, j = 0, k = 0, cidr = 0, gap = -2, valid, tmp;

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
                if  (j == 0 &&
                   !(k == 0 && i != length - 1 && addr[i + 1] == ':') &&
                   !(i - 2 >= 0 && addr[i] == '/' &&
                     addr[i - 1] == ':' && addr[i - 2] == ':'))
                {
                    return error_addr;
                }

                token[j] = 0;
                tmp = cidr ? atoi(token) : axtoi(token);

                if(cidr) {
                    if(tmp > 128)
                        return error_addr;
                    addr_out.cidr = tmp;
                } else if(j != 0) {
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
                        if(gap == -2) {
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

        if(gap > -2) {
            for(i = k - 1; i > gap; --i) {
                addr_out.addr[7 - (k - 1 - i)] = addr_out.addr[i];
                addr_out.addr[i] = 0;
            }
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

int glv_ip_check(const char* addr) {
    ipaddr_t test = glv_ip_aton(addr);
    return glv_ip_valid(&test);
}

int glv_ip_compare(const ipaddr_t* lhs, const ipaddr_t* rhs) {
    int i = 0, lhs_cidr = lhs->cidr, rhs_cidr = rhs->cidr, mask;
    for(i = 0; i < 8; ++i) {
        mask = 0xFFFF
             & ~((1 << (16 - MIN(16, lhs_cidr))) - 1)
             & ~((1 << (16 - MIN(16, rhs_cidr))) - 1);
        if(mask == 0)
            break;

        if((lhs->addr[i] & mask) != (rhs->addr[i] & mask))
            return 0;

        lhs_cidr = MAX(0, lhs_cidr - 16);
        rhs_cidr = MAX(0, rhs_cidr - 16);
    }

    return 1;
}

int glv_ip_identical(const ipaddr_t* lhs, const ipaddr_t* rhs) {
    int i;
    for(i = 0; i < 8; ++i)
        if(lhs->addr[i] != rhs->addr[i])
            return 0;

    return 1;
}

int glv_ip_isv4(const ipaddr_t* addr) {
    return addr->addr[0] == 0 && addr->addr[1] == 0 &&
           addr->addr[2] == 0 && addr->addr[3] == 0 &&
           addr->addr[4] == 0 && addr->addr[5] == 0xFFFF;
}

int glv_ip_valid(const ipaddr_t* addr) {
    return addr->cidr <= 128;
}

char* glv_ip_ntoa(const ipaddr_t* addr) {
    if(!glv_ip_isv4(addr))
        return glv_ipv6_ntoa(addr);
    if(!glv_ip_valid(addr))
        return NULL;

    char* ip = malloc(18 * sizeof(char));
    if(addr->cidr == 128) {
        sprintf(ip, "%i.%i.%i.%i",
            (addr->addr[6] >> 8) & 0xFF,
            (addr->addr[6])      & 0xFF,
            (addr->addr[7] >> 8) & 0xFF,
            (addr->addr[7])      & 0xFF
        );
    } else {
        sprintf(ip, "%i.%i.%i.%i/%i",
            (addr->addr[6] >> 8) & 0xFF,
            (addr->addr[6])      & 0xFF,
            (addr->addr[7] >> 8) & 0xFF,
            (addr->addr[7])      & 0xFF,
            (addr->cidr - 96)
        );
    }

    return ip;
}

char* glv_ipv6_ntoa(const ipaddr_t* addr) {
    if(!glv_ip_valid(addr))
        return NULL;

    char* ip = malloc(43 * sizeof(char));
    int i, jmp = 0, largest_gap_pos = -1, largest_gap_len = 0, curr_gap_len = 0;

    for(i = 0; i < 8; ++i) {
        if(addr->addr[i] == 0 && i < 7)
            ++curr_gap_len;
        else {
            if(curr_gap_len > largest_gap_len && curr_gap_len > 1) {
                largest_gap_len = curr_gap_len;
                largest_gap_pos = i - curr_gap_len;
            }

            curr_gap_len = 0;
        }
    }

    for(i = 0; i < 8; ++i) {
        if(i == largest_gap_pos) {
            sprintf(ip, (i == 0 ? "::" : "%s:") , ip);
            i += largest_gap_len - 1;
            jmp = 1;
        } else if(!(jmp && i == 7)) {
            sprintf(ip, (i == 7 ? "%s%x" : "%s%x:"), ip, addr->addr[i]);
            jmp = 0;
        }
    }

    if(addr->cidr < 128)
        sprintf(ip, "%s/%i", ip, addr->cidr);

    return ip;
}