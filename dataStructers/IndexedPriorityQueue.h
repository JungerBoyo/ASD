#ifndef ASD_PS_PRIORITYQUEUE_H
#define ASD_PS_PRIORITYQUEUE_H

#include <vector>
#include <tuple>
#include <iostream>
#include <concepts.h>

namespace DSTRS
{
    /*
     * KeyTypeMajor = Accumlated wages
     * KeyTypeMinor = vertex
     */
    template<typename KeyTypeMajor, typename KeyTypeMinor>
    requires std::is_unsigned_v<KeyTypeMajor> && std::is_unsigned_v<KeyTypeMinor>
    class PriorityQueue
    {
        public:
            PriorityQueue(size_t KeyTypeMajorCount, size_t KeyTypeMinorCount)
                : _queueValuesIndices(KeyTypeMinorCount), _queue(KeyTypeMajorCount) {}

            void push(KeyTypeMajor key, KeyTypeMinor value)
            {
                if(key > _queue.size())
                {
                    auto newSize{2 * _queue.size()};
                    if (key > newSize)
                    {
                        try{
                            _queue.resize(key + 1);
                        }
                        catch(std::exception& ex) {
                            std::cout << "bad alloc : min" << _minIndex << "|" << key + 1;
                        }

                    }
                    else
                    {
                        try{
                            _queue.resize(newSize + 1);
                        }
                        catch(std::exception& ex) {
                            std::cout << "bad alloc : min" << _minIndex << "|" << newSize + 1;
                        }
                    }

                }

                _queueValuesIndices[value] = _queue[key].size();
                _queue[key].push_back(value);

                if(key < _minIndex)
                    _minIndex = key;

                _empty = false;
            }

            auto top() const
            {
                return std::make_tuple(_minIndex, _queue[_minIndex].back());
            }

            void pop()
            {
                _queue[_minIndex].pop_back();

                if(_queue[_minIndex].empty())
                {
                    for(auto i{_minIndex}; i<_queue.size(); ++i)
                        if(!_queue[i].empty())
                        {
                            _minIndex = i;
                            return;
                        }

                    _minIndex = std::numeric_limits<KeyTypeMajor>::max();
                    _empty = true;
                }
            }

            bool empty() const
            {
                return _empty;
            }

            void decrease(KeyTypeMajor keyMajor, KeyTypeMinor value, KeyTypeMajor newKeyMajor)
            {
                auto& oldKeyVec = _queue[keyMajor];
                oldKeyVec[_queueValuesIndices[value]] = oldKeyVec.back();
                _queueValuesIndices[oldKeyVec.back()] = _queueValuesIndices[value];
                oldKeyVec.pop_back();

                push(newKeyMajor, value);
            }

        private:
            KeyTypeMajor _minIndex{std::numeric_limits<KeyTypeMajor>::max()};
            bool _empty{true};
            std::vector<size_t> _queueValuesIndices;
            std::vector<std::vector<KeyTypeMinor>> _queue;
    };


    //template<typename KeyType, typename T>
    //class IndexedPriorityQueue
    //{
    //
    //};
}

#endif