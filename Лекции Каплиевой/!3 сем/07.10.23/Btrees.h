#pragma once
#include <iostream>
#include <fstream>
using TInfo = int;

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

void Add(Tree& root, TInfo elem)
{
    if (!root)
        root = new NODE(elem);
    else if (elem > root->info)
        Add(root->right, elem);
    else if (elem < root->info)
        Add(root->left, elem);
    else 
        ++root->count;
}   

// Нерекурсвиный метод, вызывающий рекурсивную функцию
Tree Build_Search(std::ifstream &file)
{
    TInfo elem;
    Tree result = nullptr;
    while (file>>elem)
        Add(result, elem);
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
            std::cout << "     ";
        std::cout<<root->info<<'\n';
        Print(root->left, level+1);
    }
}

// Нерекурсивный поиск элемента в дереве поиска
Tree Search(const Tree& root, TInfo elem)
{
    Tree t = root, result = nullptr;
    while (t && !result)
    {
        if (elem < t->info)
            t = t->left;
        else if (elem > t->info)
            t = t->right;
        else
            result = t;
    }
    return result;
}

void Find_element(Tree& r, Tree& q) // r - где ищем, q - что удаляем 
{
    if (r->right)
        Find_element(r->right, q);
    else
    {
        q->info = r->info;
        q->count = r->count;
        q = r;
        r = r->left;
    }
}


// Лексикографическое удаление элемента
bool Delete_element(Tree& root, TInfo elem)
{
    bool result = false;
    if (root)
    {
        if (elem < root->info)
            result = Delete_element(root->left, elem);
        else if (elem > root->info)
            result = Delete_element(root->right, elem);
        else
            {
                result = true;
                if (root->count > 1)
                    --root->count;
                else
                {
                    Tree q = root;
                    if (!q->right)
                        root = q->left;
                    else if (!q->left)
                        root = q->right; // root->right??
                    else
                        Find_element(q->left, q);
                    delete q;
                }
            }
    }
    return result;
}