#include "Zadania.h"
#include <fstream>

struct Mercenary
{
    int32_t strength;
    int32_t gluttony;
    int32_t debauch;
};

template<typename T>
struct SubProblemSpace
{
    SubProblemSpace(size_t xMag, size_t yMag, size_t zMag, T fillValue)
        : _xMagnitude(xMag), _xyPlaneSize(xMag*yMag),
          _problems(xMag*yMag*zMag, fillValue)
        {}

    void fillXYPlane(size_t z, T fillValue)
    {
        for(size_t i{z*_xyPlaneSize}; i<z*_xyPlaneSize + _xyPlaneSize; ++i)
            _problems[i] = fillValue;
    }

    T& operator()(size_t x, size_t y, size_t z)
    {
        return _problems[x + y*_xMagnitude + z*_xyPlaneSize];
    }

    const T& operator()(size_t x, size_t y, size_t z) const
    {
        return _problems[x + y*_xMagnitude + z*_xyPlaneSize];
    }

    private:
        size_t _xMagnitude;
        size_t _xyPlaneSize;

        std::vector<T> _problems;
};

struct RentBest
{
    RentBest(std::vector<Mercenary>&& mercenaries, SubProblemSpace<int32_t>&& subProblems)
        : _subProblems(std::move(subProblems)),
          _mercenaries(std::move(mercenaries))  {}

    int32_t operator()(int32_t food, int32_t entmt, int32_t merIndex)
    {
        ++_recursionCounter;

        /*
         wartosc dla Z(food, entmt,  n - (merIndex+1)) (nie bierze)
         */
        int32_t notRenting{0};

        /*
         wartosc dla mercenaries[merIndex].strength +
         Z(food - mercenaries[merIndex].gluttony, entmt - mercenaries[merIndex].debauch,
         n - (merIndex+1))
         */
        int32_t renting{0};


        notRenting = _subProblems(food, entmt, merIndex+1);
        if (notRenting == -1)
            notRenting = (*this)(food, entmt, merIndex+1);

        if(food - _mercenaries[merIndex].gluttony >= 0 && entmt - _mercenaries[merIndex].debauch >= 0)
        {
            auto tmpF = food - _mercenaries[merIndex].gluttony;
            auto tmpE = entmt - _mercenaries[merIndex].debauch;

            renting = _subProblems(tmpF, tmpE, merIndex+1);
            if(renting == -1)
                renting = (*this)(tmpF, tmpE, merIndex+1) + _mercenaries[merIndex].strength;
            else
                renting += _mercenaries[merIndex].strength;
        }
        else
        {
            renting = _subProblems(food, entmt, merIndex+1);
            if (renting == -1)
                renting = (*this)(food, entmt, merIndex+1);
        }

        return _subProblems(food, entmt, merIndex) = std::max(renting, notRenting);
    }

    std::vector<uint32_t> RetrieveChosensList(int32_t food, int32_t entmt)
    {
        std::vector<uint32_t> chosenOnes;
        chosenOnes.reserve(_mercenaries.size()/2);

        auto tmpF = food;
        auto tmpE = entmt;
        for(uint32_t i{0}; i<_mercenaries.size(); ++i)
        {
            auto lhs = _subProblems(tmpF, tmpE, i+1);
            auto rhs = -1;

            if(tmpF - _mercenaries[i].gluttony >= 0 && tmpE - _mercenaries[i].debauch >= 0)
                rhs = _subProblems(tmpF - _mercenaries[i].gluttony, tmpE - _mercenaries[i].debauch, i+1)
                        + _mercenaries[i].strength;

            if(rhs > lhs)
            {
                chosenOnes.push_back(i+1);
                tmpF -= _mercenaries[i].gluttony;
                tmpE -= _mercenaries[i].debauch;
            }
        }

        return chosenOnes;
    }

    auto getRecursionCounterValue() const { return _recursionCounter; }


    private:
        size_t _recursionCounter{0};

        std::vector<Mercenary> _mercenaries;
        SubProblemSpace<int32_t> _subProblems;
};

std::vector<uint32_t> PS3::zad3(const std::string &path)
{
    std::ifstream stream(path);
    std::string line;

    getline(stream, line);
        auto foodStock = static_cast<int32_t>(std::stoul(std::string(line, 0, line.find(' ', 0)))  +1);
        auto entmtStock = static_cast<int32_t>(std::stoul(std::string(line, line.find(' ', 0) + 1)) +1);

    getline(stream, line);
        auto merCount = static_cast<int32_t>(std::stoul(line));

    std::vector<Mercenary> mercenaries;
    mercenaries.reserve(merCount);

    SubProblemSpace<int32_t> subProblems(foodStock, entmtStock, (merCount+1), -1);
    subProblems.fillXYPlane(merCount, 0);

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

    RentBest rentBestFn(std::move(mercenaries), std::move(subProblems));

    auto result = rentBestFn(foodStock-1, entmtStock-1, 0); // Z(P, R, n)
    auto merList = rentBestFn.RetrieveChosensList(foodStock-1, entmtStock-1);

    merList.push_back(result);
    merList.push_back(rentBestFn.getRecursionCounterValue());
    merList.push_back((merCount+1) * foodStock * entmtStock);

    return merList;
}
