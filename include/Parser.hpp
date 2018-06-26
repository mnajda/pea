#pragma once

#include <string>
#include <list>
#include <vector>
#include <tuple>

class Parser
{
public:
    Parser() = default;
    std::vector<std::vector<int> > getCitiesMatrix() const;
    void convertToMatrix();
    bool loadCitiesList(const std::string& filename);
    bool loadCitiesMatrix(const std::string& filename);
    bool loadLowerDiagonalRow(const std::string& filename);
private:
    std::list<std::tuple<int, int, int> > citiesList;
    std::vector<std::vector<int> > citiesMatrix;
};