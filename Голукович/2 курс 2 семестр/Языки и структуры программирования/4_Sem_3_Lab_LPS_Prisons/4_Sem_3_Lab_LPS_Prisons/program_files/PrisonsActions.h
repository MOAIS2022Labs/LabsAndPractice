#pragma once

#include "PrisonsMap.h"

template <typename T>
//Шаблонная функция для ввода и проверки значений
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
				std::cout << "\nПревышено количество попыток ввода!\n";
				return bad_val;
			}
			else
				std::cout << " Повторите ввод.\n";
		}
	}
	return result;
}

bool int_input(int& val);
void int_input_if_fail(int& val);

void print_villain_template();


//	меню работы с контейнером
void prison_menu(PrisonsMap& prisons, Prison* prison);

//	заполнение контейнера с помощью консоли
void fill_from_console(Prison* prison);
//	заполнение контейнера с помощью файла
void fill_from_file(Prison* prison);

//	добавление злодеев в контейнер
void add_to_prison(Prison* prison, Prison* wanted);

//	удаление злодеев из контейнера
bool remove_from_prison(Prison* prison, Prison* wanted);

//	изменение данных злодея в контейнере
void edit_prison(Prison* prison, Prison* wanted);

//	выборка злодеев из контейнера
void select_from_prison(Prison* prison);
std::function<bool(Villain&)> get_nickname_selector();
std::function<bool(Villain&)> get_data_selector();
std::function<bool(Villain&)> get_creature_selector();

//	печать последнего злодея из контейнера
void release_last_from_prison(Prison* prison);

// перемещение злодея из одной тюрьмы в другую
void move_villain(Prison* prison_from, Prison* prison_to);