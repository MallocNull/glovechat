#include "conf.h"

int glv_config_load_global(const char* path) {
    _config.global = glv_ini_read_file(path);
    if(_config.global == NULL) {
        printf(GLV_CRIT "Global configuration failed to load.");
        return 0;
    }



    return 1;
}

void glv_config_unload(void) {
    glv_ini_destroy(_config.global);
}