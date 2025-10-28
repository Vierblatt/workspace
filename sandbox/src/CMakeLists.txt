cmake_minimum_required(VERSION 3.10)
project(linkqueue_demo C)

set(CMAKE_C_STANDARD 99)

# 链表项目
add_executable(linkqueue_demo
    main.c
    linkqueue.c
)

# 哈希表项目
add_executable(hash_map_chaining_demo
    ../new/main.c
    ../new/hash_map_chaining.c
        ../../myproject/数据结构实验报告/RBTree_Hash.cpp
        ../../myproject/数据结构实验报告/RBTree_Hash.h
        ../../myproject/数据结构实验报告/main.cpp
)
