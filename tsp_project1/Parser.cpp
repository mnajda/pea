#include "Parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

Parser::Parser(const std::string& filename)
{
    if (!loadDataFromFile(filename))
    {
        throw std::invalid_argument("Can't load from file");
    }
}

std::list<std::tuple<int, int, int> > Parser::getCities() const
{
    return cities;
}

bool Parser::loadDataFromFile(const std::string& filename)
{
    std::ifstream file(filename);
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
        cities.push_back(std::make_tuple(cityNumber, firstCoordinate, secondCoordinate));
    }
    return false;
}