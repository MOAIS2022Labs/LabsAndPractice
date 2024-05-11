#include <iostream>
#include <windows.h>

class DArray
{
private:
    size_t size, max_size;
    int *array;
    void destroy()
    {
        if (array)
            delete[] array;
        array = nullptr;
    }

public:
    DArray(size_t max_size) : max_size(max_size), size(0) { array = new int[max_size]; }
    DArray(size_t max_size, int A, int B) : max_size(max_size)
    {
        srand(GetTickCount());
        array = new int[max_size];
        size = rand() % max_size + 1;
        for (size_t i = 0; i < size; ++i)
            array[i] = A + rand() % (B - A);
    }
    DArray(const DArray &other);                                                    // конструктор копирования
    DArray &operator=(const DArray &other);                                         // переопределние присваивания
    DArray(DArray &&tmp) :                                                          /*через правостороннее значение*/
                           max_size(tmp.max_size), size(tmp.size), array(tmp.array) // конструктор пермещения
    {
        tmp.array = nullptr;
    }
    DArray &operator=(DArray &&tmp) // оператор присваивания по правостороннему
    {
        if (this != &tmp)
        {
            destroy();
            max_size = tmp.max_size;
            size = tmp.size;
            array = tmp.array;
            tmp.array = nullptr;
        }
        return *this;
    }
    ~DArray() { destroy(); }
    size_t get_size() const;
    void set_size(size_t size);
    size_t get_max_size() const;
    int get_elem(size_t index) const;
    void set_elem(size_t index, int elem);
    void set_array(int *array);
    void print() const;
};
