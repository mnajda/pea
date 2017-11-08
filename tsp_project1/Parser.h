#pragma once

#include <string>
#include <list>
#include <vector>
#include <tuple>

class Parser
{
public:
    Parser();
    std::list<std::tuple<int, int, int> > getCitiesList() const;
    std::vector<std::vector<int> > getCitiesMatrix() const;
    bool loadCitiesList(const std::string& filename);
    bool loadCitiesMatrix(const std::string& filename);
    bool loadLowerDiagonalRow(const std::string& filename);
private:
    std::list<std::tuple<int, int, int> > citiesList;
    std::vector<std::vector<int> > citiesMatrix;
};