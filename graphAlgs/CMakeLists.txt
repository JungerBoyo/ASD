add_library(graphAlgs CppGraphBLAS.h Algs.h Algs.cpp)
target_link_libraries(graphAlgs graphblas)