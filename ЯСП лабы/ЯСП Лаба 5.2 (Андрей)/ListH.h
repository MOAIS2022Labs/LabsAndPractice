#pragma once

#include <list>
#include <algorithm>
#include <iterator>
#include <functional>

template <typename T>
class List
{
private:
    std::list<T> container;
public:
    List() {}
    void set(std::list<T> other_elems);
    void add_elem(T elem);
    void delete_elem(int index);
	void change_elem(int index, T elem);

    void fill_list(std::istream& stream);
	bool check_empty();
	int get_size();

	std::list<T> get_list();
    std::list<T> get_by_condition(std::function<bool(const T&)> pred);
    std::list<T> condition_remove(std::function<bool(T&)> condition);

	void print_beautiful_console(std::ostream_iterator<T> out = std::ostream_iterator<T>(std::cout, "\n"));
	void print_list(std::ostream_iterator<T> out = std::ostream_iterator<T>(std::cout, "\n"));
};

template <typename T>
 void List<T>::set(std::list<T> other_elems)
{
	container = other_elems;
}

template <typename T>
void List<T>::add_elem(T elem)
{
	container.push_back(elem);
}

template <typename T>
bool List<T>::check_empty()
{
	return (container.empty());
}

template <typename T>
void List<T>::delete_elem(int index)
{
	if (index >= 0 && index < (int)container.size())
	{
		auto it = container.begin();
		std::advance(it, index);
		container.erase(it);
	}
}

template <typename T>
 void List<T>::change_elem(int index, T elem)
{
	if (index >= 0 && index < (int)container.size())
	{
		auto it = container.begin();
		std::advance(it, index);
		container.insert(it, elem);
		container.erase(it);
	}
}

template <typename T>
 void List<T>::fill_list(std::istream& stream)
{
	std::copy(std::istream_iterator<T>(stream), std::istream_iterator<T>(), std::back_inserter(container));
}

template <typename T>
 void List<T>::print_beautiful_console(std::ostream_iterator<T> out)
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	for (T d : container)
	{
		SetConsoleTextAttribute(h, ((0 << 4) | d.define_color()) );

		*out = d;
		++out;		
	}
	SetConsoleTextAttribute(h, (((0 << 4) | 15)));
}

template <typename T>
 void List<T>::print_list(std::ostream_iterator<T> out)
{
	std::copy(container.begin(), container.end(), out);
}

template<typename T>
 int List<T>::get_size()
{
	return container.size();
}

template<typename T>
 std::list<T> List<T>::get_list()
{
	return container;
}

template<typename T>
 std::list<T> List<T>::get_by_condition(std::function<bool(const T&)> condition)
{
	 std::list<T> result;
	 for (const auto& elem : container)
	 {
		 if (condition(elem))
			 result.push_back(elem);
	 }
	 return result;
}

template <typename T>
std::list<T> List<T>::condition_remove(std::function<bool(T&)> condition)
{
	container.erase(std::remove_if(container.begin(), container.end(), condition), container.end());
	return container;
}

