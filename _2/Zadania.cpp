#include "Zadania.h"
#include <vector>
#include <array>
#include <fstream>
#include <fmt/format.h>

struct DynamicBitset
{
    DynamicBitset() = default;

    DynamicBitset(std::size_t bitsCount, bool bitsState)
    {
        auto value = bitsState ? UINT32_MAX : 0;
        _bits.resize(bitsCount / 32 + static_cast<uint32_t>(bitsCount % 32 != 0), value);
    }

    void set(std::size_t index)
    {
        _bits[index/32] |= (setMask >> index%32);
    }

    void reset(std::size_t index)
    {
        _bits[index/32] &= ~(setMask >> index%32);
    }

    bool operator[](std::size_t index) const
    {
        return _bits[index/32] & (setMask >> index%32);
    }

    private:
        static constexpr uint32_t setMask   = 1 << 31;
        std::vector<uint32_t> _bits;
};

///3D :>

struct WaterStateSpace
{
    WaterStateSpace() = default;

    WaterStateSpace(uint32_t n, uint32_t m, uint32_t waterLine, uint32_t depth, std::vector<uint32_t>&& cells)
        : _zAxisMagnitude(n), _waterLine(waterLine), _xAxisMagnitude(m), _yAxisMagnitude(depth - 1 + 5),
          _states(n*m, {depth - 1 + 5, false})
    {
        uint32_t statesIter{0};
        for(const auto cell: cells)
        {
            auto y = cell - 1;
            _states[statesIter].set(y + 0);
            _states[statesIter].set(y + 1);
            _states[statesIter].set(y + 2);
            _states[statesIter].set(y + 3);
            _states[statesIter].set(y + 4);

            ++statesIter;
        }
    }

    void reset(uint32_t x, uint32_t y, uint32_t z)
    {
        _states[x + _zAxisMagnitude * z].reset(y);
        ++_cubicMeterCounter;
    }

    bool check(int32_t x, int32_t y, int32_t z) const
    {
        return  (y < _yAxisMagnitude && y >= _waterLine)     &&
                (x < _xAxisMagnitude && x >= 0         )     &&
                (z < _zAxisMagnitude && z >= 0         )     &&

                _states[x + _zAxisMagnitude * z][y];
    }

    uint32_t getCounterValue() const
    {
        return _cubicMeterCounter;
    }

    private:
        uint32_t _waterLine{0};
        uint32_t _yAxisMagnitude{0};
        uint32_t _xAxisMagnitude{0};
        uint32_t _zAxisMagnitude{0};

        std::vector<DynamicBitset> _states;
        uint32_t _cubicMeterCounter{0};
};

static WaterStateSpace stateSpace;


void TrackWater(int32_t x, int32_t y, int32_t z)
{
    if(stateSpace.check(x, y, z))
    {
        stateSpace.reset(x, y, z);

        TrackWater(x + 1, y, z);
        TrackWater(x - 1, y, z);
        TrackWater(x, y, z + 1);
        TrackWater(x, y, z - 1);

        TrackWater(x + 1, y, z + 1);
        TrackWater(x - 1, y, z - 1);
        TrackWater(x - 1, y, z + 1);
        TrackWater(x + 1, y, z - 1);

        TrackWater(x, y + 1, z);
        TrackWater(x, y - 1, z);
    }
}


uint32_t PS2::zad3_0(const std::string& path)
{
    std::ifstream stream(path);
    std::string line;

    getline(stream, line);

    const uint32_t n = std::stoul(std::string(line, 0, line.find(' ', 0)));
    const uint32_t m = std::stoul(std::string(line, line.find(' ', 0) + 1));

    std::vector<uint32_t> cells(n*m, 0);

    uint32_t cellIter{0};
    uint32_t depth{0};
    while(getline(stream, line) && cellIter < n*m)
    {
        uint32_t nextNum = 0;
        for(uint32_t i{0}; i<m; ++i)
        {
            uint32_t tmpCell = std::stoul(std::string(line, nextNum));

            if(tmpCell > depth)
                depth = tmpCell;

            cells[cellIter++] = tmpCell;
            nextNum = line.find(' ', nextNum + 1);
        }
    }

    const auto outflowZ = static_cast<int32_t>(std::stoul(std::string(line, 0, line.find(' ', 0)))  - 1);  /// i
    const auto outflowX = static_cast<int32_t>(std::stoul(std::string(line, line.find(' ', 0) + 1)) - 1); /// j
    const auto outflowY = static_cast<int32_t>(cells[outflowX + outflowZ * n] - 1 + 4);
    stream.close();

    stateSpace = std::move(WaterStateSpace(n, m, outflowY, depth, std::move(cells)));

    TrackWater(outflowX, outflowY, outflowZ);

    return stateSpace.getCounterValue();
}

