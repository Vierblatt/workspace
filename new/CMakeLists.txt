cmake_minimum_required(VERSION 3.4.1)
project(demo)
add_executable(demo demo.cpp) # 生成可执行文件
add_library(common STATIC util.cpp) # 生成静态库
add_library(common SHARED util.cpp) # 生成动态库或共享库
add_library(demo demo.cpp test.cpp util.cpp)
aux_source_directory(. SRC_LIST) # 搜索当前目录下的所有.cpp文件
add_library(demo ${SRC_LIST})
file(GLOB SRC_LIST "*.cpp" "protocol/*.cpp")
add_library(demo ${SRC_LIST})
# 或者
file(GLOB SRC_LIST "*.cpp")
file(GLOB SRC_PROTOCOL_LIST "protocol/*.cpp")
add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
# 或者
aux_source_directory(. SRC_LIST)
aux_source_directory(protocol SRC_PROTOCOL_LIST)
add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
)
target_link_libraries(demo libface.a) # 链接libface.a
target_link_libraries(demo libface.so) # 链接libface.so
target_link_libraries(demo ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a)
target_link_libraries(demo ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.so)
target_link_libraries(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a
        boost_system.a
        boost_thread
        pthread)

set(SRC_LIST main.cpp test.cpp)
add_executable(demo ${SRC_LIST})
set(SRC_LIST main.cpp)
set(SRC_LIST ${SRC_LIST} test.cpp
        tmp.cpp
        tmp.cpp
        tmp.cpp
        tmp.cpp
        U1.cpp
        U1.cpp)
add_executable(demo ${SRC_LIST})