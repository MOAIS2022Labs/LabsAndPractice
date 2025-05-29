#pragma once
#include <iostream>
#include <fstream>
#include <string>


using uint = unsigned int;
using ushort = unsigned short;


template<typename T, typename Predicate>
void validation(T& x, Predicate condition, const char* message)
{
    std::cout << message << "\n>>> ";
    while (!(std::cin >> x && condition(x)))
    {
        std::cout << "Input error!" << '\n';
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << message << "\n>>> ";
    }
}

std::string input(const char* message = "");

ushort menu(const char* message = "", const ushort choice_count = 1);

short check_file(std::fstream& file);
