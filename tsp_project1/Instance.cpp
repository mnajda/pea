#include "Instance.h"

#include <functional>
#include <algorithm>
#include <iostream>

Instance::Instance()
{
    std::vector<std::vector<int> > costMatrix = { { intMax, 14, 4, 10, 20 },
                                                  { 14, intMax, 7,  8,  7 },
                                                  { 4, 5, intMax,  7,  16 },
                                                  { 11, 7,  9, intMax,  2 },
                                                  { 18, 7, 17,  4, intMax } };
    /*std::vector<std::vector<int> > costMatrix =
    { { intMax,    3,    5,   48,   48,    8,    8,    5,    5,    3,    3,    0,   3,    5,    8,    8,  5 },
    { 3,    intMax,    3,   48,   48,    8,    8,    5,    5,    0,    0,    3,    0,    3,    8,    8, 5 },
    { 5,    3,  intMax,   72,   72,   48,   48,   24,   24,    3,    3,    5,    3,    0,   48,   48, 24 },
    { 48,   48,   74, intMax,    0,    6,    6,   12,   12,   48,   48,   48,   48,   74,    6 ,   6 ,12 } ,
    { 48,   48,   74,    0, intMax,    6,    6,   12,   12,   48,   48,   48,   48,   74,    6,    6, 12 } ,
    { 8,    8,   50,    6,    6, intMax,    0,    8,    8,    8,    8,    8,    8,   50,    0,    0, 8 } ,
    { 8,    8,   50,    6,    6,    0, intMax,    8,    8,    8,    8,    8,    8,   50,    0,    0, 8 },
    { 5,    5,   26,   12,   12,    8,    8, intMax,    0,    5,    5,    5,    5,   26,    8,    8, 0 } ,
    { 5,    5,   26,   12,   12,    8,    8,    0, intMax,    5,    5,    5,    5,   26,    8,    8, 0 } ,
    { 3,    0,    3,   48,   48,    8,    8,    5,    5, intMax,    0,    3,    0,    3,    8,    8, 5 } ,
    { 3,    0,    3,   48,   48,    8,    8,    5,    5,    0, intMax,    3,    0,    3,    8,    8, 5 } ,
    { 0,    3,    5,   48,   48,    8,    8,    5,    5,    3,    3, intMax,    3,    5,    8,    8, 5 } ,
    { 3,    0,    3,   48,   48,    8,    8,    5,    5,    0,    0,    3, intMax,    3,    8,    8, 5 } ,
    { 5,    3,    0,   72,   72,   48,   48,   24,   24,    3,    3,    5,    3, intMax,   48,   48, 24 } ,
    { 8,    8,   50,    6,    6,    0,    0,    8,    8,    8,    8,    8,    8,   50, intMax,    0, 8 } ,
    { 8,    8,   50,    6,    6,    0,    0,    8,    8,    8,    8,    8,    8,   50,    0, intMax, 8 } ,
    { 5,    5,   26,   12,   12,    8,    8,    0,    0,    5,    5,    5,    5,   26,    8,    8, intMax } };*/

    bestPaths.reserve(costMatrix.size());
    createTree(costMatrix);

    auto bestPath = std::min_element(bestPaths.begin(), bestPaths.end(),
        [](const std::tuple<int, std::vector<int> >& e1, std::tuple<int, std::vector<int> >& e2)
    {
        return std::get<0>(e1) < std::get<0>(e2);
    });
    std::cout << std::get<0>(*bestPath) << std::endl;
    std::cout << std::endl;
    for (const auto& c : std::get<1>(*bestPath))
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

Instance::Instance(std::list<std::tuple<int, int, int> > cities)
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

    bestPaths.reserve(costMatrix.size());
    createTree(costMatrix);

    auto bestPath = std::min_element(bestPaths.begin(), bestPaths.end(),
        [](const std::tuple<int, std::vector<int> >& e1, std::tuple<int, std::vector<int> >& e2)
    {
        return std::get<0>(e1) < std::get<0>(e2);
    });
    std::cout << std::get<0>(*bestPath) << std::endl;
    std::cout << std::endl;
    for (const auto& c : std::get<1>(*bestPath))
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

int Instance::getCost()
{
    return minCost;
}

int Instance::minRow(std::vector<std::vector<int> >& matrix, const int row)
{
    int min = intMax;
    for (int i = 0; i < matrix.size(); ++i)
    {
        min = std::min(min, matrix[row][i]);
    }
    if (min == intMax)
    {
        return 0;
    }
    return min;
}

int Instance::minCol(std::vector<std::vector<int> >& matrix, const int col)
{
    int min = intMax;
    for (int i = 0; i < matrix.size(); ++i)
    {
        min = std::min(min, matrix[i][col]);
    }
    if (min == intMax)
    {
        return 0;
    }
    return min;
}

int Instance::reduceRows(std::vector<std::vector<int> >& matrix)
{
    int rowBound = 0;
    for (int i = 0; i < matrix.size(); ++i)
    {
        int rmin = minRow(matrix, i);
        if (rmin > 0)
        {
            for (int k = 0; k < matrix.size(); ++k)
            {
                if (matrix[i][k] != intMax)
                {
                    matrix[i][k] -= rmin;
                }
            }
            rowBound += rmin;
        }
    }
    return rowBound;
}

int Instance::reduceColumns(std::vector<std::vector<int> >& matrix)
{
    int colBound = 0;
    for (int i = 0; i < matrix.size(); ++i)
    {
        int cmin = minCol(matrix, i);
        if (cmin > 0)
        {
            for (int k = 0; k < matrix.size(); ++k)
            {
                if (matrix[k][i] != intMax)
                {
                    matrix[k][i] -= cmin;
                }
            }
            colBound += cmin;
        }
    }
    return colBound;
}

int Instance::reduceMatrix(std::vector<std::vector<int> >& matrix)
{
    int rowBound = reduceRows(matrix);
    int colBound = reduceColumns(matrix);
    return rowBound + colBound;
}

void Instance::removePaths(std::vector<std::vector<int> >& matrix, const int row, const int col)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        matrix[row][i] = intMax;
        matrix[i][col] = intMax;
    }
    matrix[col][row] = intMax;
}

