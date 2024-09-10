//Голукович Тимофей 2 курс 9 группа 

//20 задача
//Создать класс Binary для работы с беззнаковыми целыми двоичными числами,
//используя для представления массив из 100 элементов типа unsigned char,
//каждый элемент котоорого является двоичной цифрой.
//Младшая цифра имеет младший индекс (единицы - в нулевом элементе массива).
//Реальный размер задается как аргумент конструктора инициализации.
//Реалтзовать арифметические операции, аналогичные встроенным для целых в C++, и операции сравнения.

#include "Bin.h"
#include <Windows.h>

void pick_and_check(int& choice, const int a, const int b, const char* message);

Binary pick_num();

void one_number_menu(Binary& num_l);

void two_numbers_menu();

void main_menu(int choice);

int main()
{
	SetConsoleOutputCP(1251);

	//Binary num("1010");
	//std::cout << num.to_cstring();

	int choice = 1;
	while (choice)
	{
		pick_and_check(choice, 0, 2, "\nРабота с одним числом >> 1\nРабота с двумя числами >> 2\nЗавершить работу прогаммы >> 0\n");
		main_menu(choice);
	}
	std::cin.get();
	return 0;
}

void pick_and_check(int& choice, const int a, const int b, const char* message)
{
	std::cout << message;
	bool flag_of_out = false;
	while (!flag_of_out)
	{
		if (std::cout << ">> " && std::cin >> choice && a <= choice && choice <= b) //ввод целого числа и проверка на попадание в диапазон от a до b
			flag_of_out = true;
		else
		{
			std::cout << "\nОшибка ввода! Повторите ввод\n";
			std::cin.clear(); //очистка флагов потока cin
			std::cin.ignore(255, '\n');
		}	
	}
}

Binary pick_num()
{
	try //конструкция для отлова исключений
	{
		int choice;
		Binary result;
		pick_and_check(choice, 1, 2, "Ввод числа вручную >> 1\nВвод числа с помощью текстового файла >> 2\n");
		if (choice == 1)
		{
			pick_and_check(choice, 0, MAX, "Введите размер числа в битах\n");
			result = Binary(choice); //инициализация бинарного числа
		}
		else
			if (choice == 2)
			{
				char* name_of_file = new char[255];
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "Введите имя файла >> ";
				std::cin.getline(name_of_file, 255);
				std::ifstream file(name_of_file);
				if (file)
					result = Binary(file); //инициализация бинарного числа с помощью файла
				else
					throw Error(404, "File cannot be opend correctly!");
				file.close();
				delete[] name_of_file;
				name_of_file = nullptr;
			}
		return result;
	}
	catch (const Error error) { throw error; } //обработка исключения
}

void one_number_menu(Binary& num_l)
{
	int choice = 1;
	while (choice != 0)
	{
		pick_and_check(choice, 0, 9, "Напечатать текущее число >> 1\nНапечатать текущее число в файл >> 2\nУвеличить текущее число на новое >> 3\nУменьшить текущее число на новое >> 4\nУмножить текущее число на новое >> 5\nРазделить текущее число на новое >> 6\nОстаток от деления текущего числа на новое >> 7\nУвеличить текущее число на 1 >> 8\nУменьшить текущее число на 1 >> 9\nЗавершить работу с текущим числом >> 0\n");
		try
		{
			Binary num_r;
			switch (choice)
			{
			case 1:
				std::cout << "\nТекущее число >> " << num_l << "\n\n";
				break;
			case 2:
			{
				char* name_of_file = new char[255];
				std::cout << "Введите имя файла >> ";
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cin.getline(name_of_file, 255);
				std::ofstream file(name_of_file);
				if (file)
					file << num_l << '\n';
				else
					throw Error(404, "File cannot be opend correctly!");
				file.close();
				break;
			}
			case 3:
				num_r = pick_num(); //инициализация второго числа
				std::cout << ' ' << num_l << "\n+\n " << num_r << "\n=\n ";;
				num_l += num_r;
				std::cout << num_l << "\n\n";
				break;
			case 4:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n-\n " << num_r << "\n=\n ";;
				num_l -= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 5:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n*\n " << num_r << "\n=\n ";;
				num_l *= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 6:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n/\n " << num_r << "\n=\n ";;
				num_l /= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 7:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n%\n " << num_r << "\n=\n ";;
				num_l %= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 8:
				++num_l;
				break;
			case 9:
				--num_l;
				break;
			default:
				break;
			}
		}
		catch (const Error error) { error.print_Error(); } //обработка исключения (печать ошибки в консоль)
	}
}

void two_numbers_menu()
{
	try
	{
		Binary num_l = pick_num();
		Binary num_r = pick_num();
		int choice = 1;
		pick_and_check(choice, 0, 5, "Сложение первого и второго чисел >> 1\nВычесть из первого числа второе >> 2\nУмножить первое число на второе >> 3\nРазделить первое число на второе >> 4\nОстаток от деления первого числа на второе >> 5\n");
		switch (choice)
		{
		case 1:
			std::cout << ' ' << num_l << "\n+\n " << num_r << "\n=\n " << num_l + num_r << "\n\n";
			break;
		case 2:
			std::cout << ' ' << num_l << "\n-\n " << num_r << "\n=\n " << num_l - num_r << "\n\n";
			break;
		case 3:
			std::cout << ' ' << num_l << "\n*\n " << num_r << "\n=\n " << num_l * num_r << "\n\n";
			break;
		case 4:
			std::cout << ' ' << num_l << "\n/\n " << num_r << "\n=\n " << num_l % num_r << "\n\n";
			break;
		case 5:
			std::cout << ' ' << num_l << "\n%\n " << num_r << "\n=\n " << num_l % num_r << "\n\n";
			break;
		}
	}
	catch (const Error error) { throw error; }
}

void main_menu(int choice)
{
	try
	{
		if (choice == 1)
		{
			Binary num = pick_num();
			one_number_menu(num);
		}
		if (choice == 2)
			two_numbers_menu();
	}
	catch (const Error error) { error.print_Error(); }
}