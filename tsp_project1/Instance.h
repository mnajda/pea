#pragma once

#include <vector>
#include <list>
#include <tuple>
#include <numeric>

struct Node
{
    std::vector<std::vector<int> > matrix;
    int city;
    int lowerBound = 0;
    Node(std::vector<std::vector<int> > inputMatrix, int inputCity) : matrix(inputMatrix),
                                                                      city(inputCity)
    {}
};

class Instance
{
public:
    Instance();
    Instance(std::list<std::tuple<int, int, int> > cities);
    int getCost();
private:
    int minRow(std::vector<std::vector<int> >& matrix, const int row);
    int minCol(std::vector<std::vector<int> >& matrix, const int col);
    int reduceRows(std::vector<std::vector<int> >& matrix);
    int reduceColumns(std::vector<std::vector<int> >& matrix);
    int reduceMatrix(std::vector<std::vector<int> >& matrix);
    void removePaths(std::vector<std::vector<int> >& matrix, const int row, const int col);
    void createTree(std::vector<std::vector<int> > costMatrix);
    void branchAndBound(std::vector<std::vector<int> > matrix,
                        std::vector<Node>& currentLevel,
                        std::vector<int>& path,
                        std::vector<int>& visited,
                        int previousLowerBound,
                        int level);

    std::vector<int> bestPath;
    std::vector<std::tuple<int, std::vector<int> > > bestPaths;
    static constexpr int intMax = std::numeric_limits<int>::max();
    int minCost = 0;
};