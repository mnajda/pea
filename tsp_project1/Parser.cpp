#include "Parser.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

Parser::Parser()
{
}

std::list<std::tuple<int, int, int> > Parser::getCitiesList() const
{
    return citiesList;
}

std::vector<std::vector<int> > Parser::getCitiesMatrix() const
{
    return citiesMatrix;
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
            return true;
        }
        citiesList.push_back(std::make_tuple(cityNumber, firstCoordinate, secondCoordinate));
    }
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
