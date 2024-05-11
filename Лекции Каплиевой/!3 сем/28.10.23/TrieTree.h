
#include <iostream>
#include <fstream>
#include <string>

struct Node
{
    bool eow = false; // end of word
    Node *ptrs[26];
    Node()
    {
        for (size_t i = 0; i < 26; ++i)
            ptrs[i] = nullptr;
    }
};

using TrieTree = Node *;

void init(TrieTree &root)
{
    root = nullptr;
}

bool empty(const TrieTree &root)
{
    return root == nullptr;
}

void add(TrieTree &root, const std::string word, size_t i)
{
    if (!root)
        root = new Node;
    if (word.length() - 1 < i)
        root->eow = true;
    else
        add(root->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptrs_empty(TrieTree root)
{
    bool result = true;
    size_t i = 0;
    while (i < 26 && result)
        if (!root->ptrs[i])
            ++i;
        else
            result = false;
    return result;
}

void del(TrieTree &root, const std::string word, size_t i)
{
    if (root)
    {
        if (i <= word.length() - 1)
            del(root->ptrs[word[i] - 'a'], word, i + 1);
        else
        {
            root->eow = false;
            if (all_ptrs_empty(root))
            {
                delete root;
                root = nullptr;
            }
        }
    }
}

void print(TrieTree root, std::string word, std::ostream& os)
{
    if (root->eow)
        os << word +'\0'<< '\n';
    for (size_t i = 0; i < 26; ++i)
        if (root->ptrs[i])
            print(root->ptrs[i], word + char(i + 'a'), os);
}

void clear(TrieTree &root)
{   // if (root) {
    for (size_t i = 0; i < 26; ++i)
        if (root->ptrs[i]) // описывается без внешнего условия if(root)
            clear(root->ptrs[i]);
    delete root;
    root = nullptr;
    //}
}