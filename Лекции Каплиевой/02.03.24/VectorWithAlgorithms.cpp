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

void printF(ELEM elem)
{
    std::cout << elem.x << " (" << elem.ch << ")\n";
}

struct print // функтор - объект, который ведёт себя как функция
{
    void operator() (ELEM elem) const // переопредялет оператор "круглые скобки"
    {
        std::cout << elem.x << " (" << elem.ch << ")\n";
    }
};

int main()
{
    /*
    1. Вектор можно создать пустой.
    2. Его можно заполнить проинициализированными значениями (универсальный метод).
    3. Можно проинициализировать объектами другого вектора.

    Есть класс содержит в полях строчку (std::string) или вектор и мы пишем конструктор,
    то здесь происходит копирование из внешней программы.
    Рекомендуется в таком случае передавать через move. Тогда не происходит копирование,
    строчка получает указатель внутри класса и передаются права владения на объект.
    */

   

    Vector vect = {ELEM(1, 'a'), {2, 'b'}, {3, 'c'}};

    for (auto elem : vect)
        elem.print();
    std::cout << "-------------------\n";

    /*
    К итераторам применимы только две операции: инкремент и декремент.
   */

    // классический способ обхода через итераторы
    for (Iterator it = vect.begin(); it != vect.end(); it++) // end - это элемент послед последнего элемента, т.е. несущесвтующий элемент коллекции
    {
        (*it).print(); // опреация разыменовывания имеет высокий приоритет. поэтому берём её в скобки   
    }

    // второй вариант: for (Iterator it = next(vect.begin()); it != vect.end(); it++) // - обойдёт коллекцию со второго элемента и до конца


    // третий вариант - библиотечный
    // данный аолгритм является наследием языка СИ, поэтому метод класса передать нельзя
    std::for_each(vect.begin(), vect.end(), printF); // вариант 1: передать функцию
    std::for_each(vect.begin(), vect.end(), print()); // вариант 2: передать функтор
    std::for_each(vect.begin(), vect.end(), ELEM()); // вариант 3: передать внешний функтор
    std::for_each(vect.begin(), vect.end(), std::mem_fn(&ELEM::print)); // вариант 4: передаём имя функции - адрес, где хранится эта функция
    // обёртка класса memory function обратится к указателю метода print

    auto prnt = std::bind(&ELEM::print, std::placeholders::_1); 
    std::for_each(vect.begin(), vect.end(), prnt);// вариант 5: через bind 
    // обёртка bind принимает либо функтор, либо метод, либо функцию (всё то, что можно вызывать)
    // и возвращает указатель на указанную функцию; второй аргумент говорит о том, сколько в функции принимается параметров
    /*
    auto function_ref = std::bind(func, _3, _2, _1); // - с помощью bind можно ещё изменить порядок аргументов функции 
    */
    auto printL = [](ELEM elem){std::cout << elem.x << " (" << elem.ch << ")\n";};
    std::for_each(vect.begin(), vect.end(), printL); // вариант 6: через лямбда-функцию

    std::cin.get();
    return 0;
}