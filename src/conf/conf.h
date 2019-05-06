#ifndef GLV_CONF_CONF_H
#define GLV_CONF_CONF_H

#include "conf/ini.h"

struct {
    glv_ini_t* global;
} _config;

int glv_config_load_global(const char* path);

void glv_config_unload(void);

#endif
