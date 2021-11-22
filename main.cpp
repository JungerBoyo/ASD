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

    auto exp = res.back();
    res.pop_back();

    auto recCounter = res.back();
    res.pop_back();

    fmt::print("{}  ", res.back());
    res.pop_back();
    fmt::print("[ ");
    for(auto merc : res)
        fmt::print("{}, ", merc);
    fmt::print("]\n");

    double hitPercentage{recCounter};
    for(auto i=0; i<exp; ++i)
        hitPercentage /= 2.f;
    hitPercentage = (1.f - hitPercentage)*100.f;

    fmt::print("recursive calls :: {}(~2^{}), raw complexity :: 2^{}, % of sb hits :: ~{}%, time :: ~{}ms \n\n",
            recCounter, static_cast<uint32_t>(std::log2p1(recCounter)), exp, hitPercentage, dur);
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