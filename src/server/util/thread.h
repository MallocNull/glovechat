#ifndef GLV_UTIL_THREAD_H
#define GLV_UTIL_THREAD_H

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #ifdef __MINGW32__
    #undef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WIN8
  #endif
  #include <windows.h>

  typedef HANDLE glv_thread_t;
  typedef HANDLE glv_mutex_t;
#else
  #include <pthread.h>

  typedef pthread_t glv_thread_t;
  typedef pthread_mutex_t glv_mutex_t;
#endif

#include <stdlib.h>
typedef void(*glv_func_t)(void*);

glv_thread_t* glv_thread_create(glv_func_t func, void* args);
void glv_thread_join(glv_thread_t* thread);
void glv_thread_destroy(glv_thread_t* thread);

/** END THREAD DECLS **/
/**********************/
/** BEGIN MUTX DECLS **/

glv_mutex_t* glv_mutex_create();
void glv_mutex_lock(glv_mutex_t* mutex);
void glv_mutex_unlock(glv_mutex_t* mutex);
void glv_mutex_destroy(glv_mutex_t* mutex);

#endif
