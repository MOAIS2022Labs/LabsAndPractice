#pragma once
#include "HumanParameters.h"

const int allocate_memory = 50;

// шаблон класса вектор
template <class X>
class Vector
{
private:
    X* arr; // массив элементов
    int capacity; // выделенная память под массив массив
    X* first; // указатель на первый элемент
    X* last; // указатель на последний элемент
public:
    // конструкторы
    Vector(int size = allocate_memory) { capacity = 0; arr = new X[size]; first = nullptr; last = nullptr; }
    // деструктор
    ~Vector() 
    {
        clear();
        delete[] arr;
    };

    X get_type()
    {
        return X();
    }

    // метод для заполнения массива из файла
    void init_from_file(std::ifstream& file);

    // метод для добавления элемента в начало массива
    void push_front(X value);

    // метод для добавления элемента в конец массива
    void push_back(X value);

    // метод для вывода всех элементов массива
    void print(std::ostream& output);

    // метод для определения количества элементов массива
    int get_size();

    // метод для удаления элемента по номеру (индексу)
    void remove_at(int index);

    // метод для удаления первого элемента
    void remove_first();

    // метод для удаления последнего элемента
    void remove_last();

    // метод для удаления всех элементов массива с заданным значением
    void remove_all_with_value(X value);

    // метод для сортировки элементов массива
    void sort();

    //метод для очистки массива
    void clear();
};

template<class X>
void Vector<X>::init_from_file(std::ifstream& file)
{
    X tmp{};
    while (file >> tmp)
        push_back(tmp);
}

template<class X>
void Vector<X>::push_front(X value)
{
    if (capacity == 0)
    {
        arr = new X[allocate_memory];
        
        arr[0] = value;
        first = arr;
        last = arr;
        capacity = allocate_memory;
    }
    else if (first == arr)
    {
        int diff = get_size();
        X* temp = new X[capacity * 2];
        first = temp + capacity / 2 - 1;
        last = first + diff;
        for (int i = 0; i < capacity; ++i)
        {
            temp[i + capacity /2] = arr[i];
        }
        delete[] arr;
        arr = temp;
        *first = value;
        capacity *= 2;
    }
    else
        *--first = value;
}

template<class X>
void Vector<X>::push_back(X value)
{
    if (capacity == 0)
    {
        arr = new X[allocate_memory];
        arr[0] = value;
        first = arr;
        last = arr;
        capacity = allocate_memory;
    }
    else if (last == arr + capacity - 1)
    {
        int diff = first - arr;
        X* temp = new X[capacity * 2];
        for (int i = 0; i < capacity; ++i)
            temp[i] = arr[i];
        delete[] arr;
        arr = temp;
        arr[capacity] = value;
        first = arr + diff;
        last = arr + capacity;
        capacity *= 2;
    }
    else
        *++last = value;
}

template<class X>
void Vector<X>::print(std::ostream& output)
{
    if (first)
    {
        for (X* i = first; i <= last; ++i)
            output << *i << " ";
    }
    else
        std::cout << "Вектор пустой";
    std::cout << '\n';
}

template<class X>
int Vector<X>::get_size()
{
    return ((last==first) ? (first && last ? 1 : 0) : last - first + 1);
}

template<class X>
void Vector<X>::remove_at(int index)
{
    // Проверяем, что индекс находится в пределах массива
    if (index < 0 || index >= get_size())
    {
        std::cout << "Индекс за пределами массива\n";
    }
    else
    {  
        X* newElements = new X[capacity - 1];

        // Находим разницу между указателями first и arr
        int diff = first - arr;

        X* new_first = newElements + diff;
        X* index_temp = new_first;

        X* new_last = new_first;
        for (int i = 0; i < get_size(); ++i)
        {
            if (i != index)
            {
                *(index_temp) = *(arr + i);
                ++new_last;
                ++index_temp;
            }
        }

        // Удаляем старый массив
        delete[] arr;

        // Обновляем указатель на новый массив
        arr = newElements;

        // Обновляем указатель first и last
        int diff1 = new_first - newElements;
        first = arr + diff1;
        int diff2 = new_last - new_first;
        last = first + diff2 - 1;
        
        // Уменьшаем capacity
        --capacity;
    }
}

template<class X>
void Vector<X>::remove_first()
{
    if (first)
    {
        //int index_first = first - arr;
        remove_at(0);
    }
    else
        std::cout << "Вектор пустой\n"; // если массив пустой, выводим сообщение об ошибке
}

template<class X>
void Vector<X>::remove_last()
{
    if (first)
    {
        //int index_last = last - arr;
        remove_at(get_size()-1);
    }
    else
        std::cout << "Вектор пустой\n"; // если массив пустой, выводим сообщение об ошибке
}

template<class X>
void Vector<X>::remove_all_with_value(X value) // переделать
{
    int count = 0;
    for (X* i = first; i <= last; ++i)
    {
        if (*i == value)
            ++count;
    }
    if (count)
    {
        // создаем новый массив на один элемент меньше
        X* newElements = new X[capacity - count];

        int diff = first - arr;

        X* new_first = newElements + diff;
        X* index_temp = new_first;

        X* new_last = new_first;

        // проходимся по всем элементам массива
        for (X* i = first; i <= last; ++i)
        {
            // если элемент не равен заданному значению, копируем его в новый массив
            if (*i != value)
            {
                *(index_temp) = *i;
                ++new_last;
                ++index_temp;
            }
        }
        // Удаляем старый массив
        delete[] arr;

        // Обновляем указатель на новый массив
        arr = newElements;

        // Обновляем указатель first и last
        int diff1 = new_first - newElements;
        first = arr + diff1;
        int diff2 = new_last - new_first;
        last = first + diff2 - 1;

        capacity -= count;
    }
}

template<class X>
void Vector<X>::sort()
{
    for (X* i = first; i != last+1; ++i)
    {
        for (X* j = i; j != first && *(j - 1) > *j; --j)
        {
            X tmp = *(j - 1);
            *(j - 1) = *j;
            *j = tmp;
        }
    }
}

template<class X>
void Vector<X>::clear() // Сделать чтобы не было вывода на консоль
{
    int index_first = first - arr;
    for (int i = index_first; i < get_size(); ++i)
        remove_at(i);
    capacity = 0;
    arr = nullptr;
    first = nullptr;
    last = nullptr;
}