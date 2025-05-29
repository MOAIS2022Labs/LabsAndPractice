#include "IOlib.h"

std::string input(const char* message)
{
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::string result{};
    std::cout << message << "\n>>> ";
    std::getline(std::cin, result);
    return result;
}

ushort menu(const char* message, const ushort choice_count)
{
    std::cout << message;
    short res{};
	validation(res, [choice_count](short x) { return x > 0 && x <= choice_count; }, "");
    return res;
}

short check_file(std::fstream& file)
{
    short res = 1;
    if (!file)
    {
        res = -1; // file not found
    }
    else
        if (file.peek() == EOF)
            res = 0; // file is empty
    return res;
}
