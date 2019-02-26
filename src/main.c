#include <stdio.h>
#include "util/ipaddr.h"
#include "util/containers.h"

int main(int argc, char** argv) {
    glv_map_t* map = glv_map_create();
    glv_map_set_copy(map, "test", "Hello!", 0);
    glv_map_set_copy(map, "amazing", "Hello!!", 0);
    glv_map_set_copy(map, "holy me WOW", "Hello!!", 0);

    return 0;
}