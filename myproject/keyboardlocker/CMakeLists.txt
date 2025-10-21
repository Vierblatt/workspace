cmake_minimum_required(VERSION 4.0)
project(keyboardlocker)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(keyboardlocker WIN32
    src/keyboardlocker.cpp
    src/hookfunctions.cpp
    src/utilityfunctions.cpp
)

target_link_libraries(keyboardlocker user32 shell32)