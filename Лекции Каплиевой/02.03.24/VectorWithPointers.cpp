#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

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
    void operator()(ELEM elem) const
    {
        std::cout << x << " (" << ch << ")\n";
    }
};

using Vector = std::vector<ELEM>;
using uptr = std::unique_ptr<int>;

template <class TIterator, class TPredicate>
TIterator my_remove_if(TIterator first, TIterator last, TPredicate condition) // работа для метода remove_if
{
    for (TITerator it = first, it != last; ++it)
    {
        if (!condition(*it))
        {
            *first = std::move(*it);
            first++;
        }
    }
    return first;
}

int main()
{
    Vector vector = {{1, 'a'}, {2, 'b'}, {3, 'c'}};


    std::cin.get();
    return 0;
}