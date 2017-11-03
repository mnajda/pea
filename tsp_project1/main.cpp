#include "Parser.h"
#include "Instance.h"

#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        Parser parser("eil51.tsp");

        //Instance instance(parser.getCities());
        Instance instance;
        instance.printSolution();
        instance.printTime();
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    system("pause");

    return 0;
}