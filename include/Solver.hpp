#pragma once

#include <vector>
#include <chrono>

#include "Instance.hpp"
#include "Node.hpp"

class Solver
{
public:
    explicit Solver(std::vector<std::vector<int>> costMatrix);
    void run();
    void printSolution();
private:
    std::vector<bool> getVisited(const std::vector<int>& path) const;
    std::vector<int> getValues(const std::vector<int>& path) const;
    int getLowerBound(const std::vector<int>& path, int cost) const;
    void branchAndBound(Node& node);

    Instance instance;
    std::chrono::duration<double> elapsedTime;
};
