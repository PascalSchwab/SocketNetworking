cmake_minimum_required(VERSION 3.2)
project(SocketNetworking VERSION 0.0.1)

file(GLOB files
    "src/*.h"
    "src/*.c"
    "network.h"
)

add_library(SocketNetworking ${files})
