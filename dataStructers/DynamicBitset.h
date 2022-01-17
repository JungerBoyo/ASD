#ifndef ASD_PS_DYNAMICBITSET_H
#define ASD_PS_DYNAMICBITSET_H

#include <vector>
#include <cinttypes>

namespace DSTRS
{
    struct DynamicBitset
    {
        DynamicBitset() = default;

        DynamicBitset(std::size_t bitsCount, bool bitsState)
                : _bits((bitsCount >> 5) + static_cast<uint32_t>((bitsCount & 31) != 0), bitsState ? UINT32_MAX : 0)
        {}

        void set(std::size_t index)
        {
            _bits[index >> 5] |= (setMask >> (index & 31));
        }

        void reset(std::size_t index)
        {
            _bits[index >> 5] &= ~(setMask >> (index & 31));
        }

        bool operator[](std::size_t index) const
        {
            return _bits[index >> 5] & (setMask >> (index & 31));
        }

        private:
            static constexpr uint32_t setMask   = 1 << 31;
            std::vector<uint32_t> _bits;
    };
}

#endif
