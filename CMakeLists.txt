cmake_minimum_required(VERSION 3.20)
project(ASD_PS)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(ASD_PS main.cpp cwiczenia/zad.h cwiczenia/zad.cpp)

add_subdirectory(Timer)
add_subdirectory(_1)
add_subdirectory(cwiczenia)

target_link_libraries(${PROJECT_NAME} fmt Timer Zadania zadaniaCwiczenia)