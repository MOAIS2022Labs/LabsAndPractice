#include "Container.h"

Container::Container(std::fstream& file)
{
	iterator ptr = fl.before_begin();
	int x{};
	while (file >> x)
	{
		fl.insert_after(ptr, x);
		++ptr;
	} 
}

int Container::_count_non_negative(iterator begin, iterator end)
{
	int count{};
	for (iterator ptr = begin; ptr != end; ++ptr)
		count += *ptr >= 0 ? 1 : 0;
	return count;
}

std::forward_list<int> Container::modify_for(iterator begin, iterator end)
{
	//std::forward_list<int> result;
	//int count{};
	//for (iterator ptr = begin, ptr_res = result.before_begin(); ptr != end; ++ptr, ++ptr_res)
	//{
	//	result.insert_after(ptr_res, *ptr);
	//	count += *ptr >= 0 ? 1 : 0;
	//}
	//iterator new_end = result.end();
	//for (iterator ptr = result.begin(); ptr != new_end; ++ptr)
	//	*ptr += *ptr > 0 ? count : 0;
	//return result;

	std::forward_list<int> result;
	int count = _count_non_negative(begin, end);
	for (iterator ptr = begin, ptr_res = result.before_begin(); ptr != end; ++ptr, ++ptr_res)
	{
		int val = *ptr > 0 ? *ptr + count : *ptr;
		result.insert_after(ptr_res, val);
	}
	return result;
}

std::forward_list<int> Container::modify_transform(iterator begin, iterator end)
{
	/*std::forward_list<int> result(begin, end);
	int count{};
	std::transform(begin, end, result.begin(), [&count](int x)
		{
			count += x >= 0 ? 1 : 0;
			return x;
		});
	std::transform(result.begin(), result.end(), result.begin(), [count](int x)
		{
			if (x > 0) return x + count;
			else return x;
		});
	return result;*/

	std::forward_list<int> result(begin, end);
	int count = _count_non_negative(begin, end);
	std::transform(begin, end, result.begin(), [count](int x)
		{
			if (x > 0) return x + count;
			else return x;
		});
	return result;
}

std::forward_list<int> Container::modify_for_each(iterator begin, iterator end)
{
	/*std::forward_list<int> result;
	int count{};
	iterator ptr = result.before_begin();
	std::for_each(begin, end, [&count, &result, &ptr](int x)
		{
			result.insert_after(ptr, x);
			++ptr;
			count += x >= 0 ? 1 : 0;
		});
	std::for_each(result.begin(), result.end(), [count](int& x) {if (x > 0) x += count; });
	return result;*/

	std::forward_list<int> result;
	int count = _count_non_negative(begin, end);
	iterator ptr = result.before_begin();
	std::for_each(begin, end, [count, &result, &ptr](int x) 
		{
			if (x > 0) x += count; 
			result.insert_after(ptr, x);
			++ptr;
		});
	return result;
}

iterator Container::begin()
{
	return fl.begin();
}

iterator Container::end()
{
	return fl.end();
}

iterator Container::get_iterator(const size_t number)
{
	iterator end = fl.end();
	size_t i{1};
	for (iterator ptr = fl.begin(); ptr != end; ++ptr, ++i)
		if (i == number)
			return ptr;
	return end;
}

int Container::sum()
{
	int sum{};
	std::for_each(fl.begin(), fl.end(), [&sum](int x) {sum += x; });
	return sum;
}

double Container::average()
{
	int sum{}, count{};
	std::for_each(fl.begin(), fl.end(), [&sum, &count](int x) {sum += x; ++count; });
	if (!count)
		return 0;
	return static_cast<double>(sum) / count;
}

void Container::print_console()
{
	for (int elem : fl)
		std::cout << elem << ' ';
	std::cout << '\n';
}

void Container::print_file(const std::string& fname)
{
	std::ofstream file(fname);
	for (int elem : fl)
		file << elem << ' ';
	file.close();
}

std::ostream& operator<<(std::ostream& out, const Container& container)
{
	for (int elem : container.fl)
		out << elem << ' ';
	out << '\n';
	return out;
}
