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
        ../实验报告杨恒熠+3124009862/RBTree_Hash.cpp
        ../实验报告杨恒熠+3124009862/RBTree_Hash.h
        ../实验报告杨恒熠+3124009862/main.cpp
)
