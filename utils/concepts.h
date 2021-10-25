#ifndef ASD_PS_CONCEPTS_H
#define ASD_PS_CONCEPTS_H

#include <iostream>

namespace utils
{
    namespace detail
    {
        template<typename T, typename U>
        concept SameHelper = std::is_same_v<T, U>;
    }

    template<typename T, typename U>
    concept same_as = detail::SameHelper<T, U> && detail::SameHelper<U, T>;

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

    template<typename T>
    concept has_ostream = requires(T value)
    {
        { std::cout << value } -> same_as<std::ostream&>;
    };

    template<typename T>
    concept unsigned_integer = std::is_unsigned_v<T>;

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
}


#endif