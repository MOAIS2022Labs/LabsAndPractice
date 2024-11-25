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

	//���������� flist �� ����� ����� ���������
	std::forward_list<int> fill_flist(std::fstream& file);

	//����� ������ ����� ������������� �������� � �����
	int find_more_common_value();
public:
	//�����������, ����������� ���� �� ����� � ������ file_name
	FList(std::fstream& file);
	//�����������, ���������� ����
	FList(std::forward_list<int> new_list);

	//����� ��-�� �����
	int find_sum();

	//������� �������������� ��-�� �����
	double find_average();

	//��������������� �����
	void set(std::forward_list<int> new_list);

	//iterator
	std::forward_list<int> modify_ver_1(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end);

	//std::transform
	std::forward_list<int> modify_ver_2(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end);

	//std::for_each
	std::forward_list<int> modify_ver_3(std::forward_list<int>::iterator& begin, std::forward_list<int>::iterator& end);
	
	//��������� ���������� �� ������ � ����� �������
	void set_iterators(std::forward_list<int>::iterator& iterator_begin, std::forward_list<int>::iterator& iterator_end, int begin, int end);

	//���������� ���������
	size_t get_size();

	//���������� ��������� ������
	friend std::ostream& operator<<(std::ostream& out, const FList& forward_list);
};