#pragma once
#include <algorithm>
#include <list>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <fstream>
//#include "Arthropod.h"

template <typename T>
class Container
{
private:
	std::list<T> container{};

public:

	Container<T>() {}
	Container<T>(const Container<T>& other)
	{
		std::copy(other.container.begin(), other.container.end(), container.begin());
	}
	
	void clear()
	{
		container.clear();
	}

	void add(const T& val)
	{
		container.push_back(val);
	}

	size_t size()
	{
		return container.size();
	}

	// удаление по индексу (индексация с нуля)
	void remove(size_t index)
	{
		if (index >= container.size())
			throw std::out_of_range("Индекс слишком велик!\n");
		auto it = container.begin();
		std::advance(it, index);
		container.erase(it);
	}

	// изменение значения по индексу (индексация с нуля)
	void change(size_t index, const T& val)
	{
		if (index >= container.size())
			throw std::out_of_range("Индекс слишком велик!\n");
		auto it = container.begin();
		std::advance(it, index);
		*it = val;
	}

	void remove_duplicates()
	{
		std::unordered_set<T> set;
		container.remove_if([&set](const T& x) {return !set.insert(x).second; });
	}

	void print(std::ostream_iterator<T> it)
	{
		std::copy(container.begin(), container.end(), it);
	}

	void read(std::istream_iterator<T> it)
	{
		container.clear();
		std::istream_iterator<T> eos;
		while (it != eos)
		{
			container.push_back(*it);
			++it;			
		}
	}

	std::list<T> selection(std::function<bool(const T&)> predicate)
	{
		std::list<T> result;
		std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
		return result;
	}

	friend std::ostream& operator<<(std::ostream& out, Container& cont)
	{
		std::ostream_iterator<T> it(out, "\n");
		cont.print(it);
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Container& cont)
	{
		std::istream_iterator<T> it(in);
		cont.read(it);
		return in;
	}
};