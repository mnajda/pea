#pragma once

#include <vector>
#include <list>
#include <tuple>
#include <numeric>
#include <chrono>

struct Node
{
    std::vector<int> currentPath;
    int city;
    Node(std::vector<int> path, int thisCity) : currentPath(path),
                                                city(thisCity)
    {}
};

class Instance
{
public:
    Instance();
    Instance(std::list<std::tuple<int, int, int> > cities);
    void printSolution();
    void printTime();
private:
    int calculateLowerBound(std::vector<std::vector<int> >& matrix, std::vector<int>& path) const;
    void prepareTree(std::vector<std::vector<int> >& matrix);
    void branchAndBound(std::vector<std::vector<int> >& matrix, Node node);

    std::vector<int> bestPath;
    static constexpr int intMax = std::numeric_limits<int>::max();
    int minCost = intMax;
    std::chrono::duration<double> time;
};