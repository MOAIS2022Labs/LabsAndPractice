#include <stack>
#include <queue>
#include "Btree.h"
// #2
int Count_evenRec(Tree root)
{
    int result = 0;
    if (root)
        result = (root->info % 2 == 0 ? 1 : 0) +
                 Count_evenRec(root->left) +
                 Count_evenRec(root->right);
    return result;
}

int Count_evenStack(Tree root)
{
    std::stack<Tree> st;
    int result = 0;
    Tree t = root;
    bool stop = false;
    // bool stop = t? 1 : 0;
    // bool stop = t;
    while (!stop) // while(t)
    {
        if (t->info % 2 == 0)
            ++result;
        if (t->left)
        {
            if (t->right)
                st.push(t->right);
            t = t->left;
        }
        else if (t->right)
            st.push(t->right);
        else if (!st.empty())
        {
            t = st.top();
            st.pop();
        }
        else
        {
            stop = true;
            // t = nullptr;
        }
    }
    return result;
}

int Count_EvenQueue(Tree root)
{
    int result = 0;
    std::queue<Tree> q;
    Tree t;
    q.push(root);
    while (!q.empty())
    {
        t = q.front();
        q.pop();
        if (t->info % 2 == 0)
            ++result;
        if (t->left)
            q.push(t->left);
        if (t->right)
            q.push(t->right);
    }
    return result;
}
// #3
// bool IsLeaf(Tree root)
// {
//     return !(root->left) && !(root->right);
// }

Tree Copy(Tree root)
{
    Tree result = nullptr;
    if (root /*&& !IsLeaf(root)*/)
    {
        result = new NODE(root->info);
        result->left = Copy(root->left);
        result->right = Copy(root->right);
    }
    return result;
}

int main()
{
    // № 1 вывод идеально сбалансированного дерева
    std::ifstream file("data.txt");
    if (file)
    {
        int n;
        file >> n;
        Tree root = Build_Balance(n, file);
        Print(root, 0);

        // № 2 вычислить количество чётных элементов в дереве

        // Метод обхода в глубину
        // Рекурсивный способ:
        // std::cout<<Count_evenRec(root)<<'\n';
        // Нерекурсивный способ (через стек):
        // std::cout << Count_evenStack(root)<<'\n';

        // Метод обхода в ширину (по слоям)
        // std::cout<<Count_EvenQueue(root)<<'\n';


    
    /*№ 3 Посторить копию дерева без листьев (отсечь последний ярус).
    Это означает получить новую структуру.
    */
    Tree copy_tree = Copy(root);
    Print(copy_tree, 0);
    Clear(root);
    }
    

    std::cin.get();
    return 0;
}