#pragma once
#include "HumanParameters.h"

const int allocate_memory = 50;

// ������ ������ ������
template <class X>
class Vector
{
private:
    X* arr; // ������ ���������
    int capacity; // ���������� ������ ��� ������ ������
    X* first; // ��������� �� ������ �������
    X* last; // ��������� �� ��������� �������
public:
    // ������������
    Vector(int size = allocate_memory) { capacity = 0; arr = new X[size]; first = nullptr; last = nullptr; }
    // ����������
    ~Vector() 
    {
        clear();
        delete[] arr;
    };

    X get_type()
    {
        return X();
    }

    // ����� ��� ���������� ������� �� �����
    void init_from_file(std::ifstream& file);

    // ����� ��� ���������� �������� � ������ �������
    void push_front(X value);

    // ����� ��� ���������� �������� � ����� �������
    void push_back(X value);

    // ����� ��� ������ ���� ��������� �������
    void print(std::ostream& output);

    // ����� ��� ����������� ���������� ��������� �������
    int get_size();

    // ����� ��� �������� �������� �� ������ (�������)
    void remove_at(int index);

    // ����� ��� �������� ������� ��������
    void remove_first();

    // ����� ��� �������� ���������� ��������
    void remove_last();

    // ����� ��� �������� ���� ��������� ������� � �������� ���������
    void remove_all_with_value(X value);

    // ����� ��� ���������� ��������� �������
    void sort();

    //����� ��� ������� �������
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
        std::cout << "������ ������";
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
    // ���������, ��� ������ ��������� � �������� �������
    if (index < 0 || index >= get_size())
    {
        std::cout << "������ �� ��������� �������\n";
    }
    else
    {  
        X* newElements = new X[capacity - 1];

        // ������� ������� ����� ����������� first � arr
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

        // ������� ������ ������
        delete[] arr;

        // ��������� ��������� �� ����� ������
        arr = newElements;

        // ��������� ��������� first � last
        int diff1 = new_first - newElements;
        first = arr + diff1;
        int diff2 = new_last - new_first;
        last = first + diff2 - 1;
        
        // ��������� capacity
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
        std::cout << "������ ������\n"; // ���� ������ ������, ������� ��������� �� ������
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
        std::cout << "������ ������\n"; // ���� ������ ������, ������� ��������� �� ������
}

template<class X>
void Vector<X>::remove_all_with_value(X value) // ����������
{
    int count = 0;
    for (X* i = first; i <= last; ++i)
    {
        if (*i == value)
            ++count;
    }
    if (count)
    {
        // ������� ����� ������ �� ���� ������� ������
        X* newElements = new X[capacity - count];

        int diff = first - arr;

        X* new_first = newElements + diff;
        X* index_temp = new_first;

        X* new_last = new_first;

        // ���������� �� ���� ��������� �������
        for (X* i = first; i <= last; ++i)
        {
            // ���� ������� �� ����� ��������� ��������, �������� ��� � ����� ������
            if (*i != value)
            {
                *(index_temp) = *i;
                ++new_last;
                ++index_temp;
            }
        }
        // ������� ������ ������
        delete[] arr;

        // ��������� ��������� �� ����� ������
        arr = newElements;

        // ��������� ��������� first � last
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
void Vector<X>::clear() // ������� ����� �� ���� ������ �� �������
{
    int index_first = first - arr;
    for (int i = index_first; i < get_size(); ++i)
        remove_at(i);
    capacity = 0;
    arr = nullptr;
    first = nullptr;
    last = nullptr;
}