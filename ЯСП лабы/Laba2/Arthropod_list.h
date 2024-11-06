#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <unordered_set>

template<class T>
class Arthropod_list {
private:
	std::list<T> container{};
public:
	Arthropod_list() {}
	void set(std::list<T> container)
	{
		this.container = container;
	}

	void add(T elem)
	{
		container.push_back(elem);
	}

	int size()
	{
		return container.size();
	}

	void del(int number)
	{
		auto x = container.begin();
		std::advance(x, number - 1);
		container.erase(x);
	}

	void change(int number, T new_elem)
	{
		del(number);
		auto x = container.begin();
		std::advance(x, number - 1);
		container.insert(x, new_elem);
	}

	Arthropod_list<T> selection(std::function<bool(T)> foo)
	{
		
		Arthropod_list result;
		std::copy_if(container.begin(), container.end(), std::back_inserter(result.container), foo);
		return result;
	}
	void remove_duplicates() {
		std::unordered_set<T> uniqueSet;
		container.remove_if([&uniqueSet](const T& val) {
			return !uniqueSet.insert(val).second;
			});

	}

	friend std::istream& operator >>(std::istream& is, Arthropod_list<T>& elem) {
		elem.container.clear();
		std::istream_iterator<T> input(is);
		std::istream_iterator<T> eos;
		while (input != eos)
		{
			elem.add(*input);
			
			++input;
			if (is.eof())
			{
				is.clear();
				break;
			}
		}

		return is;
	}

	friend std::ostream& operator <<(std::ostream& os, Arthropod_list<T>& elem) {
		std::ostream_iterator<T> out(os,"\n");
		std::copy(elem.container.cbegin(), elem.container.cend(), out);
		return os;
	}

};

