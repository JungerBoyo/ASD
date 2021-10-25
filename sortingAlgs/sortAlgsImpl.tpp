#ifndef ASD_PS_SORTALGSIMPL_TPP
#define ASD_PS_SORTALGSIMPL_TPP

#include <functional>
#include <random>
#include "sortAlgs.h"

namespace SortAlgs
{
    template<template <typename...> typename ContainerType, typename T>
    requires (std::is_arithmetic_v<T> || has_operatorHI<T> || has_operatorLE<T>) &&
              is_indexable<ContainerType, T>                    &&
              has_size<ContainerType, T>                        &&
              std::is_copy_constructible_v<ContainerType<T>>

    void MergeSort(ContainerType<T>& values, size_t beginIndex, size_t endIndex)
    {
        ContainerType<T> helperContainer(values);

        const static auto merge = [&values, &helperContainer](size_t begin, size_t center, size_t end){

            size_t tmpCenter = center;
            size_t helperBegin = begin;
            size_t remBegin = begin;

            while(begin < center && tmpCenter < end)
            {
                if constexpr(has_operatorHI<T>)
                {
                    if(values[begin] > values[tmpCenter])
                        helperContainer[helperBegin++] = values[tmpCenter++];
                    else
                        helperContainer[helperBegin++] = values[begin++];
                }
                else
                {
                    if(values[begin] < values[tmpCenter])
                        helperContainer[helperBegin++] = values[begin++];
                    else
                        helperContainer[helperBegin++] =  values[tmpCenter++];
                }
            }

            if(begin == center)
            {
                begin = tmpCenter;
                center = end;
            }

            while(begin < center)
                helperContainer[helperBegin++] = values[begin++];

            for(;remBegin < end; ++remBegin)
                values[remBegin] = helperContainer[remBegin];
        };

        static const std::function<void(size_t, size_t)> divide = [&values](size_t begin, size_t end){

            if(begin < end)
            {
                size_t center = (begin + end)/2;
                divide(begin, center);
                divide(center, end);
                merge(begin, center, end);
            }
        };

        if(beginIndex == endIndex)
            divide(0, values.size());
        else
            divide(beginIndex, endIndex);
    }


    template<template <typename...> typename ContainerType, typename T>
    requires (std::is_arithmetic_v<T> || (has_operatorHI<T> && has_operatorLE<T>)) &&
            is_indexable<ContainerType, T>       &&
            has_size<ContainerType, T>           &&
            is_swappable<T>

    void QuickSort(ContainerType<T>& values, size_t beginIndex, size_t endIndex)
    {
        if(beginIndex == endIndex)
        {
            beginIndex = 0;
            endIndex = values.size() - 1;
        }

        std::mt19937_64 generator((std::random_device()()));
        std::uniform_int_distribution<uint64_t> distribute(beginIndex, endIndex-1);

        const static auto sort = [&values](uint64_t begin, uint64_t end, const T& pivot) -> size_t {

            while(true)
            {
                while(values[begin] < pivot) begin++;
                while(end != UINT64_MAX && values[end] > pivot) end--;

                if(begin >= end)
                    return end;

                utils::swap(values[begin], values[end]);
                --end;
                ++begin;
            }
        };

        static const std::function<void(uint64_t, uint64_t)> quick = [&distribute, &generator, &values](uint64_t begin, uint64_t end){

            if(begin < end)
            {
                auto center = sort(begin, end, values[ begin + distribute(generator) % ((end-begin)/2 + 1) ]);
                quick(begin, center);
                quick(center+1, end);
            }
        };

        quick(beginIndex, endIndex);
    }


    template<template <typename...> typename ContainerType, typename T>
    requires (std::is_arithmetic_v<T> || has_operatorHI <T> || has_operatorLE <T> ) &&
              is_indexable<ContainerType, T>    &&
              has_size<ContainerType, T>        &&
              is_swappable<T>

    void InsertionSort(ContainerType<T> &values, size_t beginIndex, size_t endIndex)
    {
        if(beginIndex == endIndex)
        {
            beginIndex = 0;
            endIndex = values.size();
        }

        for(size_t i{beginIndex}; i<endIndex; ++i)
        {
            size_t j = i;
            while(j>beginIndex && values[j] < values[j - 1])
            {
                utils::swap(values[j], values[j-1]);
                --j;
            }
        }
    }
}



#endif