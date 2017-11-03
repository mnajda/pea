#include "Instance.h"

#include <iostream>

Instance::Instance()
{
    using clock = std::chrono::high_resolution_clock;

    /*std::vector<std::vector<int> > costMatrix = { { intMax, 14, 4, 10, 20 },
                                                    { 14, intMax, 7,  8,  7 },
                                                    { 4, 5, intMax,  7,  16 },
                                                    { 11, 7,  9, intMax,  2 },
                                                    { 18, 7, 17,  4, intMax } };*/

    /*std::vector<std::vector<int> > costMatrix = { {intMax, 3, 4, 2, 7 },
                                                    { 3, intMax, 4, 6, 3},
                                                    { 4, 4, intMax, 5, 8},
                                                    { 2, 6, 5, intMax, 6},
                                                    { 7, 3, 8, 6, intMax} };*/

    /*std::vector<std::vector<int> > costMatrix = { { intMax, 10, 8, 9, 7  },
                                                    { 10, intMax, 10, 5, 6 },
                                                    { 8, 10, intMax, 8, 9  },
                                                    { 9, 5, 8, intMax, 6   },
                                                    { 7, 6, 9, 6, intMax   } };*/

    /*std::vector<std::vector<int> > costMatrix = { { intMax, 3, 1, 5, 8 },
                                                    { 3, intMax, 6, 7, 8 },
                                                    { 1, 6, intMax, 4, 2 },
                                                    { 5, 7, 4, intMax, 3 },
                                                    { 8, 9, 2, 3, intMax } };*/

    std::vector<std::vector<int> > costMatrix = { {intMax, 3, 93, 13, 33, 9, 57  },
                                                  {4, intMax, 77, 42, 21, 16, 34 },
                                                  {45, 17, intMax, 36, 16, 28, 25},
                                                  {39, 90, 80, intMax, 56, 7, 91 },
                                                  {28, 46, 88, 33, intMax, 25, 57},
                                                  {3, 88, 18, 46, 92, intMax, 7  },
                                                  {44, 26, 33, 27, 84, 39, intMax} };

    /*std::vector<std::vector<int> > costMatrix = { { intMax, 3, 5, 48, 48, 8, 8, 5, 5, 3, 3, 0, 3, 5, 8, 8, 5          },
                                                    { 3, intMax, 3, 48, 48, 8, 8, 5, 5, 0, 0, 3, 0, 3, 8, 8, 5          },
                                                    { 5, 3, intMax, 72, 72, 48, 48, 24, 24, 3, 3, 5, 3, 0, 48, 48, 24   },
                                                    {48, 48, 74, intMax, 0, 6, 6, 12, 12, 48, 48, 48, 48, 74, 6, 6, 12  },
                                                    {48, 48, 74, 0, intMax, 6, 6, 12, 12, 48, 48, 48, 48, 74, 6, 6, 12  },
                                                    { 8, 8, 50, 6, 6, intMax, 0, 8, 8, 8, 8, 8, 8, 50, 0, 0, 8          },
                                                    { 8, 8, 50, 6, 6, 0, intMax, 8, 8, 8, 8, 8, 8, 50, 0, 0, 8          },
                                                    { 5, 5, 26, 12, 12, 8, 8, intMax, 0, 5, 5, 5, 5, 26, 8, 8, 0        },
                                                    { 5, 5, 26, 12, 12, 8, 8, 0, intMax, 5, 5, 5, 5, 26, 8, 8, 0        },
                                                    { 3, 0, 3, 48, 48, 8, 8, 5, 5, intMax, 0, 3, 0, 3, 8, 8, 5          },
                                                    { 3, 0, 3, 48, 48, 8, 8, 5, 5, 0, intMax, 3, 0, 3, 8, 8, 5          },
                                                    { 0, 3, 5, 48, 48, 8, 8, 5, 5, 3, 3, intMax, 3, 5, 8, 8, 5          },
                                                    { 3, 0, 3, 48, 48, 8, 8, 5, 5, 0, 0, 3, intMax, 3, 8, 8, 5          },
                                                    { 5, 3, 0, 72, 72, 48, 48, 24, 24, 3, 3, 5, 3, intMax, 48, 48, 24   },
                                                    { 8, 8, 50, 6, 6, 0, 0, 8, 8, 8, 8, 8, 8, 50, intMax, 0, 8          },
                                                    { 8, 8, 50, 6, 6, 0, 0, 8, 8, 8, 8, 8, 8, 50, 0, intMax, 8          },
                                                    { 5, 5, 26, 12, 12, 8, 8, 0, 0, 5, 5, 5, 5, 26, 8, 8, intMax        }  };*/

    auto begin = clock::now();
    prepareTree(costMatrix);
    auto end = clock::now();
    time = end - begin;
}

Instance::Instance(std::list<std::tuple<int, int, int>> cities)
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

void Instance::printSolution()
{
    std::cout << minCost << std::endl;
    std::cout << std::endl;

    bestPath.push_back(0);

    for (const auto& e : bestPath)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void Instance::printTime()
{   
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << "ns" << std::endl;
    std::cout << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() / 1000.0f << "ms" << std::endl;
    std::cout << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(time).count() / 60.0f << "min" << std::endl;
    std::cout << std::endl;
}

int Instance::calculateLowerBound(std::vector<std::vector<int> >& matrix, std::vector<int>& path) const
{
    int lowerBound = 0;
    for (int i = 0; i < path.size() - 1; ++i)
    {
        lowerBound += matrix[path[i]][path[i + 1]];
    }
    if (path.size() == matrix.size())
    {
        lowerBound += matrix[path.back()][0];
    }
    return lowerBound;
}

void Instance::prepareTree(std::vector<std::vector<int> >& matrix)
{
    std::vector<int> path;
    path.push_back(0);
    Node root{ path, 0 };
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
            Node newNode{ node.currentPath, i };
            newNode.currentPath.push_back(i);
            nodes.push_back(newNode);
        }
    }
    for (const auto& next : nodes)
    {
        branchAndBound(matrix, next);
    }
}
