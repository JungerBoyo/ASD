#include "zadania.h"

#include <fmt/format.h>
#include <list>
#include <fstream>
#include <bitset>
#include <vector>
#include <array>


/*
 * 1. Wczytywanie zmiennych z pliku na liste przy jednoczesnym sortowaniu danych rosnąco
 *
 *      Złożoność :: artmetyczna => O(~(n*(n+1))/2)  [zakładając że w najgorszym wypadku dane są unikalne i posortowane malejąco]
 *
 * 2. Znajdywanie w posortowanej liście najdłużeszego podciągu takich samych danych
 *
 *      Złożoność :: liniowa => O(~2*n)
 *
 * Czyli :: O((n*(n+1))/2 + 2*n)
 */

uint32_t PS1::zad2_0(const std::string& inFilePath)
{
    std::ifstream inStream(inFilePath);

    std::string line;
    getline(inStream, line);

    uint32_t dataCount = std::stoul(line);

    std::list<std::bitset<25>> bitsets;

    while(getline(inStream, line))
    {
        std::bitset<25> tmpBitset(line);

        auto iter = bitsets.cbegin();
        for(;iter != bitsets.cend() && tmpBitset.to_ulong() < iter->to_ulong(); ++iter);

        if(iter != bitsets.cend())
            bitsets.insert(iter, tmpBitset);
        else
            bitsets.push_back(tmpBitset);
    }

    uint32_t max = 0;
    uint32_t tmpMax = 1;


    for(auto iter1{bitsets.begin()}, iter2{++bitsets.begin()}; iter2 != bitsets.end(); ++iter1, ++iter2)
    {
        if(*iter1 == *iter2)
            ++tmpMax;
        else
        {
            if(tmpMax > max) max = tmpMax;
            tmpMax = 1;
        }
    }

    return max;
}

/*
 * 1. Wczytywanie zmiennych z pliku do dynamicznej tablicy przy jednoczesnym sprawdzaniu
 *    czy dana wartość pojawiła się jeśli tak inkremetnacja liczby całkowitej powiązanej z tą daną
 *    jeśli nie
 *
 *      Złożoność :: artmetyczna => O(~(n*(n+1))/2)  [zakładając że w najgorszym wypadku wszystkie dane są unikalne]
 *
 * 2. Szukanie max
 *
 *      Złożoność :: liniowa => O(n)
 *
 * Czyli :: O((n*(n+1))/2 + n)
 */


uint32_t PS1::zad2_1(const std::string& inFilePath)
{
    std::ifstream inStream(inFilePath);

    std::string line;
    getline(inStream, line);

    uint32_t dataCount = std::stoul(line);

    std::vector<std::pair<std::bitset<25>, uint32_t>> bitsets;
    bitsets.reserve(dataCount);

    while(getline(inStream, line))
    {
        std::bitset<25> tmpBitset(line);

        bool contains{false};
        for (auto& bitset : bitsets)
            if (tmpBitset == bitset.first)
            {
                bitset.second++;
                contains = true;
                break;
            }

        if (!contains)
            bitsets.emplace_back(std::make_pair(tmpBitset, 1));
    }

    uint32_t max = 0;
    for(auto bitset: bitsets)
        if(bitset.second > max) max = bitset.second;

    return max;
}

/*
 * 1. Wczytywanie zmiennych z pliku do dynamicznej tablicy przy jednoczesnym sprawdzaniu
 *    czy dana wartość pojawiła się jeśli tak inkremetnacja liczby całkowitej powiązanej z tą daną
 *    jeśli nie
 *
 *      Złożoność :: kwadratowa => O(~(n*(n+1))/2)  [zakładając że w najgorszym wypadku wszystkie dane są unikalne]
 *
 * 2. Szukanie max
 *
 *      Złożoność :: liniowa => O(n)
 *
 * Czyli :: O((n*(n+1))/2 + n)
 */

uint32_t PS1::zad2_2(const std::string& inFilePath)
{
    std::ifstream inStream(inFilePath);

    std::string line;
    getline(inStream, line);

    uint32_t dataCount = std::stoul(line);

    std::vector<uint64_t> bitsets;
    bitsets.reserve(dataCount);

    uint64_t maxBitset = 0;
    uint64_t minBitset = UINT64_MAX;

    while(getline(inStream, line))
    {
        bitsets.emplace_back(std::bitset<25>(line).to_ulong());

        if(maxBitset < bitsets.back())
            maxBitset = bitsets.back();

        if(minBitset > bitsets.back())
            minBitset = bitsets.back();
    }

    uint32_t maxNum = 0;
    std::vector<uint32_t> quantities(maxBitset - minBitset + 1, 0);
    for(auto bitset : bitsets)
        if(++quantities[bitset - minBitset] > maxNum)
            maxNum = quantities[bitset - minBitset];

    return maxNum;
}