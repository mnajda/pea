#pragma once

#include <vector>

struct Node
{
    std::vector<int> currentPath;
    int city;
    int cost{0};
    Node(const std::vector<int>& path, int thisCity)
            : currentPath(path)
            , city(thisCity)
    {
    }
};
