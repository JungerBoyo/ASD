#include "Algs.h"
#include <vector>

#define DEBUG(dbg_vec, type, size) std::vector<uint64_t> dbg_indices(size, 0); \
                                   std::vector<type> dbg_values(size, static_cast<type>(0));\
                                   GrB_Index dbg_size{size};\
                                   GrB_Vector_extractTuples<type>(dbg_indices.data(), dbg_values.data(), &dbg_size, dbg_vec)

GrB_Info GraphAlgs::BFSLevels(GrB_Vector *v, GrB_Matrix A, GrB_Index s)
{
    GrB_Index n;
    GrB_Matrix_nrows(&n, A);

    GrB_Vector_new(v, GrB_INT32, n);

    GrB_Vector q;
    GrB_Vector_new(&q, GrB_BOOL, n);
    GrB_Vector_setElement(q, true, s);

    int32_t d{0};
    bool succ = false;
    do
    {
        ++d;
        GrB_Vector_assign_INT32(*v, q, GrB_NULL, d, GrB_ALL, n, GrB_NULL);
        GrB_vxm(q, *v, GrB_NULL, GrB_LOR_LAND_SEMIRING_BOOL, q, A, GrB_DESC_RC);
        GrB_Vector_reduce_BOOL(&succ, GrB_NULL, GrB_LOR_MONOID_BOOL, q, GrB_NULL);
    }
    while(succ);

    /*
     *  int32_t level{0};
    GrB_Index nvals;
    do
    {
        ++level;
        GrB_Vector_apply_BinaryOp2nd_INT32(*v, GrB_NULL, GrB_PLUS_INT32, GrB_SECOND_INT32, q, level, GrB_NULL);
        GrB_vxm(q, *v, GrB_NULL, GrB_LOR_LAND_SEMIRING_BOOL, q, A, GrB_DESC_RC);
        GrB_Vector_nvals(&nvals, q);
    }
    while(nvals);
     *
     */

    GrB_Vector_free(&q);

    return GrB_SUCCESS;
}


GrB_Info GraphAlgs::BFSParents(GrB_Vector *v, GrB_Matrix A, GrB_Index s)
{
    GrB_Index n;
    GrB_Matrix_nrows(&n, A);

    GrB_Vector_new(v, GrB_UINT64, n);
    GrB_Vector_setElement(*v, s, s);

    GrB_Vector wavefront;
    GrB_Vector_new(&wavefront, GrB_UINT64, n);
    GrB_Vector_setElement(wavefront, s, s);

    GrB_Index nvals;
    GrB_Vector_nvals(&nvals, *v);

    while(nvals < n)
    {
        GrB_vxm(wavefront, *v, GrB_NULL, GrB_MIN_FIRST_SEMIRING_UINT64, wavefront, A, GrB_DESC_RSC);
        GrB_Vector_apply(*v, GrB_NULL, GrB_PLUS_UINT64, GrB_IDENTITY_UINT64, wavefront, GrB_NULL);
        GrB_Vector_apply_IndexOp_UINT64(wavefront, GrB_NULL, GrB_NULL, GrB_ROWINDEX_INT64, wavefront, 0UL, GrB_NULL);
        GrB_Vector_nvals(&nvals, *v);
    }

    GrB_Vector_free(&wavefront);

    return GrB_SUCCESS;
}

GrB_Info GraphAlgs::GroupingBFS(GrB_Vector *v, GrB_Matrix A, GrB_Index s, uint32_t grpID)
{
    GrB_Index n;
    GrB_Matrix_nrows(&n, A);

    GrB_Vector_setElement(*v, grpID, s);

    GrB_Vector mask;
    GrB_Vector_new(&mask, GrB_BOOL, n);
    GrB_Vector_setElement(mask, true, s);

    GrB_Index nvals;
    GrB_Vector_nvals(&nvals, mask);

    while(true)
    {
        GrB_vxm(mask, *v, GrB_NULL, GrB_MIN_FIRST_SEMIRING_UINT64, mask, A, GrB_DESC_RC);
        GrB_Vector_nvals(&nvals, mask);

        if(!nvals)
            break;

        GrB_Vector_assign_UINT32(*v, mask, GrB_NULL, grpID, GrB_ALL, n, GrB_NULL);
    }

    GrB_Vector_free(&mask);

    return GrB_SUCCESS;
}

GrB_Info GraphAlgs::GroupGraph(GrB_Vector *grps, GrB_Matrix A)
{
    GrB_Index n;
    GrB_Matrix_nrows(&n, A);

    uint32_t groupId{1};
    GrB_Index src{0};

    GrB_Vector grpsIndices;
    GrB_Vector_new(&grpsIndices, GrB_UINT64, n);

    GrB_Index nvals;
    while(true)
    {
        GroupingBFS(grps, A, src, groupId);

        GrB_Vector_nvals(&nvals, *grps);
        if(nvals == n)
            break;

        GrB_Vector_assign_UINT64(grpsIndices, *grps, GrB_NULL, 0, GrB_ALL, n, GrB_DESC_RSC);
        GrB_Vector_apply_IndexOp_UINT64(grpsIndices, GrB_NULL, GrB_NULL, GrB_ROWINDEX_INT64, grpsIndices, 0UL, GrB_DESC_R);
        GrB_Vector_reduce_UINT64(&src, GrB_NULL, GrB_MIN_MONOID_UINT64, grpsIndices, GrB_NULL);

        ++groupId;
    }

    return GrB_SUCCESS;
}

GrB_Vector GraphAlgs::TopoSort(GrB_Matrix A)
{
    GrB_Index n;
    GrB_Matrix_nrows(&n, A);

    GrB_Vector sortedIndices;
    GrB_Vector_new(&sortedIndices, GrB_UINT64, n);

    GrB_Vector helperMask;
    GrB_Vector_new(&helperMask, GrB_BOOL, n);

    GrB_Vector dependencies;
    GrB_Vector_new(&dependencies, GrB_UINT32, n);

    GrB_Matrix_reduce_Monoid(dependencies, GrB_NULL, GrB_NULL, GrB_PLUS_MONOID_UINT32, A, GrB_DESC_T0);
    GrB_Vector_assign_UINT32(dependencies, dependencies, GrB_NULL, 0, GrB_ALL, n, GrB_DESC_SC);

    GrB_Semiring GrB_PLUS_SECOND_SEMIRING_UINT32;
    GrB_Semiring_new(&GrB_PLUS_SECOND_SEMIRING_UINT32, GrB_PLUS_MONOID_UINT32, GrB_SECOND_UINT32);

    GrB_Index begin, end{0};
    while(true)
    {
        GrB_Vector_assign_BOOL(helperMask, dependencies, GrB_LXOR, true, GrB_ALL, n, GrB_DESC_RC);

        begin = end;
        GrB_Vector_nvals(&end, helperMask);

        GrB_Index range{0};
        range |= begin;
        range |= (end << 31);

        GrB_Vector_assign_UINT64(sortedIndices, dependencies, GrB_NULL, range, GrB_ALL, n, GrB_DESC_C);

        if(end == n)
            break;

        GrB_vxm(dependencies, GrB_NULL, GrB_MINUS_UINT32, GrB_PLUS_TIMES_SEMIRING_UINT32, helperMask, A, GrB_NULL);

        GrB_Vector_assign_BOOL(helperMask, helperMask, GrB_NULL, true, GrB_ALL, n, GrB_DESC_S);
    }

    return sortedIndices;
}



