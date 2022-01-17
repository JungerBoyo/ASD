#include "Zadania.h"

#include <fstream>
#include <charconv>
#include <future>
#include <queue>

#include <IndexedPriorityQueue.h>
#include <DynamicBitset.h>

struct Edge
{
    bool operator==(uint16_t otherM) const
    {
        return vertex == otherM;
    }

    const uint16_t vertex;
    uint16_t wage;
    const uint16_t len;
};

struct Vertex
{
    std::vector<Edge> edges;
};

struct StructureInfo
{
    std::string date;
    uint16_t m1;
    uint16_t m2;
    uint16_t v;
    std::optional<uint16_t> d;
};

constexpr uint32_t InvalidCost{UINT32_MAX/2};
using PathCost_t = uint32_t;
using VertexIndex_t = uint16_t;

uint32_t
Dijkstra(const std::vector<Vertex>& graph, std::vector<PathCost_t>& bestPaths, uint16_t m1, uint32_t w, uint16_t m2, uint16_t limit)
{
    DSTRS::DynamicBitset visited(graph.size(), false);
    DSTRS::IndexedPriorityQueue_BH<VertexIndex_t, UINT16_MAX, PathCost_t, InvalidCost> pq(graph.size());

    bestPaths[m1] = w;
    pq.push(m1, w);

    while(!pq.empty())
    {
        auto[minVertex, accumWagesMin] = pq.pop();

        visited.set(minVertex);

        if(accumWagesMin > limit || minVertex == m2)
            break;

        if(bestPaths[minVertex] >= accumWagesMin)
            for(auto edge : graph[minVertex].edges)
                if(!visited[edge.vertex])
                    if(accumWagesMin + edge.wage + 5 < bestPaths[edge.vertex])
                    {
                        auto newWage = accumWagesMin + edge.wage + 5;
                        if(pq.contains(edge.vertex))
                            pq.decrease(edge.vertex, newWage);
                        else
                            pq.push(edge.vertex, newWage);

                         bestPaths[edge.vertex] = newWage;
                    }
    }

    return bestPaths[m2] - 5;
}

std::vector<PS5::CommandInfo> PS5::Zad5(std::string_view dataPath)
{
#pragma region DataParsing
    std::ifstream stream(dataPath.data());

    std::string line;
    getline(stream, line);

    uint32_t n;
    size_t begin{0};
    size_t end{line.find_first_of(' ')};
    std::from_chars(&line[begin], &line[end], n);

    uint32_t m;
    begin = end + 1;
    end = line.find_first_of(' ', begin);
    std::from_chars(&line[begin], &line[end], m);

    uint32_t z;
    begin = end + 1;
    end = line.length();
    std::from_chars(&line[begin], &line[end], z);

    std::vector<StructureInfo> structureInfos;
    structureInfos.reserve(m);

    for(uint32_t i{0}; i < m && getline(stream, line); ++i)
    {
        StructureInfo info{};

        begin = 0;
        end = line.find_first_of(' ');

        info.date = std::string(line.data(), end);
        const char op = line[end + 1];

        begin = end + 3;
        end = line.find_first_of(' ', begin);
        std::from_chars(&line[begin], &line[end], info.m1);
        info.m1--;

        begin = end + 1;
        end = line.find_first_of(' ', begin);
        std::from_chars(&line[begin], &line[end], info.m2);
        info.m2--;

        bool building{(op == 'b')};

        begin = end + 1;
        end = building ? line.find_first_of(' ', begin) : line.length();
        std::from_chars(&line[begin], &line[end], info.v);

        if(building)
        {
            begin = end + 1;
            end = line.length();
            uint32_t d;
            std::from_chars(&line[begin], &line[end], d);
            info.d.emplace(d);
        }

        structureInfos.emplace_back(std::move(info));
    }

    std::vector<Vertex> graph(n);
    std::vector<std::vector<PathCost_t>> allBestPaths;
    allBestPaths.reserve(z);

    std::vector<CommandInfo> cmdInfos;
    cmdInfos.reserve(z);

    while(getline(stream, line))
    {
        CommandInfo info{};

        begin = 0;
        end = line.find_first_of(' ');
        std::from_chars(&line[begin], &line[end], info.m1);
        info.m1--;

        begin = end + 1;
        end = line.find_first_of(' ', begin);
        std::from_chars(&line[begin], &line[end], info.m2);
        info.m2--;

        begin = end + 1;
        end = line.length();
        std::from_chars(&line[begin], &line[end], info.t);

        allBestPaths.emplace_back(std::vector<PathCost_t>(n, InvalidCost));
        allBestPaths.back()[info.m1] = 0;
        cmdInfos.push_back(info);
    }

    stream.close();
#pragma endregion

    const static auto dijkstra{[&graph, &allBestPaths](uint16_t i, uint16_t m1, uint32_t w, uint16_t m2, uint16_t lim){
        return Dijkstra(graph, allBestPaths[i], m1, w, m2, lim);
    }};

    for(const auto& stInfo : structureInfos)
    {
        uint16_t w;
        if(stInfo.d.has_value())
        {
            w = 60*(*stInfo.d)/stInfo.v;

            graph[stInfo.m1].edges.push_back({stInfo.m2, w, *stInfo.d});
            graph[stInfo.m2].edges.push_back({stInfo.m1, w, *stInfo.d});
        }
        else
        {
            auto& v1{graph[stInfo.m1]};
            auto& v2{graph[stInfo.m2]};
            auto e1 = std::find(v1.edges.begin(), v1.edges.end(), stInfo.m2);
            auto e2 = std::find(v2.edges.begin(), v2.edges.end(), stInfo.m1);

            w = 60*e1->len/stInfo.v;

            e1->wage = w;
            e2->wage = w;
        }

        std::vector<std::pair<uint16_t, std::future<uint32_t>>> tasks;
        tasks.reserve(z);
        for(size_t i{0}; i<z; ++i)
            if(!cmdInfos[i].result.has_value()       &&
               !graph[cmdInfos[i].m1].edges.empty())
            {
                auto newCostXy = allBestPaths[i][stInfo.m2] + w + 5;
                auto newCostYx = allBestPaths[i][stInfo.m1] + w + 5;

                uint16_t vertex;
                uint32_t weight;
                if(allBestPaths[i][stInfo.m1] > newCostXy)
                {
                    vertex = stInfo.m1;
                    weight = newCostXy;
                }
                else if(allBestPaths[i][stInfo.m2] > newCostYx)
                {
                    vertex = stInfo.m2;
                    weight = newCostYx;
                }
                else
                    continue;

                tasks.emplace_back(i, std::async(std::launch::async, dijkstra, i, vertex, weight, cmdInfos[i].m2, cmdInfos[i].t));
            }

        for(auto& task : tasks)
        {
            task.second.wait();
            auto result = task.second.get();

            if(result <= cmdInfos[task.first].t)
            {
                cmdInfos[task.first].m2 = result;
                cmdInfos[task.first].result.emplace(stInfo.date);
            }
        }
    }

    return cmdInfos;
}

