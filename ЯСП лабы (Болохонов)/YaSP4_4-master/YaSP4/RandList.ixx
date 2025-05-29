module;
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <numeric>

export module RandList;
export class RandList
{
private:
	std::list<int> list;
public:
	RandList() {};
	RandList(const RandList& other);
	RandList& operator=(const RandList& other);
	RandList(const size_t size);
	RandList(std::fstream& file);
	void fill_generate(const int radius);
	void fill_iter(const int radius);
	int sum() const { return std::accumulate(list.begin(), list.end(), 0); }
	int avg() const { return (sum() / 1.0) / list.size(); }
	int abs_min() const;
	RandList modify_for() const;
	RandList modify_transform() const;
	RandList modify_for_each() const;
	friend std::ostream& operator<<(std::ostream& os, const RandList& rlist);
};

export std::ostream& operator<<(std::ostream& os, const RandList& rlist)
{
	for (const int i : rlist.list)
		os << i << ' ';
	return os;
}

RandList::RandList(const RandList& other)
{
	for (const int i : other.list)
		this->list.push_back(i);
}

RandList& RandList::operator=(const RandList& other)
{
	if (this != &other)
	{
		list.clear();
		for (const int i : other.list)
			this->list.push_back(i);
	}
	return *this;
}

RandList::RandList(const size_t size)
{
	for (size_t i{}; i < size; ++i)
		list.push_back(0);
}

RandList::RandList(std::fstream& file)
{
	int elem{};
	while (file >> elem)
	{
		list.push_back(elem);
	}
}

void RandList::fill_generate(const int radius)
{
	std::generate_n(list.begin(), list.size(), [&]() { return rand() % (2 * radius + 1) - radius; });
}

void RandList::fill_iter(const int radius)
{
	for (int i : list)
		i = rand() % (2 * radius + 1) - radius;
}

int RandList::abs_min() const
{
	int result = abs(list.front());
	for (const int i : list)
	{
		if (abs(i) < result)
			result = abs(i);
	}
	return result;
}

RandList RandList::modify_for() const
{
	RandList res_list{};
	int sqrt_abs_min = trunc(sqrt(abs_min()));

	// перебор списка и прибавление к каждому второму числу sqrt_abs_min
	bool second = false;
	for (const int i : list)
	{
		if (second == true)
		{
			res_list.list.push_back(i + sqrt_abs_min);
			second = false;
		}
		else
		{
			res_list.list.push_back(i);
			second = true;
		}
	}
	return res_list;
}

RandList RandList::modify_transform() const
{
	RandList res_list{};
	int sqrt_abs_min = trunc(sqrt(abs_min()));
	bool second = false;
	std::transform(list.begin(), list.end(), std::back_inserter(res_list.list), [&second, sqrt_abs_min](int a)
		{
			if (second)
			{
				second = false;
				return a + sqrt_abs_min;
			}
			else
			{
				second = true;
				return a;
			}
		});
	return res_list;
}

RandList RandList::modify_for_each() const
{
	RandList res_list{};
	res_list.list = list;
	int sqrt_abs_min = trunc(sqrt(abs_min()));
	bool second = false;
	std::for_each(res_list.list.begin(), res_list.list.end(), [&second, sqrt_abs_min](int& a)
		{
			if (second)
			{
				second = false;
				a += sqrt_abs_min;
			}
			else
			{
				second = true;
			}
		});
	return res_list;
}