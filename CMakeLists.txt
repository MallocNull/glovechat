cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_STANDARD 99)
project(glovechat C)

file(GLOB_RECURSE glv_src
    "src/*.h"
    "src/*.c"
)

find_package(OpenSSL)

add_executable(server ${glv_src})
target_include_directories(server
    PRIVATE ${OPENSSL_INCLUDE_DIR}
    PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(server ${OPENSSL_LIBRARIES})
install(TARGETS server RUNTIME DESTINATION bin/server)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(server wsock32 ws2_32)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(server pthread nsl resolv)
else()
    target_link_libraries(server pthread socket nsl resolv)
endif()
