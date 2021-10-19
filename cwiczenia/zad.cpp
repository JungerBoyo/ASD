#include "zad.h"
#include <fstream>
#include <vector>


static uint32_t CountQuadPixelSum(uint32_t kernelSize, uint32_t stride, uint32_t h, uint32_t w, const std::vector<uint32_t>& pixels)
{
    uint32_t sum{0};
    for(uint32_t ker{0}; ker<kernelSize*kernelSize; ++ker)
        sum += pixels[(h + ker/kernelSize) * stride + (w+(ker%kernelSize))/32] & (1 << (31 - (w + (ker%kernelSize))%32)) ? 1 : 0;

    return sum;
}

static uint32_t CountColumnPixelSum(uint32_t kernelSize, uint32_t stride, uint32_t h, uint32_t w, const std::vector<uint32_t>& pixels)
{
    uint32_t sum{0};
    const uint32_t bit = (1 << (31 - (w % 32)));
    const uint32_t rowOffset = w / 32;
    for(uint32_t row{0}; row<kernelSize; ++row)
        sum += pixels[(h + row) * stride + rowOffset] & bit ? 1 : 0;

    return sum;
}

static uint32_t CountRowPixelSum(uint32_t kernelSize, uint32_t stride, uint32_t h, uint32_t w, const std::vector<uint32_t>& pixels)
{
    uint32_t sum{0};
    const uint32_t row = h * stride;
    for(uint32_t col{0}; col<kernelSize; ++col)
        sum += pixels[row + ((w + col)/32)] & (1 << (31 - ((w + col)%32) )) ? 1 : 0;

    return sum;
}



uint32_t cwiczenia::zad1_0(const std::string& path)
{
    std::ifstream stream(path);

    std::string line;
    getline(stream, line);

    uint32_t dimension = std::stoul(line);

    uint32_t stride = (dimension/32) + static_cast<uint32_t>(dimension % 32 != 0);
    std::vector<uint32_t> pixels(dimension * stride, 0);

    for(uint32_t i{0}; i<dimension && getline(stream, line); ++i)
    {
        uint32_t tmpWidthCounter = 0;
        for(const char ch : line)
        {
            if(ch == '1')
                pixels[i * stride + tmpWidthCounter/32] |= (1 << ((31 - tmpWidthCounter)%32));

            ++tmpWidthCounter;
        }
    }

    getline(stream, line);
    uint32_t kernelSize = std::stoul(line);

    uint32_t maxSum{0};

    ///1
    //for(uint32_t h{0}; h < dimension - kernelSize + 1; ++h)
    //    for(uint32_t w{0}; w < dimension - kernelSize + 1; ++w)
    //    {
    //        uint32_t sum{0};
    //        for(uint32_t ker{0}; ker<kernelSize*kernelSize; ++ker)
    //            sum += pixels[(h + ker/kernelSize) * stride + (w+(ker%kernelSize))/32] & (1 << (31 - (w + (ker%kernelSize))%32)) ? 1 : 0;
//
    //        if(maxSum < sum)
    //            maxSum = sum;
    //    }

    ///2

    uint32_t startSum = CountQuadPixelSum(kernelSize, stride, 0, 0, pixels);
    for(uint32_t h{0}; h < dimension - kernelSize + 1; ++h)
    {
        uint32_t nextSum = startSum;
        for(uint32_t w{0}; w < dimension - kernelSize + 1; ++w)
        {
            if(nextSum > maxSum)
                maxSum = nextSum;

            nextSum = nextSum  - CountColumnPixelSum(kernelSize, stride, h, w             , pixels)
                               + CountColumnPixelSum(kernelSize, stride, h, w + kernelSize, pixels);
        }

        startSum = startSum - CountRowPixelSum(kernelSize, stride, h             , 0, pixels)
                            + CountRowPixelSum(kernelSize, stride, h + kernelSize, 0, pixels);
    }

    return maxSum;
}


uint32_t cwiczenia::hanoi(uint32_t diskCount)
{
    if(diskCount == 1)
        return 1;
    else
    {
        return 2*hanoi(diskCount - 1) + 1;
    }
}

uint64_t cwiczenia::fastPowering(uint64_t num, uint32_t power, uint32_t modArg)
{
    if(power == 2)
        return num * num % modArg;

    uint64_t tmp = fastPowering(num, power / 2, modArg) % modArg;
    tmp = tmp * tmp % modArg;

    if(power % 2)
        return tmp * num % modArg;
    else
        return tmp % modArg;
}