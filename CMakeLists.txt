cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_STANDARD 99)
project(glovechat C)

file(GLOB_RECURSE server_src
    "src/server/*.h"
    "src/server/*.c"
)

find_package(OpenSSL)

add_executable(server ${server_src})
target_include_directories(server
    PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(server ${OPENSSL_LIBRARIES})
install(TARGETS server RUNTIME DESTINATION bin/server)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(server wsock32 ws2_32)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(server dl pthread nsl resolv)
else()
    target_link_libraries(server dl pthread socket nsl resolv)
endif()
