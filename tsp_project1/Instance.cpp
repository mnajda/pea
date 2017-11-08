#include "Instance.h"

#include <iostream>
#include <algorithm>
#include <functional>

Instance::Instance(std::vector<std::vector<int> > costMatrix, int enableBF)
{
    using clock = std::chrono::high_resolution_clock;

    for (int i = 0; i < costMatrix.size(); ++i)
    {
        costMatrix[i][i] = intMax;
    }

    auto begin = clock::now();
    prepareTree(costMatrix);
    auto end = clock::now();
    time = end - begin;

    printSolution();
    printTime();

    begin = clock::now();
    bruteForce(costMatrix);
    end = clock::now();
    time = end - begin;

    printSolution();
    printTime();
}

Instance::Instance(std::list<std::tuple<int, int, int> > cities)
{
    using clock = std::chrono::high_resolution_clock;

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

    auto begin = clock::now();
    prepareTree(costMatrix);
    auto end = clock::now();
    time = end - begin;
}

Instance::Instance(std::vector<std::vector<int> > costMatrix)
{
    using clock = std::chrono::high_resolution_clock;

    for (int i = 0; i < costMatrix.size(); ++i)
    {
        costMatrix[i][i] = intMax;
    }
    auto begin = clock::now();
    prepareTree(costMatrix);
    auto end = clock::now();
    time = end - begin;
}

void Instance::printSolution()
{
    std::cout << std::endl;
    std::cout << "Cost: " << minCost << std::endl;
    std::cout << std::endl;

    bestPath.push_back(0);
    std::cout << "Path: ";

    for (const auto& e : bestPath)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void Instance::printTime()
{
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << "ns ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "ms ";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(time).count() << "s" << std::endl;
}

std::list<std::tuple<int, int> > Instance::getValues(std::vector<std::vector<int> >& matrix, std::vector<int>& path) const
{
    std::list<std::tuple<int, int> > values;
    for (int i = 0; i < matrix.size(); ++i)
    {
        if (std::find(path.begin(), path.end(), i) == path.end())
        {
            for (int j = 0; j < matrix.size(); ++j)
            {
                if ((std::find(path.begin(), path.end(), j) == path.end()) && matrix[i][j] != intMax)
                {
                    values.push_back(std::make_tuple(matrix[i][j], j));
                }
            }
        }
    }
    return values;
}

int Instance::getLowerBound(std::vector<std::vector<int> >& matrix, std::vector<int>& path, const int cost) const
{
    int count = 0;
    int lowerBound = cost;
    std::list<std::tuple<int, int> > minCosts;
    minCosts = getValues(matrix, path);
    minCosts.sort();
    while (!minCosts.empty())
    {
        lowerBound += std::get<0>(minCosts.front());
        int city = std::get<1>(minCosts.front());
        minCosts.remove_if([&city](const auto& e1)
        {
            return std::get<1>(e1) == city;
        });
    }
    return lowerBound;
}

void Instance::prepareTree(std::vector<std::vector<int> >& matrix)
{
    std::vector<int> path;
    path.reserve(matrix.size());
    path.push_back(0);
    Node root{ path, 0 };
    branchAndBound(matrix, root);
}

void Instance::branchAndBound(std::vector<std::vector<int> >& matrix, Node& node)
{
    if (node.currentPath.size() == matrix.size())
    {
        node.cost += matrix[node.currentPath.back()][0];
        if (node.cost < minCost)
        {
            minCost = node.cost;
            bestPath = node.currentPath;
        }
        return;
    }
    std::vector<Node> nodes;
    nodes.reserve(matrix.size() - 1);
    for (int i = 1; i < matrix.size(); ++i)
    {
        if (std::find(node.currentPath.begin(), node.currentPath.end(), i) == node.currentPath.end())
        {
            int cost = node.cost + matrix[node.currentPath.back()][i];
            //if (cost < minCost)
            if (getLowerBound(matrix, node.currentPath, node.cost) < minCost)
            {
                nodes.emplace_back(node.currentPath, i);
                nodes.back().currentPath.push_back(i);
                nodes.back().cost = cost;
            }
        }
    }
    for (auto& next : nodes)
    {
        branchAndBound(matrix, next);
    }
}

int Instance::calculateBruteForce(std::vector<std::vector<int> >& matrix, std::vector<int>& path) const
{
    int cost = 0;
    cost += matrix[0][path.front()];
    for (int i = 0; i < path.size() - 1; ++i)
    {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path.back()][0];
    return cost;
}

void Instance::bruteForce(std::vector<std::vector<int> >& matrix)
{
    bestPath.clear();
    minCost = intMax;
    std::vector<int> path;
    path.reserve(matrix.size());
    for (int i = 1; i < matrix.size(); ++i)
    {
        path.push_back(i);
    }
    do
    {
        int cost = calculateBruteForce(matrix, path);
        if (cost < minCost)
        {
            minCost = cost;
            bestPath = path;
        }
    } while (std::next_permutation(path.begin(), path.end()));
}
