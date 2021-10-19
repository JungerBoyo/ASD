cmake_minimum_required(VERSION 3.20)
project(ASD_PS)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(ASD_PS main.cpp)

add_subdirectory(Timer)
add_subdirectory(_1)

target_link_libraries(${PROJECT_NAME} fmt Timer Zadania)