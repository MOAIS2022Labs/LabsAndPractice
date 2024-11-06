#pragma once
#include <iostream>
#include <fstream>
#include <forward_list>
#include <algorithm>

using iterator = std::forward_list<int>::iterator;

class Container
{

public:
	
	Container(std::fstream& file);	

	/// <summary>
	/// увеличивает все положительные элементы диапазона на количество неотрицательных
	/// </summary>
	/// <param name="begin">итератор начала диапазона</param>
	/// <param name="end">итератор конца диапазона, не учитывается</param>
	/// <returns>модифицированная коллекция</returns>
	std::forward_list<int> modify_for(iterator begin, iterator end);
	/// <summary>
	/// увеличивает все положительные элементы диапазона на количество неотрицательных
	/// </summary>
	/// <param name="begin">итератор начала диапазона</param>
	/// <param name="end">итератор конца диапазона, не учитывается</param>
	/// <returns>модифицированная коллекция</returns>
	std::forward_list<int> modify_transform(iterator begin, iterator end);
	/// <summary>
	/// увеличивает все положительные элементы диапазона на количество неотрицательных
	/// </summary>
	/// <param name="begin">итератор начала диапазона</param>
	/// <param name="end">итератор конца диапазона, не учитывается</param>
	/// <returns>модифицированная коллекция</returns>
	std::forward_list<int> modify_for_each(iterator begin, iterator end);

	// возвращает итератор начала направленного списка
	iterator begin();

	// возвращает итератор конца направленного списка
	iterator end();

	/// <summary>
	/// возвращает итератор элемента, находящегося по порядковому номеру number
	/// </summary>
	/// <param name="number">порядковый номер, начиная с 1</param>
	iterator get_iterator(const size_t number);

	int sum();

	double average();

	void print_console();
	void print_file(const std::string& fname);
	friend std::ostream& operator<<(std::ostream& out, const Container& container);

private:

	std::forward_list<int> fl;

	int _count_non_negative(iterator begin, iterator end);

};
