#include <fmt/format.h>
#include "_3/Zadania.h"
#include "Timer/Timer.h"

void launch(const std::string& path)
{
    f64 dur{0.0};
    std::vector<uint32_t> res;
    {
        Timer t(&dur);
        res = PS3::zad3(path);
    }

    fmt::print("{}  ", res.back());
    res.pop_back();
    fmt::print("[ ");
    for(auto merc : res)
        fmt::print("{}, ", merc);
    fmt::print("]\n");

    fmt::print("time :: {} \n\n", dur);
}

int main()
{
    launch("_3/dataFiles/data0.txt");
    launch("_3/dataFiles/data1.txt");
    launch("_3/dataFiles/data2.txt");
    launch("_3/dataFiles/data3.txt");
    launch("_3/dataFiles/data4.txt");
    launch("_3/dataFiles/data5.txt");
    launch("_3/dataFiles/data6.txt");
    launch("_3/dataFiles/data7.txt");

    return 0;
}