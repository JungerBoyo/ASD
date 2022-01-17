#include <fmt/format.h>
#include "Timer/Timer.h"
#include "_5/Zadania.h"

int main()
{
    //DSTRS::IndexedPriorityQueue_BH<uint16_t, uint32_t> pq(7);

    //pq.push(0, 3);
    //pq.push(2, 9);
    //pq.push(3, 45);
    //pq.push(1, 7);
    //pq.push(5, 1);
    //pq.push(4, 8);
    //pq.push(6, 1);
//
    //pq.pop();
//
    std::vector<PS5::CommandInfo> result;
    f64 dur{.0};
    {
        Timer timer{&dur};
        result = PS5::Zad5("_5/dataFiles/data2in");
    }

    fmt::print("{}\n\n", dur);

    for(const auto& info : result)
        fmt::print("{}\n", info.result.has_value() ? *info.result : "NIE");

    return 0;
}