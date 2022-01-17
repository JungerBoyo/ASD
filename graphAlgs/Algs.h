#ifndef ASD_PS_ALGS_H
#define ASD_PS_ALGS_H

#include "CppGraphBLAS.h"
#include <tuple>

namespace GraphAlgs
{
    GrB_Info BFSParents(GrB_Vector *v, GrB_Matrix A, GrB_Index s);
    GrB_Info BFSLevels(GrB_Vector *v, GrB_Matrix A, GrB_Index s);
    GrB_Info GroupingBFS(GrB_Vector *v, GrB_Matrix A, GrB_Index s, uint32_t grpID);
    GrB_Info GroupGraph(GrB_Vector *grps, GrB_Matrix A);
    GrB_Vector TopoSort(GrB_Matrix A);
}


#endif