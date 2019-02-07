#include "tcp.h"

struct {
    SSL_CTX* server;
    glv_mutex_t server_mtx;

    SSL_CTX* client;
    glv_mutex_t client_mtx;
} _ssl_ctx;

static int ssl_init() {
    static int is_inited = 0;
    if(is_inited)
        return 1;

    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    _ssl_ctx.server = SSL_CTX_new(SSLv23_server_method());
    if(!_ssl_ctx.server)
        return 0;

    _ssl_ctx.client = SSL_CTX_new(SSLv23_client_method());
    if(!_ssl_ctx.client)
        return 0;

    SSL_CTX_set_ecdh_auto(_ssl_ctx.server, 1);
    SSL_CTX_set_ecdh_auto(_ssl_ctx.client, 1);

    int success = 0;
    success |= SSL_CTX_use_certificate_file(
        _ssl_ctx.server,

    );
}