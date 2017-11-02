#pragma once

#include <vector>
#include <list>
#include <tuple>
#include <numeric>

struct Node
{
    std::vector<int> currentPath;
    std::vector<int> availableCities;
    int city;
    Node(std::vector<int> cities, std::vector<int> path, int thisCity) : availableCities(cities),
                                                                         currentPath(path),
                                                                         city(thisCity)
    {}
};

class Instance
{
public:
    Instance();
    Instance(std::list<std::tuple<int, int, int> > cities);
private:
    int calculateLowerBound(std::vector<std::vector<int> >& matrix, std::vector<int>& path, int cost = 0);
    void prepareTree(std::vector<std::vector<int> >& matrix);
    void branchAndBound(std::vector<std::vector<int> >& matrix, Node node);

    std::vector<int> bestPath;
    static constexpr int intMax = std::numeric_limits<int>::max();
    int minCost = intMax;
    int citiesCount = 0;
};