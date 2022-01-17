#include "Zadania.h"
#include <fmt/format.h>
#include <fstream>
#include <Bst_avl.h>

using namespace MyDSTRS;

void PS4::zad4(std::string_view path, bool print)
{
    std::ifstream stream(path.data());

    AVLTree<std::string> dict{};
    for(std::string line; getline(stream, line);)
    {
        std::string str = std::string(&line[2]);

        switch (line[0])
        {
            case 'W': dict.insert(std::move(str)); break;
            case 'U': dict.erase(str); break;
            case 'S': fmt::print("{}\n", dict.find(str) ? "TAK" : "NIE"); break;
            case 'L': fmt::print("{}\n", dict.countAllStartingWith(str)); break;
            default: break;
        }
    }


    if(print)
        dict.Print();
}

