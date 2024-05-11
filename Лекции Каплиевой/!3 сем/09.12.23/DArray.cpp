#include "DArray.h"

DArray::DArray(const DArray &other)
{
    max_size = other.max_size;
    size = other.size;
    array = new int[max_size];
    for (size_t i = 0; i < size; ++i)
        array[i] = other.array[i];
}

DArray &DArray::operator=(const DArray &other)
{
    if (this != &other)
    {
        destroy();
        max_size = other.max_size;
        size = other.size;
        array = new int[max_size];
        for (size_t i = 0; i < size; ++i)
            array[i] = other.array[i];
    }
    return *this;
}

size_t DArray::get_size() const
{
    return size;
}

void DArray::set_size(size_t size)
{
    this->size = size;
}

size_t DArray::get_max_size() const
{
    return max_size;
}

int DArray::get_elem(size_t index) const
{
    int result{}; // result = 0 по умолчанию
    if (index >= 0 && index < size)
        result = array[index];
    return result;
}

void DArray::set_elem(size_t index, int elem)
{
    if (index >= 0 && index < size)
        array[index] = elem;
}

void DArray::set_array(int *array)
{
    this->array = array;
}

void DArray::print() const
{
    for (size_t i{}; i < size; ++i)
        std::cout << array[i] << ' ';
    std::cout << '\n';
}
