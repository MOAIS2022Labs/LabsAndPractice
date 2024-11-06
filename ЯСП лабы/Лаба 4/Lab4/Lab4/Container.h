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
	/// ����������� ��� ������������� �������� ��������� �� ���������� ���������������
	/// </summary>
	/// <param name="begin">�������� ������ ���������</param>
	/// <param name="end">�������� ����� ���������, �� �����������</param>
	/// <returns>���������������� ���������</returns>
	std::forward_list<int> modify_for(iterator begin, iterator end);
	/// <summary>
	/// ����������� ��� ������������� �������� ��������� �� ���������� ���������������
	/// </summary>
	/// <param name="begin">�������� ������ ���������</param>
	/// <param name="end">�������� ����� ���������, �� �����������</param>
	/// <returns>���������������� ���������</returns>
	std::forward_list<int> modify_transform(iterator begin, iterator end);
	/// <summary>
	/// ����������� ��� ������������� �������� ��������� �� ���������� ���������������
	/// </summary>
	/// <param name="begin">�������� ������ ���������</param>
	/// <param name="end">�������� ����� ���������, �� �����������</param>
	/// <returns>���������������� ���������</returns>
	std::forward_list<int> modify_for_each(iterator begin, iterator end);

	// ���������� �������� ������ ������������� ������
	iterator begin();

	// ���������� �������� ����� ������������� ������
	iterator end();

	/// <summary>
	/// ���������� �������� ��������, ������������ �� ����������� ������ number
	/// </summary>
	/// <param name="number">���������� �����, ������� � 1</param>
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
