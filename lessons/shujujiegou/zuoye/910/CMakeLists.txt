cmake_minimum_required(VERSION 3.10)
project(SeqStackDemo)

set(CMAKE_CXX_STANDARD 14)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 设置不同配置的输出目录（对于多配置生成器，如Visual Studio）
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach()

# 添加编译选项以解决编码问题
if(MSVC)
    add_compile_options(/W3 /utf-8)
else()
    add_compile_options(-Wall -Wextra -std=c++14)
endif()

add_executable(SeqStackDemo 
    main.cpp 
    SeqStack.cpp 
    SeqStack.h
)

# 设置包含目录
target_include_directories(SeqStackDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 如果在Windows上，链接必要的库
if(WIN32)
    target_link_libraries(SeqStackDemo)
endif()