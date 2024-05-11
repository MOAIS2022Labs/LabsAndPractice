/*
Задача: написать класс-обёртку "математический set" (который хранит классический set),
в котором будут 3 основных метода: объединение, пересечение и разность.
*/

/*
Set - это контейнер, который является упорядоченным множестов, хранящим уникальные элементы
Обычный set - хранит уникальные элементы, математических операций (объединение, пересечение и разность) НЕТ.
*/

#include <set>
#include <unordered_set>  // Можно использовать неупорядоченный set
#include <iostream>


template <typename T>
void print(const T& numbers)
{
for (auto x : number1)
        std::cout << x << ' ';
    std::cout << "\n";
}

int main()
{
    std::set<int> number;                          // пустое множество
    std::set<int> number1{1, 2, 2, 3, 4, 5, 5, 6}; // множество уберёт повторяющиеся элементы
    std::set<int> number2(number);                 // инициализация через копирование

    // обход set

    // 1. через for each
    for (auto x : number1)
        std::cout << x << ' ';
    std::cout << "\n";

    // 2. через итераторы

    for (std::set<int>::iterator it = number1.begin(); it != number1.end(); ++it)
        std::cout << *it << ' ';
    std::cout << "\n";

    for (auto it = number1.rbegin(); it != number1.rend(); ++it) // вывод в обратную сторону
        std::cout << *it << ' ';
    std::cout << "\n";


     for (auto it = number1.cbegin(); it != number1.cend(); ++it) // вывод через константные указатели
        std::cout << *it << ' ';
    std::cout << "\n";

    number1.count(5); // проверка вхождения элемента в set
    number1.emplace(5); // создание элемента и его добавление в set
    number1.lower_bound(6); // поиск элемента большего либо равного текущему

    struct cmp
    {
        bool operator() (int a, int b) const
        {
            return a > b;
        }
    };

    std::set<int,cmp> numbers {1,2,3,45}; // в данном множестве элементы упорядочены в обратном порядке


    std::cin.get();
    return 0;
}