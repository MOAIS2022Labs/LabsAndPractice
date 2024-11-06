#include <list>
#include <algorithm>
#include <string>
#include <iterator>
#include <iomanip>
#include <functional>
#include <iostream>

template <typename T>
class DemonContainer
{
private:
    std::list<T> demons;

public:
    DemonContainer() {}
    void set(std::list<T> other_demons);
    void clear();

    void add_demon(T demon);
    void delete_demon(int index);
    void change_demon(int index);

    void fill_list(std::istream_iterator<T>& itBegin, std::istream_iterator<T>& itEnd);
    void print_list(std::ostream_iterator<T>& it);

    int get_size();
    std::list<T> get_list();

    std::list<T> get_demons_by_condition(std::function<bool(const T&)> pred);

    std::list<T> remove_demons_by_condition(std::function<bool(T&)> condition);
};

template <typename T>
inline void DemonContainer<T>::set(std::list<T> other_demons)
{
    demons = other_demons;
}
template <typename T>
inline void DemonContainer<T>::clear()
{
    demons.clear();
}

template <typename T>
void DemonContainer<T>::add_demon(T demon)
{
    demons.push_back(demon);
}
template <typename T>
inline void DemonContainer<T>::delete_demon(int index)
{
    if (index >= 0 && index < demons.size())
    {
        auto it = demons.begin();
        std::advance(it, index);
        demons.erase(it);
    }
}
template <typename T>
inline void DemonContainer<T>::change_demon(int index)
{
    std::cout << "\nВведите данные демона в следующем виде:\n\n";
    std::cout << "Имя\n";
    std::cout << "Происхождения \n";
    std::cout << "Рост \n";
    std::cout << "Оружие \n";
    std::cout << "Количество рогов \n";
    std::cout << "Количество часов жизни \n";
    std::cout << "Цвет \n";
    T demon;
    std::cin >> demon;

    typename std::list<T>::iterator it = demons.begin();
    std::advance(it, index);
    demons.insert(it, demon);
}

template <typename T>
void DemonContainer<T>::fill_list(std::istream_iterator<T>& itBegin, std::istream_iterator<T>& itEnd)
{
    std::copy(itBegin, itEnd, std::back_inserter(demons));
}
template <typename T>
void DemonContainer<T>::print_list(std::ostream_iterator<T>& it)
{
    std::copy(demons.begin(), demons.end(), it);
}

template<typename T>
inline int DemonContainer<T>::get_size()
{
    return demons.size();
}

template<typename T>
inline std::list<T> DemonContainer<T>::get_list()
{
    return demons;
}

template<typename T>
inline std::list<T> DemonContainer<T>::get_demons_by_condition(std::function<bool(const T&)> pred)
{
    std::list<T> result;
    for (const auto& demon : demons)
    {
        if (pred(demon))
            result.push_back(demon);
    }
    return result;
}

template <typename T>
std::list<T> DemonContainer<T>::remove_demons_by_condition(std::function<bool(T&)> condition)
{
    demons.remove_if(condition);
    return demons;
}