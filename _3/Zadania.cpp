#include "Zadania.h"
#include <fstream>
#include <fmt/format.h>

struct Mercenary
{
    int32_t strength;
    int32_t gluttony;
    int32_t debauch;
};

std::vector<Mercenary> mercenaries;
std::vector<int32_t> subProblems;

int32_t sizeP;
int32_t sizeR;
int32_t N;

int32_t rentBest(int32_t p, int32_t r, int32_t n)
{
    int32_t notRenting{0};
    int32_t renting{0};

    if(n+1 < N)
    {
        notRenting = subProblems[p + r * sizeP + (n + 1) * sizeP * sizeR];
        if (notRenting == -1)
            notRenting = rentBest(p, r, n + 1);
    }

    if(p - mercenaries[n].gluttony >= 0 && r - mercenaries[n].debauch >= 0)
    {
        auto tmpP = p - mercenaries[n].gluttony;
        auto tmpR = r - mercenaries[n].debauch;

        if(n + 1 < N)
        {
            renting = subProblems[tmpP + tmpR*sizeP + (n+1)*sizeP*sizeR];
            if(renting == -1)
                renting = rentBest(tmpP, tmpR, n+1) + mercenaries[n].strength;
            else
                renting +=  mercenaries[n].strength;
        }
        else
        {
            renting = mercenaries[n].strength;
            subProblems[tmpP + tmpR*sizeP + (n+1)*sizeP*sizeR] =  renting;
        }

    }
    else
    {
        if(n + 1 < N)
        {
            renting = subProblems[p + r * sizeP + (n + 1) * sizeP * sizeR];
            if (renting == -1)
                renting = rentBest(p, r, n + 1);
        }
    }

    return subProblems[p + r*sizeP + n*sizeP*sizeR] = std::max(renting, notRenting);
}

std::vector<uint32_t> PS3::zad3(const std::string &path)
{
    std::ifstream stream(path);
    std::string line;

    getline(stream, line);
        sizeP = static_cast<int32_t>(std::stoul(std::string(line, 0, line.find(' ', 0)))  +1);
        sizeR = static_cast<int32_t>(std::stoul(std::string(line, line.find(' ', 0) + 1)) +1);

    getline(stream, line);
        N = static_cast<int32_t>(std::stoul(line));

    mercenaries = std::vector<Mercenary>{};
    mercenaries.reserve(N);

    subProblems = std::vector<int32_t>((N+1) * sizeP * sizeR, -1);

    while(getline(stream, line))
    {
        Mercenary tmpMercenary{};

        uint32_t nextNum = 0;

        tmpMercenary.strength = static_cast<int32_t>(std::stoul(std::string(line, nextNum)));
        nextNum = line.find(' ', nextNum + 1);

        tmpMercenary.gluttony = static_cast<int32_t>(std::stoul(std::string(line, nextNum)));
        nextNum = line.find(' ', nextNum + 1);

        tmpMercenary.debauch = static_cast<int32_t>(std::stoul(std::string(line, nextNum)));
        mercenaries.push_back(tmpMercenary);
    }

    auto result = rentBest(sizeP-1, sizeR-1, 0);
    std::vector<uint32_t> chosenOnes;
    chosenOnes.reserve(N/2);

    auto tmpP = static_cast<int32_t>(sizeP-1);
    auto tmpR = static_cast<int32_t>(sizeR-1);
    for(uint32_t i{1}; i<N+1; ++i)
    {
        auto lhs = subProblems[tmpP + tmpR*sizeP + i*sizeP*sizeR];
        auto rhs = -1;

        if(tmpP - mercenaries[i-1].gluttony >= 0 && tmpR - mercenaries[i-1].debauch >= 0)
            rhs = subProblems[tmpP - mercenaries[i-1].gluttony        +
                             (tmpR - mercenaries[i-1].debauch)*sizeP +
                             i*sizeP*sizeR                            ] + mercenaries[i-1].strength;

        if(rhs > lhs)
        {
            chosenOnes.push_back(i);
            tmpP -= mercenaries[i-1].gluttony;
            tmpR -= mercenaries[i-1].debauch;
        }
    }

    chosenOnes.push_back(result);
    return chosenOnes;
}
