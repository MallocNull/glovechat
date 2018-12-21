#ifndef GLV_SOCK_TCP_H
#define GLV_SOCK_TCP_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
  #ifdef __MINGW32__
    #undef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WIN8
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>

  typedef GLV_SOCK_T SOCKET;
  typedef GLV_ADDR_T SOCKADDR_

  #define GLV_SOCK_T SOCKET
  #define GLV_ADDR_T SOCKADDR_IN
#else
  #include <arpa/inet.h>
  #include <errno.h>
  #include <fcntl.h>
  #include <netdb.h>
  #include <netinet/in.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <unistd.h>

  #define GLV_SOCK_T int
  #define GLV_ADDR_T struct sockaddr_in
#endif

#include <stdint.h>

#define GLV_TCP_FLAG_TYPE   1
#define GLV_TCP_FLAG_NBIO   2

typedef struct {
    uint32_t flags;
} tcp_t;

tcp_t* tcp_create_server();
tcp_t* tcp_create_client();



void tcp_destroy(tcp_t* socket);

#endif
