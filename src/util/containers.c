#include "containers.h"

/** STRING HASHMAP START **/

#define GLV_MAP_DEFAULT_BUCKETS 8

static uint32_t glv_map_hash_func(const char* key) {
    uint32_t hash = 7;
    size_t length = strlen(key), i;

    for(i = 0; i < length; ++i)
        hash = hash * 31 + key[i];
    return hash;
}

glv_map_t* glv_map_create(void) {
    return glv_map_create_ex(GLV_MAP_DEFAULT_BUCKETS);
}

glv_map_t* glv_map_create_ex(int initial_size) {
    glv_map_t* map = malloc(sizeof(glv_map_t));
    map->buckets = NULL;
    map->bucket_lengths = NULL;
    map->pair_count = 0;

    glv_map_resize(map, initial_size);
    return map;
}

void* glv_map_get(const glv_map_t* map, const char* key) {
    uint32_t hash = glv_map_hash_func(key) % map->bucket_count, i;

    for(i = 0; i < map->bucket_lengths[hash]; ++i)
        if(map->buckets[hash][i].key != NULL &&
           strcmp(map->buckets[hash][i].key, key) == 0)
            return map->buckets[hash][i].value;

    return NULL;
}

void* glv_map_set(glv_map_t* map, const char* key, void* value) {
    if(value == NULL)
        return NULL;

    uint32_t hash = glv_map_hash_func(key), i;
    glv_pair_t* pair = NULL;
    void* tmp;

    if(glv_map_has_key(map, key)) {
        hash = hash % map->bucket_count;
        for(i = 0; i < map->bucket_lengths[hash]; ++i) {
            if(map->buckets[hash][i].key != NULL &&
               strcmp(map->buckets[hash][i].key, key) == 0)
            {
                tmp = map->buckets[hash][i].value;
                map->buckets[hash][i].value = value;
                return tmp;
            }
        }
    } else {
        if(map->pair_count + 1 > map->bucket_count * 2)
            glv_map_resize(map, map->bucket_count * 2);

        hash = hash % map->bucket_count;
        for(i = 0; i < map->bucket_lengths[hash]; ++i) {
            if(map->buckets[hash][i].key == NULL) {
                pair = &(map->buckets[hash][i]);
                break;
            }
        }

        if(pair == NULL) {
            map->buckets[hash] =
                realloc(map->buckets[hash], ++(map->bucket_lengths[hash]));
            pair = &(map->buckets[hash][map->bucket_lengths[hash] - 1]);
        }

        pair->key = strdup(key);
        pair->value = value;
        ++(map->pair_count);
    }

    return NULL;
}

void* glv_map_set_copy
    (glv_map_t* map, const char* key, void* value, size_t length)
{

    length = (length == 0 ? strlen(value) + 1 : length);
    void* copy = malloc(length);
    memcpy(copy, value, length);

    return glv_map_set(map, key, copy);
}

void glv_map_setf(glv_map_t* map, const char* key, void* value) {
    free(glv_map_set(map, key, value));
}

void glv_map_setf_copy
    (glv_map_t* map, const char* key, void* value, size_t length)
{
    free(glv_map_set_copy(map, key, value, length));
}

void* glv_map_remove(glv_map_t* map, const char* key) {
    uint32_t hash = glv_map_hash_func(key) % map->bucket_count, i;
    for(i = 0; i < map->bucket_lengths[hash]; ++i) {
        if(map->buckets[hash][i].key != NULL &&
           strcmp(map->buckets[hash][i].key, key) == 0)
        {
            free(map->buckets[hash][i].key);
            map->buckets[hash][i].key = NULL;
            return map->buckets[hash][i].value;
        }
    }

    return NULL;
}

void glv_map_removef(glv_map_t* map, const char* key) {
    free(glv_map_remove(map, key));
}

int glv_map_has_key(const glv_map_t* map, const char* key) {
    return glv_map_get(map, key) != NULL;
}

void glv_map_resize(glv_map_t* map, int size) {
    glv_pair_t** new_buckets = calloc(size, sizeof(glv_pair_t*));
    int* new_lengths = calloc(size, sizeof(int));
    uint32_t i, j, hash;

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
    free(map->bucket_lengths);

    map->buckets = new_buckets;
    map->bucket_lengths = new_lengths;
    map->bucket_count = size;
}

void glv_map_destroy(glv_map_t* map) {
    glv_map_destroyf_func(map, NULL);
}

void glv_map_destroyf(glv_map_t* map) {
    glv_map_destroyf_func(map, free);
}

void glv_map_destroyf_func(glv_map_t* map, glv_map_dealloc_func func) {
    int i, j;

    if(map == NULL)
        return;

    for(i = 0; i < map->bucket_count; ++i) {
        for(j = 0; j < map->bucket_lengths[i]; ++j) {
            free(map->buckets[i][j].key);
            if(func != NULL)
                func(map->buckets[i][j].value);
        }

        free(map->buckets[i]);
    }

    free(map->buckets);
    free(map->bucket_lengths);
    free(map);
}

/** STRING HASHMAP END **/