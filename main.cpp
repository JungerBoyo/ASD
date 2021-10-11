#include <fmt/format.h>
#include "_1/zadania.h"
#include "Timer/Timer.h"

int main()
{
    f64 duration_0_1{0.0};
    {
        Timer timer{&duration_0_1};
        if(PS1::zad2_0("_1/dataFiles/test1_OUT4") != 4) fmt::print("[error]0_1\n");
    }

    f64 duration_0_2{0.0};
    {
        Timer timer{&duration_0_2};
        if(PS1::zad2_0("_1/dataFiles/test2_OUT5") != 5) fmt::print("[error]0_2\n");
    }

    f64 duration_0_3{0.0};
    {
        Timer timer{&duration_0_3};
        if(PS1::zad2_0("_1/dataFiles/test3_OUT17") != 17) fmt::print("[error]0_3\n");
    }



    f64 duration_1_1{0.0};
    {
        Timer timer{&duration_1_1};
        if(PS1::zad2_1("_1/dataFiles/test1_OUT4") != 4) fmt::print("[error]1_1\n");
    }

    f64 duration_1_2{0.0};
    {
        Timer timer{&duration_1_2};
        if(PS1::zad2_1("_1/dataFiles/test2_OUT5") != 5) fmt::print("[error]1_2\n");
    }

    f64 duration_1_3{0.0};
    {
        Timer timer{&duration_1_3};
        if(PS1::zad2_1("_1/dataFiles/test3_OUT17") != 17) fmt::print("[error]1_3\n");
    }



    f64 duration_2_1{0.0};
    {
        Timer timer{&duration_2_1};
        if(PS1::zad2_2("_1/dataFiles/test1_OUT4") != 4) fmt::print("[error]2_1\n");
    }

    f64 duration_2_2{0.0};
    {
        Timer timer{&duration_2_2};
        if(PS1::zad2_2("_1/dataFiles/test2_OUT5") != 5) fmt::print("[error]2_2\n");
    }

    f64 duration_2_3{0.0};
    {
        Timer timer{&duration_2_3};
        if(PS1::zad2_2("_1/dataFiles/test3_OUT17") != 17) fmt::print("[error]2_3\n");
    }


    fmt::print("durations for 0 :: {}ms {}ms {}ms\ndurations for 1 :: {}ms {}ms {}ms\ndurations for 2 :: {}ms {}ms {}ms\n",
               duration_0_1, duration_0_2, duration_0_3,
               duration_1_1, duration_1_2, duration_1_3,
               duration_2_1, duration_2_2, duration_2_3);


    return 0;
}
