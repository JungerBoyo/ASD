#ifndef ASD_PS_SWAP_H
#define ASD_PS_SWAP_H

namespace utils
{
    template<typename T>
    void swap(T& lhs, T& rhs)
    {
        if constexpr(std::is_move_assignable_v<T> && std::is_move_constructible_v<T> &&
                    !std::is_trivially_copy_assignable_v<T> && !std::is_trivially_copy_constructible_v<T>)
        {
            auto &&tmp = std::move(rhs);
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

#endif