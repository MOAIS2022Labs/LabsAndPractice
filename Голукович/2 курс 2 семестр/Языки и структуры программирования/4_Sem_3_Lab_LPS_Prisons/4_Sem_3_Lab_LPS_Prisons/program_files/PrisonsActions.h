#pragma once

#include "PrisonsMap.h"

template <typename T>
//��������� ������� ��� ����� � �������� ��������
T pick_and_check(const char* message, std::function<bool(T&)> task, std::function<bool(T&)> predicate,
	std::function<void(T&)> if_fail = []() {}, int max = -1, T bad_val = T())
{
	std::cout << message;
	T result;
	bool flag_of_out = false;
	while (!flag_of_out && max != 0)
	{
		if (task(result) && predicate(result))
			flag_of_out = true;
		else
		{
			max--;
			if_fail(result);
			if (max == 0)
			{
				std::cout << "\n��������� ���������� ������� �����!\n";
				return bad_val;
			}
			else
				std::cout << " ��������� ����.\n";
		}
	}
	return result;
}

bool int_input(int& val);
void int_input_if_fail(int& val);

void print_villain_template();


//	���� ������ � �����������
void prison_menu(PrisonsMap& prisons, Prison* prison);

//	���������� ���������� � ������� �������
void fill_from_console(Prison* prison);
//	���������� ���������� � ������� �����
void fill_from_file(Prison* prison);

//	���������� ������� � ���������
void add_to_prison(Prison* prison, Prison* wanted);

//	�������� ������� �� ����������
bool remove_from_prison(Prison* prison, Prison* wanted);

//	��������� ������ ������ � ����������
void edit_prison(Prison* prison, Prison* wanted);

//	������� ������� �� ����������
void select_from_prison(Prison* prison);
std::function<bool(Villain&)> get_nickname_selector();
std::function<bool(Villain&)> get_data_selector();
std::function<bool(Villain&)> get_creature_selector();

//	������ ���������� ������ �� ����������
void release_last_from_prison(Prison* prison);

// ����������� ������ �� ����� ������ � ������
void move_villain(Prison* prison_from, Prison* prison_to);