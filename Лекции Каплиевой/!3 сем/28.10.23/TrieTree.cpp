#include "TrieTree.h"

/*
ЗАДАЧИ НА ПРАКТИКУ:
1 задача: добавить метод, который будет печатать не слова дерева, а его лозы.
добавить функцию поиска слова как метод.

2 задача: посторить копию дерева (в task).

3 задача: а) посчитать общее количество слов в дереве.
б) Посчитать количество слов в дереве, содержащую заданную подстроку.
*/

int main()
{
    std::ifstream file("words.txt");
    TrieTree root{};
    init(root);
    std::string word;
    while (std::getline(file, word))
    {
        if (word.length())
            add(root, word, 0);
    }

    std::ofstream fout("tree.txt");
    print(root, "", fout);
    fout.close();
    std::cin.get();
    return 0;
}