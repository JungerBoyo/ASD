#ifndef ASD_PS_ZADANIA_H
#define ASD_PS_ZADANIA_H

#include <string_view>
#include <string>
#include <optional>
#include <vector>

namespace PS5
{
    struct CommandInfo
    {
        std::optional<std::string> result;
        uint16_t m1{0};
        uint16_t m2{0};
        uint16_t t{0};
    };

    std::vector<CommandInfo> Zad5(std::string_view dataPath);
}

#endif