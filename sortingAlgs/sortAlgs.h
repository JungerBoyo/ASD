#ifndef ASD_PS_SORTALGS_H
#define ASD_PS_SORTALGS_H

#include <utility>

namespace SortAlgs
{
    namespace detail
    {
        template<typename T, typename U>
        concept SameHelper = std::is_same_v<T, U>;
    }

    template<typename T, typename U>
    concept same_as = detail::SameHelper<T, U> && detail::SameHelper<U, T>;

    template<typename T>
    concept unsigned_integer = std::is_unsigned_v<T>;

    template<typename T>
    concept has_operatorLE = requires(const T& lhs, const T& rhs)
    {
        { operator<(lhs, rhs) } -> same_as<bool>;
    };

    template<typename T>
    concept has_operatorHI = requires(const T& lhs, const T& rhs)
    {
        { operator>(lhs, rhs) } -> same_as<bool>;
    };

    template<template <typename...> typename ContainerType, typename T, unsigned_integer size_type = size_t>
    concept is_indexable = requires(ContainerType<T>& container, size_type index)
    {
        { container.operator[] (index) } noexcept -> same_as<T>;
    };

    template<template <typename...> typename ContainerType, typename T>
    concept has_size = requires(const ContainerType<T> container)
    {
        { container.size() } -> unsigned_integer;
    };

    template<typename T>
    concept is_swappable = requires
    {
        (std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>) ||
        (std::is_move_constructible_v<T> && std::is_move_assignable_v<T>);
    };


    namespace utils {

        template<typename T>
        void swap(T& lhs, T& rhs)
        {
            if constexpr(std::is_move_assignable_v<T> && std::is_move_constructible_v<T> && !std::is_trivial_v<T>)
            {
                auto&& tmp = std::move(rhs);
                rhs = std::move(lhs);
                lhs = std::move(tmp);
            }
            else
            {
                auto tmp = rhs;
                rhs = lhs;
                lhs = tmp;
            }
        }
    }


    template<template <typename...> typename ContainerType, typename T>
    requires (std::is_arithmetic_v<T> || has_operatorHI<T> || has_operatorLE<T>) &&
              is_indexable<ContainerType, T>                 &&
              has_size<ContainerType, T>                     &&
              std::is_copy_constructible_v<ContainerType<T>>

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



}

#include "sortAlgsImpl.tpp"
#endif