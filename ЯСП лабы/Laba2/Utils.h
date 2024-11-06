#pragma once
#include <iostream>
template<class X>
bool is_valid_input(X& info)
{
	bool isCorrectInfo = false;
	while (!isCorrectInfo)
	{
		std::cin >> info;
		if (!std::cin.fail())
			isCorrectInfo = true;
		else
		{
			std::cout << "Ошибка. Попробуйте снова.\n --> ";
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}
	}
	return isCorrectInfo;
}
template<class X>
X input_in_range(X min, X max)
{
	int choice;
	while (!is_valid_input(choice) || !(choice >= min && choice <= max))
	{
		std::cout << "Неверный ввод, попробуйте ещё раз\n-->";
	}
	return choice;
}