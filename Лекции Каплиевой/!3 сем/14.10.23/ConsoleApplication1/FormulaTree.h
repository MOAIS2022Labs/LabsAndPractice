#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <queue>
/*
НА ЭКЗАМЕН:
В библиотеке должен быть конструктор, в котором будем строить
дерево из файла.
Должен быть деструктор, который будет использовать метод clear().
Также должны быть get и set
в привате описан root - корень дерева.
информационная часть описывается вне дерева (TInfo).
*/

using TInfo = char;

struct NODE
{
    TInfo info;
    int count = 1;
    NODE *left, *right;
    NODE() {}
    NODE(TInfo info, int count = 1, NODE *left = nullptr, NODE *right = nullptr)
        : info(info), left(left), right(right) {}
    ~NODE()
    {
        left = nullptr;
        right = nullptr;
    }
};

using Tree = NODE *;

Tree Build_Formula(std::ifstream& file)
{
    char c = file.get();
    Tree result = new NODE(' ');
    if (c >= '0' && c <= '9')
        result->info = c;
    else
    {
        // c ='('
        result->left = Build_Formula(file);
        result->info = file.get();
        result->right = Build_Formula(file);
        c = file.get();
    }
    return result;
}

int Calculate(const Tree &root)
{
    int result = 0;
    if (!root->left && !root->right)
        result = root->info - '0';
    else
    {
        int left_form = Calculate(root->left);
        int right_form = Calculate(root->right);
        switch (root->info)
        {
        case '+':
            result = left_form + right_form;
            break;
        case '-':
            result = left_form - right_form;
            break;
        case '*':
            result = left_form * right_form;
            break;
        }
    }
    return result;
}

void Clear(Tree &root)
{
    if (root)
    {
        Clear(root->left);
        Clear(root->right);
        delete root;
        root = nullptr;
    }
}

std::string Print_to_string(const Tree &root)
{
    std::string result = "";
    if (!root->left && !root->right)
        result += root->info;
    else
        result = '(' + Print_to_string(root->left) + root->info +
                 Print_to_string(root->right) + ')';
    return result;
}

void Print(Tree root, int level)
{
    if (root)
    {
        Print(root->right, level + 1);
        for (int i = 1; i <= level; ++i)
            std::cout << "     ";
        std::cout << root->info << '\n';
        Print(root->left, level + 1);
    }
}
