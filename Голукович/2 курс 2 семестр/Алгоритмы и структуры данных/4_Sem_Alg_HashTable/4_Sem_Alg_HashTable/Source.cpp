#include "HashTableInt.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::ifstream file("test.txt", std::ios::in);
    if (file)
    {
        HashTableInt HT(3);
        HT.Fill(file);
        HT.Print();
    }
    return 0;
}