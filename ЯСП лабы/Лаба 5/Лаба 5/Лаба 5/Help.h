#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

template <typename T>
T read_and_check(T min, T max)
{
	std::cin.clear();
	T input;
	std::cout << "-> ";
	while (!(std::cin >> input) || input > max || input < min)
	{
		std::cout << "Ошибка ввода!\n";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << "-> ";
	}
	return input;
}

std::string date_to_string(int day, int mon, int year);

bool is_leap_year(int year);

tm read_date(std::istream& in);

std::fstream choose_file();

int menu_class();

int fill_menu();

int print_menu();

int container_menu();

std::fstream choose_empty_file();

void show_template_multiple();

void show_template_single();

int selection_menu();








void surprise(int type);
