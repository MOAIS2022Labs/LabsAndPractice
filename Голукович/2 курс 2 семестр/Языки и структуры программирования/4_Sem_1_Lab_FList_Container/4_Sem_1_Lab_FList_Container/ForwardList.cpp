#include "ForwardList.h"

std::forward_list<int> FList::fill_flist(std::fstream& file)
{
	std::forward_list<int> flist;
	int value;

	std::forward_list<int>::iterator iterator = flist.before_begin();
	while (file >> value)
	{
		flist.insert_after(iterator, value);
		iterator++;
		size += 1;
	}

	return flist;
}

int FList::find_more_common_value()
{
	std::map<int, size_t> count;
	int max_count_value = 0;
	size_t max = 0;
	for (int value : flist)
	{
		count[value] += 1;
		if (max < count[value])
		{
			max = count[value];
			max_count_value = value;
		}
	}
	return max_count_value;
}

FList::FList(std::fstream& file)
{
	flist = fill_flist(file);
	file.close();
}

FList::FList(std::forward_list<int> new_list)
{
	flist = new_list;
}

int FList::find_sum()
{
	return std::accumulate(flist.begin(), flist.end(), 0);
}

double FList::find_average()
{
	return (double)find_sum() / size;
}

void FList::set(std::forward_list<int> new_list)
{
	flist = new_list;
}

std::forward_list<int> FList::modify_ver_1(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end)
{
	int more_common_value = find_more_common_value();
	std::forward_list<int> new_list;
	for (std::forward_list<int>::iterator flist_iterator = begin, new_list_iterator = new_list.before_begin(); flist_iterator != end; ++flist_iterator, ++new_list_iterator)
		new_list.insert_after(new_list_iterator, *flist_iterator < 0 ? *flist_iterator : more_common_value);
	return new_list;
}

std::forward_list<int> FList::modify_ver_2(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end)
{
	int more_common_value = find_more_common_value();
	std::forward_list<int> new_list(begin, end);
	std::transform(begin, end, new_list.begin(), [&more_common_value](int value)
		{
			if (value >= 0)
				value = more_common_value;
			return value;
		});
	return new_list;
}

std::forward_list<int> FList::modify_ver_3(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end)
{
	int more_common_value = find_more_common_value();
	std::forward_list<int> new_list;
	std::forward_list<int>::iterator new_list_iterator = new_list.before_begin();
	std::for_each(begin, end, [&more_common_value, &new_list, &new_list_iterator](int flist_iterator)
		{
			new_list.insert_after(new_list_iterator, flist_iterator < 0 ? flist_iterator : more_common_value);
			++new_list_iterator;
		});
	return new_list;
}

void FList::set_iterators(std::forward_list<int>::iterator& iterator_begin, std::forward_list<int>::iterator& iterator_end, int begin, int end)
{
	std::forward_list<int>::iterator iterator = flist.begin();
	while (begin != 0)
	{
		iterator++;
		begin -= 1;
		end -= 1;
	}
	iterator_begin = iterator;
	while (end >= 0)
	{
		iterator++;
		end -= 1;
	}
	iterator_end = iterator;
}

size_t FList::get_size()
{
	return size;
}

std::ostream& operator<<(std::ostream& out, const FList& forward_list)
{
	for (int value : forward_list.flist)
		out << value << ' ';
	out << '\n';
	return out;
}