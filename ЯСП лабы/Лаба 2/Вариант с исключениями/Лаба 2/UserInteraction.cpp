#include "UserInteraction.h"

void read_and_check(unsigned short& input, const char* message, int a, int b)
{
	std::cout << message;
	while (!(std::cin >> input) || input < a || input > b) // Требует вводить до тех пор, 
														   // пока данные не введены корректно
	{
		std::cout << "Ошибка ввода!";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << '\n' << message;
	}
}

void read_and_check(std::string& str, const char* message)
{
	std::cout << message;
	std::cin >> str;
	while (!condition_string(str))
	{
		std::cout << "Ошибка ввода!\n" << message;
		std::cin >> str;
	}
}

bool check_file(std::string& fname)
{
	std::ifstream file(fname.c_str());
	int result = 1;
	if (!file)
		result = 0;
	file.close();
	return result;
}

int initialization_menu()
{
	std::cout << "Выберите способ инициализации времени\n";
	std::cout << "1. Числами\n";
	std::cout << "2. Строкой\n";
	std::cout << "3. Секундами\n";
	std::cout << "4. Временем\n";
	std::cout << "0. Завершить работу\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 0, 4);
	std::cout << '\n';
	return choice;
}

int action_menu()
{
	std::cout << "\nВыберите действие\n";
	std::cout << "1.  Вычесть некоторое количество секунд\n";
	std::cout << "2.  Добавить некоторое количество секунд\n";
	std::cout << "3.  Перевести время в секунды\n";
	std::cout << "4.  Перевести время в минуты\n";
	std::cout << "5.  Вывести момент времени на экран\n";
	std::cout << "6.  Напечатать момент времени в файл\n";
	std::cout << "7.  Вывести на экран строковое представление\n";
	std::cout << "8.  Сложить 2 момента времени\n";
	std::cout << "9.  Сложить время и секунды\n";
	std::cout << "10. Вычесть один момент времени из второго\n";
	std::cout << "11. Вычесть секунды из времени\n";
	std::cout << "12. Проверить моменты времени на равенство\n";
	std::cout << "13. Проверить моменты времени на неравенство(!=)\n";
	std::cout << "14. Проверить моменты времени на неравенство(>)\n";
	std::cout << "15. Проверить моменты времени на неравенство(<)\n";
	std::cout << "16. Проверить моменты времени на неравенство(>=)\n";
	std::cout << "17. Проверить моменты времени на неравенство(<=)\n";
	std::cout << "18. Вычислить разницу в секундах между двумя моментами времени\n";
	std::cout << "0.  Закончить действия с текущим моментом времени\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 0, 18);
	std::cout << '\n';
	return choice;
}

int input_menu()
{
	std::cout << "Выберите, откуда считать данные\n";
	std::cout << "1. Из консоли\n";
	std::cout << "2. Из файла\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 1, 2);
	std::cout << '\n';
	return choice;
}

int output_menu()
{
	std::cout << "Выберите, куда вывести данные\n";
	std::cout << "1. В консоль\n";
	std::cout << "2. В файл\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 1, 2);
	std::cout << '\n';
	return choice;
}

std::string choose_out_file_name()
{
	std::cout << "Введите имя файла: ";
	std::string fname;
	std::cin >> fname;
	return fname;
}

std::string choose_in_file_name()
{
	std::cout << "Введите имя файла: ";
	std::string fname;
	std::cin >> fname;
	while (!check_file(fname))
	{
		std::cout << "Ошибка, введите другое имя файла: ";
		std::cin >> fname;
	}
	return fname;
}
