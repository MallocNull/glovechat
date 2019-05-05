#ifdef _WIN32
#include "thread.h"

glv_thread_t* glv_thread_create(glv_func_t func, void* args) {
    glv_thread_t* thread = malloc(sizeof(glv_thread_t));
    *thread = (glv_thread_t)_beginthread(func, 0, args);

    return thread;
}

void glv_thread_join(glv_thread_t* thread) {
    WaitForSingleObject(*thread, INFINITE);
}

void glv_thread_destroy(glv_thread_t* thread) {
    CloseHandle(*thread);
    free(thread);
}

/** END THREAD IMPL **/
/*********************/
/** BEGIN MUTX IMPL **/

glv_mutex_t* glv_mutex_create(void) {
    glv_mutex_t* mutex = malloc(sizeof(glv_mutex_t));
    *mutex = CreateMutexA(NULL, NULL, NULL);

    return mutex;
}

void glv_mutex_lock(glv_mutex_t* mutex) {
    WaitForSingleObject(*mutex, INFINITE);
}

void glv_mutex_unlock(glv_mutex_t* mutex) {
    ReleaseMutex(*mutex);
}

void glv_mutex_destroy(glv_mutex_t* mutex) {
    CloseHandle(*mutex);
    free(mutex);
}

#endif