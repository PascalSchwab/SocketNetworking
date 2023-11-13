cmake_minimum_required(VERSION 3.2)
project(SocketNetworkingC VERSION 0.0.1)

file(GLOB files
    "src/*.h"
    "src/*.c"
)

add_library(SocketNetworkingC ${files})