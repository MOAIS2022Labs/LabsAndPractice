#include "TrieTree.h"

TrieTree::TrieTree()
{
    root = nullptr;
}

TrieTree::TrieTree(const std::string& fname)
{
    root = nullptr;
    std::ifstream file(fname);
    if (file)
    {
        std::string word;
        while (file >> word)
            add(word);
    }
    else
        std::cout << "Ошибка чтения файла\n";
    file.close();
}

TrieTree::~TrieTree()
{
    clear(root);
}

bool TrieTree::empty()
{
    return !root || root->count == 0;
}

void TrieTree::clear()
{
    clear(root);
}

void TrieTree::clear(Tree& root)
{
    for (size_t i = 0; i < 26; ++i)
        if (root->ptrs[i])
            clear(root->ptrs[i]);
    delete root;
    root = nullptr;
}

void TrieTree::add(const std::string& word)
{
    add_word(root, word, 0);
}

void TrieTree::del(const std::string& word)
{
    del_word(root, word, 0);
}

void TrieTree::add_word(Tree& root, const std::string& word, size_t i)
{
    if (!root)
        root = new NODE;
    if (word.length() - 1 < i)
        root->eow = true;
    else
    {
        if (!root->ptrs[word[i] - 'a'])
            ++root->count;
        add_word(root->ptrs[word[i] - 'a'], word, i + 1);
    }
}

bool TrieTree::all_ptrs_empty(const Tree& root)
{
    bool result = true;
    size_t i = 0;
    while (i < 26 && result)
    {
        if (!root->ptrs[i])
            ++i;
        else
            result = false;
    }
    return result;
}

void TrieTree::del_word(Tree& root, const std::string& word, size_t i)
{
    if (root)
    {
        if (i <= word.length() - 1)
            del_word(root->ptrs[word[i] - 'a'], word, i + 1);
        else
        {
            root->eow = false;
            --root->count;
            if (all_ptrs_empty(root))
            {
                delete root;
                root = nullptr;
            }
        }
    }
}

void TrieTree::print(const Tree& root, std::string word)
{
    if (root)
    {
        if (root->eow)
            std::cout << word << '\n';
        for (size_t i = 0; i < 26; ++i)
            if (root->ptrs[i])
                print(root->ptrs[i], word + char(i + 'a'));
    }
}

void TrieTree::print_los(const Tree& root)
{
    std::cout << find_los(root) << '\n';
}

std::string TrieTree::find_los(const Tree& root)
{
    std::string word = "";
    if (root)
    {
        if (root->eow)
            word += '.';
        for (size_t i = 0; i < 26; ++i)
            if (root->ptrs[i])
                word += char(i + 'a') + find_los(root->ptrs[i]);
    }
    return word;
}

Tree TrieTree::get_root()
{
    return root;
}

void TrieTree::set_root(Tree source)
{
    root = source;
}

void TrieTree::del_words_with_letters(Tree& t, const std::string& set, std::string word)
{
    if (t)
    {
        for (size_t i = 0; i < 26; ++i)
        {
            if (t->ptrs[i])
            {
                word += char(i + 'a');
                size_t c = set.find(char('a' + i));
                if (c == std::string::npos)
                {
                    del_words_with_letters(t->ptrs[i], set, word);
                }
                else
                {
                    if (word.length() > 0 && word.find_first_not_of(set) == std::string::npos)
                    {
                        del_word(t, word);
                    }
                }
            }
        }
    }
}

void TrieTree::del_with_letters(const std::string& set)
{
    del_words_with_letters(root, set);
}
