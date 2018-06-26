#pragma once

#include <string>
#include <list>
#include <vector>
#include <tuple>

class Parser
{
public:
    Parser() = default;
    std::vector<std::vector<int>> getCitiesMatrix() const;

    void loadCitiesList(const std::string& filename);
    void loadCitiesMatrix(const std::string& filename);
    void loadLowerDiagonalRow(const std::string& filename);
private:
    void skipToCoordinates(std::ifstream& file) const;
    std::vector<std::vector<int>> convertToMatrix(const std::list<std::tuple<int, int, int>>& citiesList);

    std::vector<std::vector<int>> citiesMatrix;
};
