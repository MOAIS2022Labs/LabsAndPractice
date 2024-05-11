#pragma once
#include <iostream>
#include <fstream>
using TInfo = int;

struct NODE
{
    TInfo info;
    NODE *left, *right;
    NODE() {}
    NODE(TInfo info, NODE *left = nullptr, NODE *right = nullptr)
        : info(info), left(left), right(right) {}
    ~NODE()
    {
        left = nullptr;
        right = nullptr;
    }
};

using Tree = NODE *;

// count - количество узлов
Tree Build_Balance(int count, std::ifstream &file)
{
    Tree result = nullptr;
    if (count)
    {
        int count_left = count / 2;
        int count_right = count - count_left - 1;
        result = new NODE;
        // Постфиксный обход
        file >> result->info;
        result->left = Build_Balance(count_left, file);
        result->right = Build_Balance(count_right, file);
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

void Print(Tree root, int level)
{
    if (root)
    {
        Print(root->right, level + 1);
        for (int i = 1; i <= level; ++i)
            std::cout << ' ';
        std::cout<<root->info<<'\n';
        Print(root->left, level+1);
    }
}