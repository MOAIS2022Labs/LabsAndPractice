#pragma once
#include <deque>
#include <functional>
#include <algorithm>
#include "Manuscript.h"

template <typename T>
class Library
{
private:
	std::deque<T> container;
public:
	Library() {}
	Library(const Library& other) { std::copy(other.container.begin(), other.container.end(), std::back_inserter(container)); }
	void clear() { container.clear(); }
	void add_left(T value) { container.push_front(value); }
	void add_right(T value) { container.push_back(value); }
	void remove_left() { container.pop_front(); }
	void remove_right() { container.pop_back(); }
	void change_left(T value) { container[0] = value; }
	void change_right(T value) { container[size() - 1] = value; }
	size_t size() { return container.size(); }
	std::deque<T> selection(std::function<bool(const T&)> predicate);
	void read(std::istream_iterator<T> it);
	void print(std::ostream_iterator<T> it) { std::copy(container.begin(), container.end(), it); }
	friend std::ostream& operator<<(std::ostream& out, Library<T>& lib);
	friend std::istream& operator>>(std::istream& in, Library<T>& lib);
};
