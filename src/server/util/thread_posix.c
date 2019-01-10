#ifndef _WIN32
#include "thread.h"

typedef struct {
    glv_func_t func;
    void* args;
} wrapper_t;

static void* _wrapper_func(void* proxy) {
    wrapper_t wrapper = *((wrapper_t*)proxy);
    free(proxy);

    wrapper.func(wrapper.args);
}

glv_thread_t* glv_thread_create(glv_func_t func, void* args) {
    wrapper_t* proxy = malloc(sizeof(wrapper_t));
    proxy->func = func;
    proxy->args = args;

    glv_thread_t* thread = malloc(sizeof(thread));
    if(pthread_create(thread, NULL, _wrapper_func, proxy) == 0)
        return thread;
    else
        return NULL;
}

void glv_thread_join(glv_thread_t* thread) {
    pthread_join(*thread, NULL);
}

void glv_thread_destroy(glv_thread_t* thread) {
    free(thread);
}

/** END THREAD IMPL **/
/*********************/
/** BEGIN MUTX IMPL **/

glv_mutex_t* glv_mutex_create() {

}

#endif
