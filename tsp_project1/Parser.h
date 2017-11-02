#pragma once

#include <string>
#include <list>
#include <tuple>

class Parser
{
public:
    explicit Parser(const std::string& filename);
    std::list<std::tuple<int, int, int> > getCities() const;
private:
    std::list<std::tuple<int, int, int> > cities;
    bool loadDataFromFile(const std::string& filename);
};