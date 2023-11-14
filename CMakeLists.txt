cmake_minimum_required(VERSION 3.2)
project(SocketNetworking VERSION 0.0.1)

file(GLOB srcFiles
    "src/*.h"
    "src/*.c"
)

file(GLOB includeFiles
    "include/*.h"
)

add_library(${PROJECT_NAME} SHARED ${srcFiles})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${includeFiles} DESTINATION include/SocketNetworking)
