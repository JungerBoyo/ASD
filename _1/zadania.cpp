#include "zadania.h"

#include <fmt/format.h>
#include <list>
#include <fstream>
#include <bitset>
#include <vector>
#include <array>
#include <sstream>
#include <future>

uint32_t PS1::zad2_1(const std::string& inFilePath)
{
    std::ifstream inStream(inFilePath);

    std::string line;
    getline(inStream, line);

    /// wczytanie ilości danych
    uint32_t dataCount = std::stoul(line);

    /// definicja tablicy first - dana, second - suma
    std::vector<std::pair<std::bitset<25>, uint32_t>> bitsets;
    bitsets.reserve(dataCount);

    uint32_t max = 0;/// maksymalna ilość takich samych danych
    while(getline(inStream, line))
    {
        /// wczytanie danej
        std::bitset<25> tmpBitset(line);

        bool contains{false}; /// dana - czy istnieje w dotychczasowch wartosciach
        for (auto& bitset : bitsets)
            if (tmpBitset == bitset.first) /// jesli zdarzy się że istnieje
            {
                if(++bitset.second > max) /// zinkrementuj i porównaj z max
                    max = bitset.second; /// jeśli większe od max zauktualizuj max

                contains = true; /// zawiera się
                break; /// wyjdź z pętli
            }

        if (!contains) /// jeśli jeszcze nie istnieje
            bitsets.emplace_back(std::make_pair(tmpBitset, 1)); /// dodaj do tablicy
    }

    /// w przypadku gdy wszystkie wartości są unikalne ustaw max na 1
    if(!max)
        max = 1;

    return max;
}


uint32_t PS1::zad2_2(const std::string& inFilePath)
{
    std::ifstream inStream(inFilePath);

    std::string line;
    getline(inStream, line);

    uint32_t dataCount = std::stoul(line);

    ///deklaracja tablicy na dane
    std::vector<uint32_t> bitsets;
    bitsets.reserve(dataCount);

    uint32_t maxBitset = 0;         /// maksymalna dana
    uint32_t minBitset = UINT32_MAX;/// minimalna dana

    while(getline(inStream, line))
    {
        /// konwersja ze bitsetu w formacie string do uint32_t
        uint32_t tmpBitset = 0;
        for(uint32_t i{0}; i<line.size(); ++i)
            if(line[i] == '1')
                tmpBitset |= (1 << (line.size()-1 - i));

        bitsets.push_back(tmpBitset);

        /// jeśli obecna dana większa od max aktualizuj max
        if(maxBitset < tmpBitset)
            maxBitset = tmpBitset;

        /// jeśli obecna dana mniejsza od min aktualizuj min
        if(minBitset > tmpBitset)
            minBitset = tmpBitset;
    }

    uint32_t maxNum = 0; /// maksymalna ilość takich samych danych

    /// zadeklaruj "hash set", o wielkości [0, maxBitset - minBitset + 1)
    std::vector<uint32_t> sums(maxBitset - minBitset + 1, 0);
    for(auto bitset : bitsets)
        /// "zahashuj" wartość bitset odejmując od nań wartość
        /// minBitsetu/offsetu w dół, następnie zinkrementuj
        /// przyporzadkowaną sume i sprawdź czy jest wieksza od
        /// dotychczasowego maksimum jeśli tak aktualizuj maxNum
        if(++sums[bitset - minBitset] > maxNum)
            maxNum = sums[bitset - minBitset];

    return maxNum;
}