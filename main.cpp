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

    auto rawCompl = res.back();
    res.pop_back();

    auto recCounter = res.back();
    res.pop_back();

    fmt::print("{}  ", res.back());
    res.pop_back();
    fmt::print("[ ");
    for(auto merc : res)
        fmt::print("{}, ", merc);
    fmt::print("]\n");


    fmt::print("recursive calls :: {} \n"
               "raw complexity :: {} \n"
               "problem % reduction :: -{}%\n"
               "time :: ~{}ms \n"
               "memory usage :: ~{}MB\n\n",
            recCounter,
            rawCompl,
            static_cast<uint32_t>((1.f - static_cast<float>(recCounter)/static_cast<float>(rawCompl)) * 100.f),
            dur,
            (static_cast<float>(rawCompl)*4.f)/1000000.f);
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