//void Instance::createTree(std::vector<std::vector<int> > costMatrix)
//{
//    std::vector<std::vector<int> > matrix = costMatrix;
//    std::vector<Node> currentLevel;
//    std::vector<int> visited(matrix.size(), 0);
//    std::vector<int> path;
//    path.push_back(0);
//    visited[0] = 1;
//    int currentLowerBound = reduceMatrix(matrix);
//    branchAndBound(matrix, currentLevel, path, visited, currentLowerBound, 0);
//    bestPath = std::move(path);
//}

void Instance::createTree(std::vector<std::vector<int> > costMatrix)
{
    std::vector<std::vector<int> > matrix = costMatrix;
    std::vector<Node> currentLevel;
    std::vector<int> visited(matrix.size(), 0);
    std::vector<int> path;
    int cost = 0;
    for (int i = 0; i < matrix.size(); ++i)
    {
        cost = 0;
        std::replace(visited.begin(), visited.end(), 1, 0);
        path.clear();
        path.push_back(i);
        visited[i] = 1;
        int currentLowerBound = reduceMatrix(matrix);
        branchAndBound(matrix, currentLevel, path, visited, currentLowerBound, 0);
        for (int k = 0; k < costMatrix.size() - 1; ++k)
        {
            cost += costMatrix[path[k]][path[k + 1]];
        }
        cost += costMatrix[path.back()][i];
        bestPaths.push_back(std::make_tuple(cost, path));
    }
}

void Instance::branchAndBound(std::vector<std::vector<int> > matrix,
                              std::vector<Node>& currentLevel,
                              std::vector<int>& path,
                              std::vector<int>& visited,
                              int previousLowerBound,
                              int level)
{
    currentLevel.clear();
    if (path.size() == matrix.size())
    {
        return;
    }
    int parent = path.back();
    for (int i = 0; i < matrix.size(); ++i)
    {
        if (visited[i])
        {
            continue;
        }
        Node node{ matrix, i };
        if (matrix[parent][i] == intMax)
        {
            node.lowerBound = intMax;
        }
        else
        {
            node.lowerBound = previousLowerBound + matrix[parent][i] + reduceMatrix(node.matrix);
        }
        removePaths(node.matrix, parent, i);
        currentLevel.push_back(node);
    }
    auto lowestCostNodeItr = std::min_element(currentLevel.begin(), currentLevel.end(), [](const Node& e1, const Node& e2)
    {
        return e1.lowerBound < e2.lowerBound;
    });
    path.push_back(lowestCostNodeItr->city);
    visited[lowestCostNodeItr->city] = 1;
    branchAndBound(lowestCostNodeItr->matrix, currentLevel, path, visited, lowestCostNodeItr->lowerBound, ++level);
}