/// 2D...

struct StatePlane
{
    StatePlane() = default;

    StatePlane(uint32_t n, uint32_t m, int32_t waterLine, std::vector<int32_t>&& cells)
                : _xAxisMagnitude(m), _zAxisMagnitude(n), _cells(std::move(cells)), _states(n*m, true),
                  _waterLine(waterLine) {}

    void reset(uint32_t x, uint32_t z)
    {
        _states.reset(x + _zAxisMagnitude * z);
        _cubicMeterCounter += std::min(5, _cells[x + z * _zAxisMagnitude] + 4 - _waterLine);
    }

    bool check(int32_t x, int32_t z, int32_t prevX, int32_t prevZ) const
    {
        return  (x < _xAxisMagnitude && x >= 0)                       &&
                (z < _zAxisMagnitude && z >= 0)                       &&
                _states[x + _zAxisMagnitude * z]                      &&


                _cells[x + _zAxisMagnitude * z] - 1 + 4 >= _waterLine                               &&
                abs(_cells[prevX + prevZ * _zAxisMagnitude] - _cells[x + z * _zAxisMagnitude]) < 5;
    }

    uint32_t getCubicMeterCounterValue() const
    {
        return _cubicMeterCounter;
    }

    private:
        int32_t _waterLine{0};

        uint32_t _xAxisMagnitude{0};
        uint32_t _zAxisMagnitude{0};

        DynamicBitset _states;
        std::vector<int32_t> _cells;
        uint32_t _cubicMeterCounter{0};

};

static StatePlane statePlane;

void TrackWaterBored(int32_t x, int32_t z, int32_t callingX, int32_t callingZ)
{
    if(statePlane.check(x, z, callingX, callingZ))
    {
        statePlane.reset(x, z);

        TrackWaterBored(x + 1, z, x, z);
        TrackWaterBored(x - 1, z, x, z);
        TrackWaterBored(x, z + 1, x, z);
        TrackWaterBored(x, z - 1, x, z);

        TrackWaterBored(x + 1, z + 1, x, z);
        TrackWaterBored(x - 1, z - 1, x, z);
        TrackWaterBored(x - 1, z + 1, x, z);
        TrackWaterBored(x + 1, z - 1, x, z);
    }
}

uint32_t PS2::zad3_1(const std::string &path)
{
    std::ifstream stream(path);
    std::string line;

    getline(stream, line);

    const uint32_t n = std::stoul(std::string(line, 0, line.find(' ', 0)));
    const uint32_t m = std::stoul(std::string(line, line.find(' ', 0) + 1));

    std::vector<int32_t> cells(n*m, 0);

    uint32_t cellIter{0};
    uint32_t depth{0};
    while(getline(stream, line) && cellIter < n*m)
    {
        uint32_t nextNum = 0;
        for(uint32_t i{0}; i<m; ++i)
        {
            int32_t tmpCell = static_cast<int32_t>(std::stoul(std::string(line, nextNum)));

            if(tmpCell > depth)
                depth = tmpCell;

            cells[cellIter++] = tmpCell;
            nextNum = line.find(' ', nextNum + 1);
        }
    }

    const auto outflowZ = static_cast<int32_t>(std::stoul(std::string(line, 0, line.find(' ', 0)))  - 1);  /// i
    const auto outflowX = static_cast<int32_t>(std::stoul(std::string(line, line.find(' ', 0) + 1)) - 1); /// j
    const auto outflowY = static_cast<int32_t>(cells[outflowX + outflowZ * n] - 1 + 4);
    stream.close();

    statePlane = std::move(StatePlane(n, m, outflowY, std::move(cells)));

    TrackWaterBored(outflowX, outflowZ, outflowX, outflowZ);

    return statePlane.getCubicMeterCounterValue();
}
