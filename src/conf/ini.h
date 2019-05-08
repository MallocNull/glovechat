#ifndef GLV_CONF_INI_H
#define GLV_CONF_INI_H

#include <stdio.h>

#include "util/containers.h"
#include "util/etc.h"

#define GLV_INI_INT         0
#define GLV_INI_INT_HEX     1
#define GLV_INI_UINT        2
#define GLV_INI_UINT_HEX    3
#define GLV_INI_DOUBLE      4

#define GLV_INI_MAX_LN  2048

typedef glv_map_t glv_ini_t;

glv_ini_t* glv_ini_read_file(const char* path);

int glv_ini_has_section(const glv_ini_t* ini, const char* section);
int glv_ini_section_has_key
    (const glv_ini_t* ini, const char* section, const char* key);

char* glv_ini_get(const glv_ini_t* ini, const char* section, const char* key);
int glv_ini_get_type
    (const glv_ini_t* ini, const char* section,
     const char* key, int type, void* out);

void glv_ini_destroy(glv_ini_t* ini);

#endif
