#include "ini.h"

glv_ini_t* glv_ini_read_file(const char* path) {
    char *split, line[GLV_INI_MAX_LN + 1];
    glv_map_t* section = NULL;
    glv_ini_t* ini = NULL;
    FILE* file;
    int length;

    if((file = fopen(path, "r")) == NULL) {
        printf(GLV_ERR "INI file '%s' was not found or not readable.", path);
        return NULL;
    }

    ini = glv_map_create();
    while(fgets(line, sizeof(line), file) != NULL) {
        trim(line);
        if(line[0] == '\0' || line[0] == ';')
            continue;

        length = strlen(line);
        if(length == GLV_INI_MAX_LN && !feof(file))
        {
            printf(GLV_ERR
                "INI file '%s' has line that exceeds %i bytes.",
                path, GLV_INI_MAX_LN
            );

            glv_ini_destroy(ini);
            fclose(file);
            return NULL;
        }

        if(line[0] == '[') {
            if(line[length - 1] == ']') {
                line[length - 1] = '\0';
                strlower(trim(line + 1));

                if(!glv_map_has_key(ini, line + 1)) {
                    section = glv_map_create();
                    glv_map_set_copy(ini, line + 1, section, sizeof(glv_ini_t));
                }
            } else {
                printf(GLV_ERR
                    "INI file '%s' contains malformed section header.", path
                );

                glv_ini_destroy(ini);
                fclose(file);
                return NULL;
            }
        } else {
            split = strchr(line, '=');
            if(section != NULL && split != NULL) {
                *split = '\0';
                trim(split + 1);
                strlower(trim(line));

                if(glv_map_has_key(ini, line)) {
                    printf(GLV_WARN
                        "INI file '%s' redefines key '%s' in same section.",
                        path, line
                    );
                }

                glv_map_setf_copy(section, line, split + 1, GLV_STRLEN);
            } else {
                printf(GLV_ERR
                    "INI file '%s' contains malformed assignment.", path
                );

                glv_ini_destroy(ini);
                fclose(file);
                return NULL;
            }
        }
    }

    return ini;
}

int glv_ini_has_section(glv_ini_t* ini, const char* section) {
    char* section_lc = strlower(strdup(section));
    int check = glv_map_has_key(ini, section_lc);

    free(section_lc);
    return check;
}

int glv_ini_section_has_key
    (glv_ini_t* ini, const char* section, const char* key)
{
    char *section_lc = strlower(strdup(section)),
         *key_lc = strlower(strdup(key));
    glv_map_t* section_map;
    int check = 0;

    section_map = glv_map_get(ini, section_lc);
    if(section_map != NULL)
        check = glv_map_has_key(section_map, key_lc);

    free(section_lc);
    free(key_lc);
    return check;
}

char* glv_ini_get(glv_ini_t* ini, const char* section, const char* key) {
    char *section_lc = strlower(strdup(section)),
         *key_lc = strlower(strdup(key)),
         *value = NULL;
    glv_map_t* section_map;

    section_map = glv_map_get(ini, section_lc);
    if(section_map != NULL)
        value = glv_map_get(section_map, key_lc);

    free(section_lc);
    free(key_lc);
    return value;
}

int glv_ini_get_type
    (glv_ini_t* ini, const char* section, const char* key, int type, void* out)
{
    char *value = glv_ini_get(ini, section, key);
    if(value == NULL)
        return 0;

    switch(type) {
        case GLV_INI_INT:
        case GLV_INI_INT_HEX:
            *(int*)out = (int)
                strtol(value, NULL, (type == GLV_INI_INT ? 10 : 16));
            break;
        case GLV_INI_UINT:
        case GLV_INI_UINT_HEX:
            *(unsigned int*)out = (unsigned int)
                strtoul(value, NULL, (type == GLV_INI_UINT ? 10 : 16));
            break;
        case GLV_INI_DOUBLE:
            *(double*)out = strtod(value, NULL);
            break;
    }
}

void glv_ini_destroy(glv_ini_t* ini) {
    if(ini == NULL)
        return;

    glv_map_destroyf_func(ini, glv_map_destroyf);
}