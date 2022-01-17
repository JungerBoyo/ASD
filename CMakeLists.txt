cmake_minimum_required(VERSION 3.20)
project(ASD_PS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS -fconcepts)

include_directories("utils/" "dataStructers/")

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(utils)
add_subdirectory(sortingAlgs)
add_subdirectory(dataStructers)
add_subdirectory(Timer)
add_subdirectory(_5)

target_link_libraries(${PROJECT_NAME} Zadania fmt Timer utils sortAlgs)