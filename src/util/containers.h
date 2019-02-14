#ifndef GLV_UTIL_CONTAINERS_H
#define GLV_UTIL_CONTAINERS_H

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

glv_map_t* glv_map_create();
glv_map_t* glv_map_create_ex(int initial_size);

void glv_map_destroy(glv_map_t* map);
void glv_map_destroy_dealloc(glv_map_t* map);

#endif
