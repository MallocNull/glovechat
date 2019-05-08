#include "conf.h"

int glv_verify_config
    (const glv_ini_t* config, const char* name,
     const char* const* sections, int section_count,
     const char* const* const* keys, const int* key_counts)
{
    int i, j;

    for(i = 0; i < section_count; ++i) {
        if(!glv_ini_has_section(config, sections[i])) {
            printf(GLV_CRIT
                "%s missing required section '%s'.", name, sections[i]
            );
            return 0;
        }

        for(j = 0; j < key_counts[i]; ++j) {
            if(!glv_ini_section_has_key(config, sections[i], keys[i][j])) {
                printf(GLV_CRIT
                    "%s section '%s' missing required key '%s'.",
                    name, sections[i], keys[i][j]
                );
                return 0;
            }
        }
    }

    return 1;
}

int glv_config_load_global(const char* path) {
    _config.global = glv_ini_read_file(path);
    if(_config.global == NULL) {
        printf(GLV_CRIT "Global config failed to load.");
        return 0;
    }

    char* sections[] = {"SSL"};
    char* ssl[] = {"Certificate", "Private Key"};
    char** keys[] = {ssl};
    int key_counts[] = {sizeof(ssl) / sizeof(ssl[0])};

    if(!glv_verify_config(_config.global, "Global config",
        sections, sizeof(sections) / sizeof(sections[0]), keys, key_counts))
    {
        printf(GLV_CRIT "Global config failed to load.");
        glv_ini_destroy(_config.global);
        return 0;
    }

    return 1;
}

void glv_config_unload(void) {
    glv_ini_destroy(_config.global);
}