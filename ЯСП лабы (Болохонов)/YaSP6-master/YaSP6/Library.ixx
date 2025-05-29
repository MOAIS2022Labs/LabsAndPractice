module;

#include <deque>
#include <functional>
#include <algorithm>
#include <fstream>
#include <chrono>

export module Library;

export template <typename T>
class Library
{
private:
	std::deque<T> container;
public:
	Library() {}
	
	Library(const Library& other) { std::copy(other.container.begin(), other.container.end(), std::back_inserter(container)); }
	
	void add_left(const T& value) { container.push_front(value); }
	
	void add_right(const T& value) { container.push_back(value); }

	T& get_left() { return container[0]; }

	T& get_right() { return container[size() - 1]; }

	size_t size() { return container.size(); }

	void clear() { container.clear(); }

	bool empty() const { return container.empty(); }
	
	void remove_left() 
	{ 
		if (size() == 0)
			throw std::out_of_range("Библиотека пуста!");
		container.pop_front();
	}
	
	void remove_right() 
	{ 
		if (size() == 0)
			throw std::out_of_range("Библиотека пуста!");
		container.pop_back();
	}
	
	void change_left(const T& value) 
	{
		if (size() == 0)
			throw std::out_of_range("Библиотека пуста!");
		container[0] = value; 
	}
	
	void change_right(const T& value) 
	{
		if (size() == 0)
			throw std::out_of_range("Библиотека пуста!");
		container[size() - 1] = value; 
	}
	
	Library<T> selection(std::function<bool(const T&)> predicate)
	{
		Library<T> result;
		std::copy_if(container.begin(), container.end(), std::back_inserter(result.container), predicate);
		return result;
	}
	
	T& operator[](size_t index) {
		if (index >= container.size()) {
			throw std::out_of_range("Индекс выходит за границы библиотеки!");
		}
		return container[index];
	}
	
	void read(std::istream_iterator<T> it)
	{
		container.clear();
		std::istream_iterator<T> eos;
		std::copy(it, eos, std::back_inserter(container));
	}
	
	void print(std::ostream_iterator<T> it) const { std::copy(container.begin(), container.end(), it); }
	
	friend std::ostream& operator<<(std::ostream& out, const Library<T>& lib)
	{
		std::ostream_iterator<T> it(out, "\n");
		lib.print(it);
		return out;
	}
	
	friend std::istream& operator>>(std::istream& in, Library<T>& lib)
	{
		std::istream_iterator<T> it(in);
		lib.read(it);
		return in;
	}
};
