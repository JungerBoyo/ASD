#ifndef ASD_PS_SORTALGS_H
#define ASD_PS_SORTALGS_H

#include "concepts.h"
#include "swap.h"

using namespace utils;

namespace SortAlgs
{

    template<template <typename...> typename ContainerType, typename T>
    requires (std::is_arithmetic_v<T> || has_operatorHI<T> || has_operatorLE<T>) &&
              is_indexable<ContainerType, T>                 &&
              has_size<ContainerType, T>                     &&
              std::is_copy_constructible_v<ContainerType<T>> &&
             (std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>)

    void MergeSort(ContainerType<T>& values, size_t beginIndex = 0, size_t endIndex = 0);


    template<template <typename...> typename ContainerType, typename T>
    requires (std::is_arithmetic_v<T> || (has_operatorHI<T> && has_operatorLE<T>)) &&
              is_indexable<ContainerType, T>             &&
              has_size<ContainerType, T>                 &&
              is_swappable<T>

    void QuickSort(ContainerType<T>& values, size_t beginIndex = 0, size_t endIndex = 0);


    template<template <typename...> typename ContainerType, typename T>
    requires (std::is_arithmetic_v<T> || has_operatorHI<T> || has_operatorLE<T>) &&
              is_indexable<ContainerType, T>             &&
              has_size<ContainerType, T>                 &&
              is_swappable<T>

    void InsertionSort(ContainerType<T>& values, size_t beginIndex = 0, size_t endIndex = 0);


    template<template <typename ...> typename ContainerType, typename T>
    requires std::is_integral_v<T> && is_indexable<ContainerType, T> && has_size<ContainerType, T>
    void CountingSort(ContainerType<T>& values, T min, T max, size_t beginIndex = 0, size_t endIndex = 0);


    template<template <typename ...> typename ContainerType, typename T>
    requires is_ordinalable<T> && is_indexable<ContainerType, T> && has_size<ContainerType, T> &&
             std::is_copy_constructible_v<ContainerType<T>> &&
            (std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>)

    void CountingSort(ContainerType<T>& values, int64_t min, int64_t max, size_t beginIndex = 0, size_t endIndex = 0,
                      size_t RSvalue = 0, size_t mask = UINT64_MAX);


    template<template <typename ...> typename ContainerType, typename T>
    requires is_ordinalable<T> && is_indexable<ContainerType, T> && has_size<ContainerType, T> &&
             std::is_copy_constructible_v<ContainerType<T>> &&
            (std::is_copy_assignable_v<T> || std::is_move_assignable_v<T>)

    void RadixSort(ContainerType<T>& values, size_t beginIndex = 0, size_t endIndex = 0);
}

#include "sortAlgsImpl.tpp"
#endif