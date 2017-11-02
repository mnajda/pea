#include "Instance.h"

#include <iostream>

Instance::Instance()
{
    /*std::vector<std::vector<int> > costMatrix = { { intMax, 14, 4, 10, 20 },
                                                  { 14, intMax, 7,  8,  7 },
                                                  { 4, 5, intMax,  7,  16 },
                                                  { 11, 7,  9, intMax,  2 },
                                                  { 18, 7, 17,  4, intMax } };*/

    std::vector<std::vector<int> > costMatrix = { {intMax, 3, 4, 2, 7 },
                                                  { 3, intMax, 4, 6, 3},
                                                  { 4, 4, intMax, 5, 8},
                                                  { 2, 6, 5, intMax, 6},
                                                  { 7, 3, 8, 6, intMax} };

    /*std::vector<std::vector<int> > costMatrix = { { intMax, 10, 8, 9, 7 },
                                                  { 10, intMax, 10, 5, 6 },
                                                  { 8, 10, intMax, 8, 9 },
                                                  { 9, 5, 8, intMax, 6 },
                                                  { 7, 6, 9, 6, intMax } };*/

    /*std::vector<std::vector<int> > costMatrix = { { intMax, 3, 1, 5, 8 },
                                                  { 3, intMax, 6, 7, 8 },
                                                  { 1, 6, intMax, 4, 2 },
                                                  { 5, 7, 4, intMax, 3 },
                                                  { 8, 9, 2, 3, intMax } };*/

    citiesCount = costMatrix.size();
    prepareTree(costMatrix);

    std::cout << minCost << std::endl;
    std::cout << std::endl;

    for (const auto& e : bestPath)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

Instance::Instance(std::list<std::tuple<int, int, int>> cities)
{
    std::vector<std::vector<int> > costMatrix(cities.size(), std::vector<int>(cities.size()));
    int x, y;
    for (int i = 0; i < cities.size(); ++i)
    {
        auto first = std::next(cities.begin(), i);
        for (auto k = 0; k < cities.size(); ++k)
        {
            auto second = std::next(cities.begin(), k);
            x = std::get<1>(*first) - std::get<1>(*second);
            y = std::get<2>(*first) - std::get<2>(*second);
            costMatrix[i][k] = (lround(sqrt((x * x + y * y))));
        }
    }
    for (int i = 0; i < cities.size(); ++i)
    {
        costMatrix[i][i] = intMax;
    }
    citiesCount = costMatrix.size();
    prepareTree(costMatrix);

    std::cout << minCost << std::endl;
    std::cout << std::endl;

    for (const auto& e : bestPath)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

int Instance::calculateLowerBound(std::vector<std::vector<int> >& matrix, std::vector<int>& path, int cost)
{
    int lowerBound = 0;
    for (int i = 0; i < path.size() - 1; ++i)
    {
        lowerBound += matrix[path[i]][path[i + 1]];
    }
    lowerBound += cost;
    if (path.size() == citiesCount)
    {
        lowerBound += matrix[path.back()][0];
    }
    return lowerBound;
}

void Instance::prepareTree(std::vector<std::vector<int> >& matrix)
{
    std::vector<int> path;
    std::vector<int> availableCities;
    path.push_back(0);
    for (int i = 1; i < matrix.size(); ++i)
    {
        availableCities.push_back(i);
    }
    Node root{ availableCities, path, 0 };
    branchAndBound(matrix, root);
}

void Instance::branchAndBound(std::vector<std::vector<int> >& matrix, Node node)
{
    if ((node.currentPath.size() > 1) && (calculateLowerBound(matrix, node.currentPath) > minCost))
    {
        return;
    }
    if (node.currentPath.size() == matrix.size())
    {
        int lowerBound = calculateLowerBound(matrix, node.currentPath);
        if (lowerBound < minCost)
        {
            minCost = lowerBound;
            bestPath = node.currentPath;
        }
        return;
    }
    std::vector<Node> nodes;
    for (int i = 1; i < matrix.size(); ++i)
    {
        if (std::find(node.currentPath.begin(), node.currentPath.end(), i) == node.currentPath.end())
        {
            std::vector<int> availableCities;
            for (int k = 1; k < matrix.size(); ++k)
            {
                if (i != k && (std::find(node.currentPath.begin(), node.currentPath.end(), k) == node.currentPath.end()))
                {
                    availableCities.push_back(k);
                }
            }
            Node newNode{ availableCities, node.currentPath, i };
            newNode.currentPath.push_back(i);
            nodes.push_back(newNode);
        }
    }
    for (auto& next : nodes)
    {
        if (!next.availableCities.empty())
        {
            next.availableCities.erase(next.availableCities.begin());
        }
        branchAndBound(matrix, next);
    }
}
