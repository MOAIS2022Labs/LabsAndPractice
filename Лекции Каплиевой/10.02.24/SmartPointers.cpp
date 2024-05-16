#include <iostream>
#include <memory>

struct ELEM
{
    int x;
    ELEM(int x) : x(x) {}
};

// возвращение умного указателя из функции
std::unique_ptr<double> average(int *arr, int size)
{
    std::unique_ptr<double> result = nullptr;
    double summ = 0;
    int count = 0;
    // ... код решения
    {
        result = std::move(std::make_unique<double>(summ / count));
    }
    return result;
}

// передача в функцию:
void foo(std::unique_ptr<ELEM> ptr)
{
    if (ptr)
        std::cout << ptr->x << '\n';
}

void bar(ELEM* ptr)
{
     if (ptr)
        std::cout << ptr->x << '\n';
}

int main()
{

    // Работа с функциями
    int *arr;
    // возврат
    std::unique_ptr<double> avg = average(arr, 7);

    auto ptr = std::make_unique<ELEM>(5);
    // передача
    foo(std::move(ptr)); // данная функция уничтожает исходынй объект! 
    bar(ptr.get()); // get возвращает из умного указателя чистый указатель - безопасное использование функции!


    std::unique_ptr<int> _uptr = std::make_unique<int>(5);
    std::unique_ptr<int> uptr(new int(5)); // unique pointer владеет выделенной ячейкой для числа 5

    std::cout << *uptr << "\n";

    std::unique_ptr<ELEM> uptr1(new ELEM(5)); // пример с имитацией класса
                                              // альтернатива с make_unique:  std::unique_ptr<ELEM> uptr1 = std::make_unique<ELEM>(5);
    std::unique_ptr<ELEM> uptr2;
    // uptr2 = uptr1; // попытка овладеть ресурсом - ОШИБКА, т.к. ресурсом уже кто-то владеет
    // внутри класса умных указателей отключена семантика копирования!!
    uptr2 = std::move(uptr1);      // правильно
    auto uptr3 = std::move(uptr2); // теперь ячейкой ELEM(5) владеет 3 указателя.
    std::cout << uptr3->x;

    // Умный указатель и динамические массивы:
    std::unique_ptr<int[]> darr(new int[5]);
    auto _darr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i)
        darr[i] = i;
    for (int i = 0; i < 5; ++i)
        std::cout << darr[i] << " ";
    std::cout << "\n";

    std::cin.get();
    return 0;
}