#pragma once
#include "Library.h"

template<typename T>
std::deque<T> Library<T>::selection(std::function<bool(const T&)> predicate)
{
	std::deque<T> result;
	std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
	return result;
}

template<typename T>
void Library<T>::read(std::istream_iterator<T> it)
{
	container.clear();
	std::istream_iterator<T> eos;
	while (it != eos)
	{
		container.push_back(*it);
		++it;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& out, Library<T>& lib)
{
	std::ostream_iterator<T> it(out, "\n");
	lib.print(it);
	return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, Library<T>& lib)
{
	std::istream_iterator<T> it(in);
	lib.read(it);
	return in;
}