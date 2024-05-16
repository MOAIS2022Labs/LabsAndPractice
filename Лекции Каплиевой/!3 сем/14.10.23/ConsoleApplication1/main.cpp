#include "FormulaTree.h"
/*
Дерево-формула
Формула - это либо терминал (в частности, цифры от 0 до 9),
либо в скобках заключенная конструкция : трерминал - знак - терминал.
Знаком могут быть: "+", "-", "*".
По определнию: во внутренних узлах могут лежать только знаки (операции),
в листьях лежат терминалы.
*/


int main()
{
    std::ifstream file("data.txt");
    if (file)
    {
        Tree root = Build_Formula(file);
        Print(root, 0);
        std::cout << Print_to_string(root) << '\n';
        std::cout << Calculate(root);
    }
    std::cin.get();
    return 0;
}