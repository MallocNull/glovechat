#include <stdio.h>
#include "conf/conf.h"

int main(int argc, char** argv) {
    printf("Starting Glove Chat server...");

    if(!glv_config_load_global("config.ini"))
        return -1;

    glv_config_unload();
    return 0;
}