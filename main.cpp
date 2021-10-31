#include <fmt/format.h>
#include "_2/Zadania.h"
#include "sortingAlgs/sortAlgs.h"
#include "Timer/Timer.h"

std::tuple<f64, uint32_t> launch0(const std::string& path)
{
    f64 duration{0.};
    uint32_t res{0};
    {
        Timer timer(&duration);
        res = PS2::zad3_1(path);
    }

    return {duration, res};
}

std::tuple<f64, uint32_t> launch1(const std::string& path)
{
    f64 duration{0.};
    uint32_t res{0};
    {
        Timer timer(&duration);
        res = PS2::zad3_0(path);
    }

    return {duration, res};
}


int main()
{

    auto[t1_2d, o1_2d] = launch0("_2/dataFiles/data1.txt");
    auto[t2_2d, o2_2d] = launch0("_2/dataFiles/data2.txt");
    auto[t3_2d, o3_2d] = launch0("_2/dataFiles/data3.txt");
    auto[t4_2d, o4_2d] = launch0("_2/dataFiles/data4.txt");
    auto[t5_2d, o5_2d] = launch0("_2/dataFiles/data5.txt");

    auto[t1_3d, o1_3d] = launch1("_2/dataFiles/data1.txt");
    auto[t2_3d, o2_3d] = launch1("_2/dataFiles/data2.txt");
    auto[t3_3d, o3_3d] = launch1("_2/dataFiles/data3.txt");
    auto[t4_3d, o4_3d] = launch1("_2/dataFiles/data4.txt");
    auto[t5_3d, o5_3d] = launch1("_2/dataFiles/data5.txt");

    fmt::print("\n\n"
            "******************************3D*TESTS*****************************\n"
            "** Tests         | test1  | test2 | test3  | test4  |    test5   **\n"
            "*******************************************************************\n"
            "** n x m x depth | 4x4x13 | 3x3x13| 5x5x13 | 7x7x13 | 200x200x14 **\n"
            "*******************************************************************\n"
            "** time[ms]      | {}  | {} | {}  | {}  | {}   **\n"
            "*******************************************************************\n"
            "** output        | {}      | {}    | {}     | {}   |  {}     **\n"
            "*******************************************************************\n\n\n",
            t1_3d, t2_3d, t3_3d, t4_3d, t5_3d, o1_3d, o2_3d, o3_3d, o4_3d, o5_3d);

    fmt::print(
            "******************************2D*TESTS*****************************\n"
            "** Tests         | test1  | test2 | test3  | test4  |    test5   **\n"
            "*******************************************************************\n"
            "** n x m x depth | 4x4x13 | 3x3x13| 5x5x13 | 7x7x13 | 200x200x14 **\n"
            "*******************************************************************\n"
            "** time[ms]      | {}  | {} | {}  | {}  | {}     **\n"
            "*******************************************************************\n"
            "** output        | {}      | {}    | {}     | {}     |  {}    **\n"
            "*******************************************************************\n\n\n",
            t1_2d, t2_2d, t3_2d, t4_2d, t5_2d, o1_2d, o2_2d, o3_2d, o4_2d, o5_2d);

    return 0;
}
