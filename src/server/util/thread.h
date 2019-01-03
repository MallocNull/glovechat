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

glv_thread_t* glv_thread_create();
void glv_thread_destroy(glv_thread_t* thread);

#endif
