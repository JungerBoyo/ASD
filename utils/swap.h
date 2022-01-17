#ifndef ASD_PS_SWAP_H
#define ASD_PS_SWAP_H

#include <memory>

namespace utils
{
    template<typename T>
    void swap(T& lhs, T& rhs)
    {
        auto &&tmp = std::move(rhs);
        rhs = std::move(lhs);
        lhs = std::move(tmp);
    }
}

#endif