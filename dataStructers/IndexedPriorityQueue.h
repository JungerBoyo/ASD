#ifndef ASD_PS_INDEXEDPRIORITYQUEUE_H
#define ASD_PS_INDEXEDPRIORITYQUEUE_H

#include <vector>
#include <tuple>
#include <iostream>
#include <concepts.h>

namespace DSTRS
{
    template<typename KeyType, KeyType InvalidKey, typename T, T InvalidValue>
    requires std::is_unsigned_v<KeyType> && std::is_unsigned_v<T>
    class IndexedPriorityQueue_BH
    {
        public:
            explicit IndexedPriorityQueue_BH(size_t maxValuesCount)
                : _keyToHeapIndex(maxValuesCount, InvalidKey) {}

            void push(KeyType key, T value)
            {
                KeyType index = _heap.size();
                _heap.push_back({key, value});
                _keyToHeapIndex[_heap.back().first] = index;

                while(index && _heap[index].second < _heap[(index >> 1) - (1 - (index & 1))].second)
                {
                    auto newIndex = (index >> 1) - (1 - (index & 1));
                    _keyToHeapIndex[_heap[index].first] = newIndex;
                    _keyToHeapIndex[_heap[newIndex].first] = index;

                    auto tmpValue = _heap[index];
                    _heap[index] = _heap[newIndex];
                    _heap[newIndex] = tmpValue;

                    index = newIndex;
                }
            }

            auto pop()
            {
                auto minValue = _heap.front();
                _heap.front() = _heap.back();
                _heap.pop_back();
                _keyToHeapIndex[_heap.front().first] = 0;
                _keyToHeapIndex[minValue.first] = InvalidKey;

                KeyType index{0};
                while((index << 1) + 1 < _heap.size())
                {
                    auto lhs = _heap[(index << 1) + 1].second;
                    auto rhs = (index << 1) + 2 < _heap.size() ? _heap[(index << 1) + 2].second : InvalidValue;

                    KeyType newIndex = lhs < rhs ? (index << 1) + 1 : (index << 1) + 2;

                    if(_heap[index].second <= _heap[newIndex].second)
                        break;

                    _keyToHeapIndex[_heap[index].first] = newIndex;
                    _keyToHeapIndex[_heap[newIndex].first] = index;

                    auto tmpValue = _heap[index];
                    _heap[index] = _heap[newIndex];
                    _heap[newIndex] = tmpValue;

                    index = newIndex;
                }

                return minValue;
            }

            auto empty() const
            {
                return _heap.empty();
            }

            auto contains(KeyType key) const
            {
                return _keyToHeapIndex[key] != InvalidKey;
            }

            void decrease(KeyType key, T value)
            {
                KeyType index = _keyToHeapIndex[key];
                _heap[_keyToHeapIndex[key]].second = value;

                while(index && _heap[index].second < _heap[(index >> 1) - (1 - (index & 1))].second)
                {
                    auto newIndex = (index >> 1) - (1 - (index & 1));
                    _keyToHeapIndex[_heap[index].first] = newIndex;
                    _keyToHeapIndex[_heap[newIndex].first] = index;

                    auto tmpValue = _heap[index];
                    _heap[index] = _heap[newIndex];
                    _heap[newIndex] = tmpValue;

                    index = newIndex;
                }
            }

        private:
            std::vector<KeyType> _keyToHeapIndex;
            std::vector<std::pair<KeyType, T>> _heap;
    };
}

#endif