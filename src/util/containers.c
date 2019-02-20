#include "containers.h"

/** STRING HASHMAP START **/

#define GLV_MAP_DEFAULT_BUCKETS 8

static int glv_map_hash_func(const char* key) {
    int hash = 7, length = strlen(key), i;
    for(i = 0; i < length; ++i)
        hash = hash * 31 + key[i];

    return hash;
}

glv_map_t* glv_map_create() {
    return glv_map_create_ex(GLV_MAP_DEFAULT_BUCKETS);
}

glv_map_t* glv_map_create_ex(int initial_size) {
    glv_map_t* map = malloc(sizeof(glv_map_t));
    map->buckets = NULL;
    map->pair_count = 0;

    glv_map_resize(map, initial_size);
    return map;
}

void* glv_map_get(glv_map_t* map, const char* key) {
    int hash = glv_map_hash_func(key) % map->bucket_count, i;

    for(i = 0; i < map->bucket_lengths[hash]; ++i)
        if(map->buckets[hash][i].key != NULL &&
           strcmp(map->buckets[hash][i].key, key) == 0)
            return map->buckets[hash][i].value;

    return NULL;
}

void* glv_map_set(glv_map_t* map, const char* key, void* value) {
    if(value == NULL)
        return NULL;

    int hash = glv_map_hash_func(key), i;
    glv_pair_t* pair;
    char* copy;
    void* tmp;

    if(glv_map_has_key(map, key)) {
        hash = hash % map->bucket_count;
        for(i = 0; i < map->bucket_lengths[hash]; ++i) {
            if(strcmp(map->buckets[hash][i].key, key) == 0) {
                tmp = map->buckets[hash][i].value;
                map->buckets[hash][i].value = value;
                return tmp;
            }
        }
    } else {
        if(map->pair_count + 1 > map->bucket_count * 2)
            glv_map_resize(map, map->bucket_count * 2);

        hash = hash % map->bucket_count;

        map->buckets[hash] =
            realloc(map->buckets[hash], ++(map->bucket_lengths[hash]));
        copy = malloc((strlen(key) + 1) * sizeof(char));
        strcpy(copy, key);

        map->buckets[hash][map->bucket_lengths[hash] - 1].key = copy;
        map->buckets[hash][map->bucket_lengths[hash] - 1].value = value;
        ++(map->pair_count);
    }

    return NULL;
}

void* glv_map_set_copy
    (glv_map_t* map, const char* key, void* value, size_t length)
{
    void* copy = malloc(length);
    memcpy(copy, value, length);

    return glv_map_set(map, key, copy);
}

void* glv_map_remove(glv_map_t* map, const char* key) {
    int hash = glv_map_hash_func(key) % map->bucket_count, i;
    void* value;

    for(i = 0; i < map->bucket_lengths[hash]; ++i) {
        if(map->buckets[hash][i].key != NULL &&
           strcmp(map->buckets[hash][i].key, key) == 0)
        {
            free(map->buckets[hash][i].key);
            value = map->buckets[hash][i].value;

            return value;
        }
    }

    return NULL;
}

int glv_map_has_key(glv_map_t* map, const char* key) {
    return glv_map_get(map, key) == NULL;
}

void glv_map_resize(glv_map_t* map, int size) {
    glv_pair_t** new_buckets = calloc(size, sizeof(glv_pair_t*));
    int* new_lengths = calloc(size, sizeof(int));
    int i, j, hash;

    for(i = 0; i < map->bucket_count; ++i) {
        for(j = 0; j < map->bucket_lengths[i]; ++j) {
            if(map->buckets[i][j].key == NULL)
                continue;

            hash = glv_map_hash_func(map->buckets[i][j].key) % size;
            new_buckets[hash] =
                realloc(new_buckets[hash], ++(new_lengths[hash]));
            new_buckets[hash][new_lengths[hash] - 1] = map->buckets[i][j];
        }

        free(map->buckets[i]);
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->bucket_lengths = new_lengths;
    map->bucket_count = size;
}

/** STRING HASHMAP END **/