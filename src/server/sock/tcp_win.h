#ifndef GLOVE_SOCK_TCP_H
#define GLOVE_SOCK_TCP_H

#include <stdint.h>

#define TCP_FLAG_TYPE           1
#define TCP_FLAG_NONBLOCKING    2

typedef struct {
    uint32_t flags;
} tcp_t;

tcp_t* tcp_create_server();
tcp_t* tcp_create_client();

void tcp_destroy(tcp_t* socket);

#endif
