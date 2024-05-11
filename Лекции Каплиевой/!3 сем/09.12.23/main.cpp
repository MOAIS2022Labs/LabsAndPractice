#include "DArray.h"

DArray task_only_odd(const DArray &DA)
{
    size_t cnt = 0, size = DA.get_size();
    DArray result(DA.get_max_size());
    for (size_t i = 0; i < size; ++i)
    {
        int x = DA.get_elem(i);
        if (x % 2 != 0)
        {
            result.set_elem(cnt, x);
            ++cnt;
        }
    }
    result.set_size(cnt);
    return result;
}

int main()
{
    DArray DA(25, -100, 100);
    DA.print();
    DArray DA2 = DA; // сработал конструктор копирования
    DA2.print();
    DArray DA3 = task_only_odd(DA); // сработал конструктор перемещения
    DA2 = task_only_odd(DA); // сработал конструктор перемещения (внутри task):
    // создаётся временный объект, ему через конструктор перемещения задаются значения
    // затем сработает оператор перемещения
    DA2 = DA; // сработал оператор присваивания
    DA3.print();
    /*
    Конструктор пермещения применяется в ситуациях, где объявление совпадает с инициализацией
    rvalue-ссылкой на экземпляр того же класса. Либо посредством прямой инициализации
    в конструкторе класса (если определение происходит с помощью lvalue-ссылки, то вызовется 
    конструктор копирования). 
    
    Оператор перемещения применяется в местах, где экземпляр класса уже был раннее определён ,
    и к нему определяется оператор присваивания, который в качестве аргумента rvalue-ссылку
    на экземпляр того же класса. Если же оператор принимает lvalue-ссылку, то вызовется 
    оператор присваивания.
    */
    std::cin.get();
    return 0;
}