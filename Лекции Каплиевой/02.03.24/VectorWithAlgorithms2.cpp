#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

struct ELEM
{
    int x;
    char ch;
    ELEM() {}
    ELEM(int x, char ch) : x(x), ch(ch) {}
    void print()
    {
        std::cout << x << " (" << ch << ")\n";
    }
};

using Vector = std::vector<ELEM>;
using Iterator = Vector::iterator;
using IterList = std::list<ELEM>::iterator;

int main()
{

    Vector vect = {new ELEM(1, 'a'), new ELEM(2, 'b'), ELEM{3, 'c'}};
    vect.push_back(new ELEM(4, 'd'));

    auto compareL = [](const ELEM &a, const ELEM &b)
    { return a.ch > b.ch; };
    std::sort(std::begin(vect), std::end(vect), compareL); // begin и end могут быть функциями библиотеки algorithm

    for (Iterator it = vect.begin(); it != vect.end();)
        if (it->x % 2 == 0)
            it = vect.erase(it);
        else
            ++it;

    // В случае контейнера list
    std::list<ELEM> list = {{1,'a'}, {2,'b'}, {3,'c'}};
    auto is_delete = [](ELEM elem)
    {
        return elem.x % 2 == 0;
    };
    list.remove_if(is_delete);

    // в случае вектора
    Vector vector = {{1,'a'}, {2,'b'}, {3,'c'}};
    Iterator del = std::remove_if(vector.begin(), vector.end(), is_delete); // метод вернул итератор на ту область, с которой начинается несоответствие заданному условию
    vector.erase(del, vector.end()); // удаляем все нечётные числа, которые оказались в конце вектора


    std::cin.get();
    return 0;
}