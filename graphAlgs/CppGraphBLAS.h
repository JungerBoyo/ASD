#ifndef ASD_PS_CPPGRAPHBLAS_H
#define ASD_PS_CPPGRAPHBLAS_H

extern "C"
{
    #include <GraphBLAS.h>
}

template<typename T>
requires std::is_arithmetic_v<T> || std::is_void_v<T>
GrB_Info GrB_Vector_setElement(GrB_Vector w, T x, GrB_Index i)
{
    if constexpr(std::is_same_v<T, bool>)
        return GrB_Vector_setElement_BOOL(w, x, i);
    else if constexpr(std::is_same_v<T, int8_t>)
        return GrB_Vector_setElement_INT8(w, x, i);
    else if constexpr(std::is_same_v<T, int16_t>)
        return GrB_Vector_setElement_INT16(w, x, i);
    else if constexpr(std::is_same_v<T, int32_t>)
        return GrB_Vector_setElement_INT32(w, x, i);
    else if constexpr(std::is_same_v<T, int64_t>)
        return GrB_Vector_setElement_INT64(w, x, i);
    else if constexpr(std::is_same_v<T, uint8_t>)
        return GrB_Vector_setElement_UINT8(w, x, i);
    else if constexpr(std::is_same_v<T, uint16_t>)
        return GrB_Vector_setElement_UINT16(w, x, i);
    else if constexpr(std::is_same_v<T, uint32_t>)
        return GrB_Vector_setElement_UINT32(w, x, i);
    else if constexpr(std::is_same_v<T, uint64_t>)
        return GrB_Vector_setElement_UINT64(w, x, i);
    else if constexpr(std::is_same_v<T, float>)
        return GrB_Vector_setElement_FP32(w, x, i);
    else if constexpr(std::is_same_v<T, double>)
        return GrB_Vector_setElement_FP64(w, x, i);
}

template<typename T>
//requires std::is_arithmetic_v<T> || std::is_void_v<T>
GrB_Info GrB_Vector_extractTuples(GrB_Index *I, T *X, GrB_Index *nvals, const GrB_Vector v)
{
    if constexpr(std::is_same_v<T, bool>)
        return GrB_Vector_extractTuples_BOOL(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, int8_t>)
        return GrB_Vector_extractTuples_INT8(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, int16_t>)
        return GrB_Vector_extractTuples_INT16(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, int32_t>)
        return GrB_Vector_extractTuples_INT32(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, int64_t>)
        return GrB_Vector_extractTuples_INT64(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, uint8_t>)
        return GrB_Vector_extractTuples_UINT8(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, uint16_t>)
        return GrB_Vector_extractTuples_UINT16(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, uint32_t>)
        return GrB_Vector_extractTuples_UINT32(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, uint64_t>)
        return GrB_Vector_extractTuples_UINT64(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, float>)
        return GrB_Vector_extractTuples_FP32(I, X, nvals, v);
    else if constexpr(std::is_same_v<T, double>)
        return GrB_Vector_extractTuples_FP64(I, X, nvals, v);
    else
        return GrB_Vector_extractTuples_UDT(I, X, nvals, v);
}

#endif