#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iterator>

template<typename T>
class Container
{
private:
    //фактический контейнера
    std::vector<T> vector{};

    //получение итератора по индексу
    typename std::vector<T>::iterator get_iterator(size_t index)
    {
        typename std::vector<T>::iterator iterator = vector.begin();
        while (index > 0) {
            iterator++;
            index -= 1;
        }
        return iterator;
    }
public:
    //неинициализирующий конструктор
    Container() {}

    //размер контейнера
    size_t size() { return vector.size(); }

    //получение элемента контейнера по индексу
    const T &at(size_t index)
    {
        if (index >= vector.size())
            throw std::out_of_range("Недействительный индекс!");
        return vector[index];
    }

    //последний элемент контейнера
    T get_last()
    {
        return vector.back();
    }

    //задание уже существующего контейнера(вектора)
    void set(std::vector<T> &selected)
    {
        vector = selected;
    }

    //очистка контейнера
    std::vector<T> clear()
    {
        std::vector<T> copy(vector);
        if (!vector.empty())
            vector.clear();
        return copy;
    }

    //добавление элемента в контейнер
    void add(const T &value)
    {
        vector.push_back(value);
    }

    //изменение элемента контейнера по индексу
    void edit(size_t index, const T &value)
    {
        if (index >= vector.size())
            throw std::out_of_range("Недействительный индекс!");
        vector[index] = value;
    }

    //удаление элемента контейнера по индексу
    T remove(size_t index) {
        if (index >= vector.size())
            throw std::out_of_range("Недействительный индекс!");
        T value = vector[index];
        vector.erase(get_iterator(index));
        return value;
    }

    //выборка из контейнера
    std::vector<T> selection(std::function<bool(T &)> selector)
	{
        std::vector<T> selected(vector.size());
        if (!vector.empty()) {
            auto selected_end = std::copy_if(vector.begin(), vector.end(), selected.begin(), selector);
            selected.erase(selected_end, selected.end());
        }
        return selected;
    }

    //вставка элементов из итератора в контейнер
    void read(std::istream_iterator<T> &in)
    {
        vector.insert(vector.end(), in, std::istream_iterator<T>());
    }

    //копирование элементов из контейнера в итератор
    bool write(std::ostream_iterator<T> &out)
    {
        if (vector.empty())
            return false;
        std::copy(vector.begin(), vector.end(), out);
        return true;
    }
};