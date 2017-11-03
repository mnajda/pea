#pragma once

#include <vector>
#include <list>
#include <tuple>
#include <numeric>

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
private:
    int calculateLowerBound(std::vector<std::vector<int> >& matrix, std::vector<int>& path);
    void prepareTree(std::vector<std::vector<int> >& matrix);
    void branchAndBound(std::vector<std::vector<int> >& matrix, Node node);

    std::vector<int> bestPath;
    static constexpr int intMax = std::numeric_limits<int>::max();
    int minCost = intMax;
};