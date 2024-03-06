#pragma once
#include <iostream>
#include <fstream>
#include <forward_list>
#include <string>
#include <numeric>
#include <map>
#include <algorithm>

class FList
{
private:
	std::forward_list<int> flist{};
	size_t size = 0;

	//заполнение flist из файла двум€ способами
	std::forward_list<int> fill_flist(std::fstream& file);

	//поиск самого часто встречающеос€ значени€ в листе
	int find_more_common_value();
public:
	//конструктор, заполн€ющий лист из файла с именем file_name
	FList(std::fstream& file);
	//конструктор, копирующий лист
	FList(std::forward_list<int> new_list);

	//сумма эл-ов листа
	int find_sum();

	//среднее арифметическое эл-ов листа
	double find_average();

	//переопределение листа
	void set(std::forward_list<int> new_list);

	//iterator
	std::forward_list<int> modify_ver_1(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end);

	//std::transform
	std::forward_list<int> modify_ver_2(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end);

	//std::for_each
	std::forward_list<int> modify_ver_3(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end);
	
	//установка итераторов на начало и конец прохода
	void set_iterators(std::forward_list<int>::iterator& iterator_begin, std::forward_list<int>::iterator& iterator_end, int begin, int end);

	//количество элементов
	size_t get_size();

	//перегрузка оператора вывода
	friend std::ostream& operator<<(std::ostream& out, const FList& forward_list);
};