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
              std::is_copy_constructible_v<ContainerType<T>>    &&
             (std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>)

    void MergeSort(ContainerType<T>& values, size_t beginIndex, size_t endIndex)
    {
        ContainerType<T> auxContainer(values);

        static const auto merge = [&values, &auxContainer](size_t begin, size_t center, size_t end){

            size_t tmpCenter = center;
            size_t helperBegin = begin;
            size_t remBegin = begin;

            while(begin < center && tmpCenter < end)
            {
                if constexpr(has_operatorHI<T>)
                {
                    if constexpr(std::is_move_assignable_v<T> && !std::is_trivially_copy_assignable_v<T>)
                    {
                        if(values[begin] > values[tmpCenter])
                            auxContainer[helperBegin++] = std::move(values[tmpCenter++]);
                        else
                            auxContainer[helperBegin++] = std::move(values[begin++]);
                    }
                    else
                    {
                        if(values[begin] > values[tmpCenter])
                            auxContainer[helperBegin++] = values[tmpCenter++];
                        else
                            auxContainer[helperBegin++] = values[begin++];
                    }
                }
                else
                {
                    if constexpr(std::is_move_assignable_v<T> && !std::is_trivially_copy_assignable_v<T>)
                    {
                        if(values[begin] < values[tmpCenter])
                            auxContainer[helperBegin++] = std::move(values[begin++]);
                        else
                            auxContainer[helperBegin++] = std::move(values[tmpCenter++]);
                    }
                    else
                    {
                        if(values[begin] < values[tmpCenter])
                            auxContainer[helperBegin++] = values[begin++];
                        else
                            auxContainer[helperBegin++] = values[tmpCenter++];
                    }
                }
            }

            if(begin == center)
            {
                begin = tmpCenter;
                center = end;
            }

            if constexpr(std::is_move_assignable_v<T> && !std::is_trivially_copy_assignable_v<T>)
            {
                while (begin < center)
                    auxContainer[helperBegin++] = std::move(values[begin++]);

                for (;remBegin < end; ++remBegin)
                    values[remBegin] = std::move(auxContainer[remBegin]);
            }
            else
            {
                while (begin < center)
                    auxContainer[helperBegin++] = values[begin++];

                for (;remBegin < end; ++remBegin)
                    values[remBegin] = auxContainer[remBegin];
            }
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

    template<template <typename ...> typename ContainerType, typename T>
    requires std::is_integral_v<T> && is_indexable<ContainerType, T> && has_size<ContainerType, T>
    void CountingSort(ContainerType<T>& values, T min, T max, size_t beginIndex, size_t endIndex)
    {
        std::vector<size_t> countsContainer(max - min + 1, 0);

        if(beginIndex == endIndex)
        {
            beginIndex = 0;
            endIndex = values.size();
        }

        for(size_t i{beginIndex}; i<endIndex; ++i)
            ++countsContainer[values[i] - min];

        for(size_t c{0}, i{beginIndex}; c < countsContainer.size(); ++c)
            while(countsContainer[c] != 0)
            {
                values[i++] = c + min;
                --countsContainer[c];
            }
    }

    template<template <typename ...> typename ContainerType, typename T>
    requires is_ordinalable<T> && is_indexable<ContainerType, T> && has_size<ContainerType, T> &&
            std::is_copy_constructible_v<ContainerType<T>> &&
            (std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>)

    void CountingSort(ContainerType<T>& values, int64_t min, int64_t max, size_t beginIndex, size_t endIndex,
                      size_t RSvalue, size_t mask)
    {
        using ordinalType = decltype(values[0].getOrdinalNumber());

        std::vector<ordinalType> countsContainer(max - min + 1, 0);
        std::vector<T> auxContainer(values);

        if(beginIndex == endIndex)
        {
            beginIndex = 0;
            endIndex = values.size();
        }

        for(size_t i{beginIndex}; i<endIndex; ++i)
            ++countsContainer[((values[i].getOrdinalNumber() & mask) >> RSvalue) - min];
        for(size_t c{1}; c < countsContainer.size(); ++c)
            countsContainer[c] += countsContainer[c - 1];

        for(size_t auxi{endIndex - 1}; auxi != beginIndex; --auxi)
            if(countsContainer[((auxContainer[auxi].getOrdinalNumber() & mask) >> RSvalue) - min])
            {
                if constexpr(std::is_move_assignable_v<T> && !std::is_trivially_copy_assignable_v<T>)
                    values[countsContainer[((auxContainer[auxi].getOrdinalNumber() & mask) >> RSvalue) - min] - 1]
                            = std::move(auxContainer[auxi]);
                else
                    values[countsContainer[((auxContainer[auxi].getOrdinalNumber() & mask) >> RSvalue) - min] - 1]
                            = auxContainer[auxi];

                --countsContainer[((auxContainer[auxi].getOrdinalNumber() & mask) >> RSvalue) - min];
            }
    }


    template<template <typename ...> typename ContainerType, typename T>
    requires is_ordinalable<T> && is_indexable<ContainerType, T> && has_size<ContainerType, T> &&
             std::is_copy_constructible_v<ContainerType<T>> &&
            (std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>)

    void RadixSort(ContainerType<T>& values, size_t beginIndex, size_t endIndex)
    {
        using ordinalType = decltype(values[0].getOrdinalNumber());
        constexpr uint8_t numSize = sizeof(ordinalType);

        if constexpr(numSize == 8)
        {
            constexpr size_t twoThirdsMask = 0x000003FFFFFFFFFF;
            constexpr size_t oneThirdMask = 0x00000000001FFFFF;

            CountingSort(values, 0, 2097152/*2^21*/, beginIndex, endIndex,  0, oneThirdMask); /// 22 21 |21|
            CountingSort(values, 0, 2097152/*2^21*/, beginIndex, endIndex, 21, twoThirdsMask); /// 22 |21| 21
            CountingSort(values, 0, 4194304/*2^22*/, beginIndex, endIndex, 42); /// |22| 21 21
        }
        else if constexpr(numSize == 4)
        {
            CountingSort(values, 0, UINT16_MAX, beginIndex, endIndex, 0, UINT16_MAX); /// 16 |16|
            CountingSort(values, 0, UINT16_MAX, beginIndex, endIndex, 16);            ///|16| 16
        }
        else
        {
            CountingSort(values, 0, UINT16_MAX, beginIndex, endIndex);
        }
    }
}



#endif