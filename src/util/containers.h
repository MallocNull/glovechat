#ifndef GLV_UTIL_CONTAINERS_H
#define GLV_UTIL_CONTAINERS_H

#include <stdlib.h>
#include <string.h>

/** STRING HASHMAP START **/

typedef struct {
    void* key;
    void* value;
} glv_pair_t;

typedef struct {
    glv_pair_t** buckets;
    int* bucket_lengths;
    int bucket_count;
    int pair_count;
} glv_map_t;

typedef void (*glv_map_dealloc_func)(void*);

glv_map_t* glv_map_create();
glv_map_t* glv_map_create_ex(int initial_size);

void* glv_map_get(glv_map_t* map, const char* key);

void* glv_map_set(glv_map_t* map, const char* key, void* value);
void* glv_map_set_copy
    (glv_map_t* map, const char* key, void* value, size_t length);

void* glv_map_remove(glv_map_t* map, const char* key);
void glv_map_remove_dealloc(glv_map_t* map, const char* key);

int glv_map_has_key(glv_map_t* map, const char* key);
void glv_map_resize(glv_map_t* map, int size);

void glv_map_destroy(glv_map_t* map);
void glv_map_destroy_dealloc(glv_map_t* map);
void glv_map_destroy_dealloc_func(glv_map_t* map, glv_map_dealloc_func func);

/** STRING HASHMAP END **/

#endif
