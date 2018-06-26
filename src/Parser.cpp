#include "Parser.hpp"

#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<std::vector<int> > Parser::getCitiesMatrix() const
{
    return citiesMatrix;
}

void Parser::convertToMatrix()
{
    std::vector<std::vector<int> > matrix(citiesList.size(), std::vector<int>(citiesList.size()));
    int x, y;
    auto it1 = citiesList.begin();
    auto it2 = citiesList.begin();
    for (int i = 0; i < citiesList.size(); ++i, ++it1)
    {
        it2 = citiesList.begin();
        for (auto k = 0; k < citiesList.size(); ++k, ++it2)
        {
            x = std::get<1>(*it1) - std::get<1>(*it2);
            y = std::get<2>(*it1) - std::get<2>(*it2);
            matrix[i][k] = (std::lround(std::sqrt((x * x + y * y))));
        }
    }
    citiesMatrix = std::move(matrix);
}

bool Parser::loadCitiesList(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    std::string line;
    int cityNumber, firstCoordinate, secondCoordinate;
    while (file.good())
    {
        file >> line;
        if (line == "NODE_COORD_SECTION")
        {
            break;
        }
    }
    for (;;)
    {
        file >> cityNumber >> firstCoordinate >> secondCoordinate;
        if (!file.good())
        {
            break;
        }
        citiesList.push_back(std::make_tuple(cityNumber, firstCoordinate, secondCoordinate));
    }
    convertToMatrix();
    return true;
}

bool Parser::loadCitiesMatrix(const std::string& filename)
{
    int dimension = 0;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    std::string line;
    file >> dimension;
    citiesMatrix.resize(dimension);
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            file >> line;
            citiesMatrix[i].push_back(std::stoi(line));
        }
    }
    return true;
}

bool Parser::loadLowerDiagonalRow(const std::string & filename)
{
    int dimension = 0;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    std::string line;
    file >> dimension;
    citiesMatrix.resize(dimension);
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < (i + 1); ++j)
        {
            file >> line;
            citiesMatrix[i].push_back(std::stoi(line));
        }
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = i + 1; j < dimension; ++j)
        {
            citiesMatrix[i].push_back(citiesMatrix[j][i]);
        }
    }
    return true;
}
