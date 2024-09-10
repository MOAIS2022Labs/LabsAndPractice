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
    //����������� ����������
    std::vector<T> vector{};

    //��������� ��������� �� �������
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
    //������������������ �����������
    Container() {}

    //������ ����������
    size_t size() { return vector.size(); }

    //��������� �������� ���������� �� �������
    const T &at(size_t index)
    {
        if (index >= vector.size())
            throw std::out_of_range("���������������� ������!");
        return vector[index];
    }

    //��������� ������� ����������
    T get_last()
    {
        return vector.back();
    }

    //������� ��� ������������� ����������(�������)
    void set(std::vector<T> &selected)
    {
        vector = selected;
    }

    //������� ����������
    std::vector<T> clear()
    {
        std::vector<T> copy(vector);
        if (!vector.empty())
            vector.clear();
        return copy;
    }

    //���������� �������� � ���������
    void add(const T &value)
    {
        vector.push_back(value);
    }

    //��������� �������� ���������� �� �������
    void edit(size_t index, const T &value)
    {
        if (index >= vector.size())
            throw std::out_of_range("���������������� ������!");
        vector[index] = value;
    }

    //�������� �������� ���������� �� �������
    T remove(size_t index) {
        if (index >= vector.size())
            throw std::out_of_range("���������������� ������!");
        T value = vector[index];
        vector.erase(get_iterator(index));
        return value;
    }

    //������� �� ����������
    std::vector<T> selection(std::function<bool(T &)> selector)
	{
        std::vector<T> selected(vector.size());
        if (!vector.empty()) {
            auto selected_end = std::copy_if(vector.begin(), vector.end(), selected.begin(), selector);
            selected.erase(selected_end, selected.end());
        }
        return selected;
    }

    //������� ��������� �� ��������� � ���������
    void read(std::istream_iterator<T> &in)
    {
        vector.insert(vector.end(), in, std::istream_iterator<T>());
    }

    //����������� ��������� �� ���������� � ��������
    bool write(std::ostream_iterator<T> &out)
    {
        if (vector.empty())
            return false;
        std::copy(vector.begin(), vector.end(), out);
        return true;
    }
};