#include "UserInteraction.h"


void ReadAndCheck(int& input, const char* message, int a, int b)
{
	std::cout << message;
	while (!(std::cin >> input) || input <= a || input >= b) // Требует вводить до тех пор, 
															 // пока данные не введены корректно
	{
		std::cout << "Ошибка ввода!";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << '\n' << message;
	}
}

int OutputMenu()
{
	std::cout << "Выберите, куда вывести матрицу\n";
	std::cout << "1. В консоль\n";
	std::cout << "2. В файл\n";
	int choice;
	ReadAndCheck(choice, "->", 0, 3);
	return choice;
}

int InputMenu()
{
	std::cout << "Выберите, откуда считывать данные, или завершите работу\n";
	std::cout << "1. Из консоли\n";
	std::cout << "2. Из файла\n";
	std::cout << "0. Завершить работу\n";
	int choice;
	ReadAndCheck(choice, "->", -1, 3);
	return choice;
}
