#include "Parser.h"
#include "Instance.h"

#include <iostream>

int main(int argc, char** argv)
{
    char choice;
    std::string filename;
    do
    {
        std::cout << "1. Test using matrix." << std::endl;
        std::cout << "2. Test using EUC_2D list." << std::endl;
        std::cout << "3. Test using default constructor." << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case '1':
        {
            try
            {
                std::cout << "Filename: \n";
                std::cin >> filename;

                Parser parser;
                parser.loadCitiesMatrix(filename);
                Instance instance(parser.getcitiesMatrix());
                instance.printSolution();
                instance.printTime();
            }
            catch (const std::runtime_error& ex)
            {
                std::cout << ex.what() << std::endl;
            }
            break;
        }
        case '2':
        {
            try
            {
                std::cout << "Filename: \n";
                std::cin >> filename;

                Parser parser;
                parser.loadCitiesList(filename);
                Instance instance(parser.getCitiesList());
                instance.printSolution();
                instance.printTime();
            }
            catch (const std::runtime_error& ex)
            {
                std::cout << ex.what() << std::endl;
            }
            break;
        }
        case '3':
        {
            Instance instance;
            break;
        }
        default:
            break;
        }
    } while (choice != '0');

    return 0;
}