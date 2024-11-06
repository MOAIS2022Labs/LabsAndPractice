// Канатников Максим Андреевич 9 группа
/*
5. Реализовать шаблон класса дек Deque<X>, хранящий элементы произвольного типа.
Класс должен в обязательном порядке содержать методы:
- Добавление нового элемента в конец push_back;
- Добавление нового элемента в начало push_front;
- Получение значения первого элемента;
- Получение значения последнего элемента;
- Извлечение элемента из начала pop_front;
- Извлечение элемента из конца pop_back;
- Инициализация очереди из файла используя добавление в конец;
- Инициализация очереди из файла используя добавление в начало;
- Запись дека в файл без его очистки;
- Вычисление длины дека;
- Печать дека без его очистки.
A. Реализация дека на основе массива
*/

#include "Deque.h"
#include <Windows.h>
#include <string>
#include "Time.h"
#include <sstream>

enum Type
{	
	INTEGER = 1,
	STRING,
	TIME
};

bool is_number(std::string str);

bool is_unsigned_number(std::string str);

// проверка файла на корректность хранимых данных
bool check_file(std::string& fname, const Type& type);

std::string choose_in_file_name(const Type& type);

std::string choose_out_file_name();

void read_and_check(int& input, const char* message, int a, int b);

// выбор типа шаблонного дека
Type choose_type();

int main_menu();

// демонстрация возможностей шаблонного класса
template <typename T>
void demonstration(Deque<T>& deq, const Type& type);

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Type choice{};
	while (true)
	{
		choice = choose_type();
		switch (choice)
		{
		case INTEGER:
		{
			Deque<int> deq;
			demonstration(deq, choice);
			break;
		}
		case STRING:
		{
			Deque<std::string> deq;
			demonstration(deq, choice);
			break;
		}
		case TIME:
		{
			Deque<Time> deq;
			demonstration(deq, choice);
			break;
		}
		}

		char is_exit{};
		std::cout << "Завершить выполнение программы? 0, если да\n-> ";
		std::cin >> is_exit;
		if (is_exit == '0')
			break;
		std::cout << "------------------------------------------------------------------------\n";
	}
	return 0;
}


bool is_number(std::string str)
{
	return !str.empty() && (str.find_first_not_of("-0123456789") == std::string::npos);
}

bool is_unsigned_number(std::string str)
{
	return !str.empty() && (str.find_first_not_of("0123456789") == std::string::npos);
}

bool check_file(std::string& fname, const Type& type)
{
	std::ifstream file(fname.c_str());
	bool result = true;
	if (!file)
		result = false; 
	else
	{
		switch (type)
		{
		case INTEGER:
		{
			std::string line;
			while (std::getline(file, line) && result)
			{
				std::stringstream ss(line);
				std::string word;
				while (ss >> word && result)
				{
					if (!is_number(word))
						result = false;
				}
			}
			break;
		}
		case STRING:
			break;
		case TIME:
			std::string line;
			size_t count = 0;
			while (std::getline(file, line) && result)
			{
				std::stringstream ss(line);
				std::string word;
				while (ss >> word && result)
				{
					if (!is_unsigned_number(word) || (count % 3 == 0 && std::stoi(word) >= 24) || (count % 3 != 0 && std::stoi(word) >= 60))
						result = false;
					++count;
				}
			}
			if (count % 3 != 0)
				result = false;
			break;
		}
	}
	file.close();
	return result;
}

std::string choose_out_file_name()
{
	std::cout << "Введите имя файла: ";
	std::string fname;
	std::cin >> fname;
	return fname;
}

std::string choose_in_file_name(const Type& type)
{
	std::cout << "Введите имя файла: ";
	std::string fname;
	std::cin >> fname;
	while (!check_file(fname, type))
	{
		std::cout << "Ошибка, введите другое имя файла: ";
		std::cin >> fname;
	}
	return fname;
}

void read_and_check(int& input, const char* message, int a, int b)
{
	std::cin.clear();
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

Type choose_type()
{
	std::cout << "Выберите тип данных\n";
	std::cout << "1. Целочисленный\n";
	std::cout << "2. Строковый\n";
	std::cout << "3. Пользовательский\n";
	int choice;
	read_and_check(choice, "->\t", 1, 3);
	std::cout << '\n';
	return (Type)choice;
}

int main_menu()
{
	std::cout << "------------------------------------------------------------------------\n";
	std::cout << "Выберите операцию\n";
	std::cout << "1. Инициализация дека из файла используя добавление в конец\n";
	std::cout << "2. Инициализация дека из файла используя добавление в начало\n";	
	std::cout << "3. Добавить элемент в конец\n";
	std::cout << "4. Добавить элемент в начало\n";
	std::cout << "5. Получение значения первого элемента\n";
	std::cout << "6. Получение значения последнего элемента\n";
	std::cout << "7. Извлечение элемента из начала (pop)\n";
	std::cout << "8. Извлечение элемента из конца (pop)\n";
	std::cout << "9. Вычисление длины дека\n";
	std::cout << "10. Печать дека в консоль\n";
	std::cout << "11. Печать дека в файл\n";
	std::cout << "0. Закончить\n";
	int choice;
	read_and_check(choice, "->\t", 0, 11);
	std::cout << "------------------------------------------------------------------------\n";
	return choice;
}

template<typename T>
void demonstration(Deque<T>& deq, const Type& type)
{
	int choice{};
	do
	{
		choice = main_menu();
		switch (choice)
		{
		case 1: // инициализация через добавление в конец
		{
			std::string fname = choose_in_file_name(type);
			std::ifstream file(fname);
			deq.init_by_push_back(file);
			file.close();
			std::cout << "Дек успешно инициализирован\n";
			break;
		}
		case 2: // инициализация через добавление в начало
		{
			std::string fname = choose_in_file_name(type);
			std::ifstream file(fname);
			deq.init_by_push_front(file);
			std::cout << "Дек успешно инициализирован\n";
			file.close();
			break;
		}
		case 3: // добавление в конец
		{
			T value;
			try
			{
				if (std::cin >> value)
				{
					deq.push_back(value);
					std::cout << "Элемент добавлен в конец дека\n";
				}
				else
				{
					std::cout << "Данные не корректны\n";
				}
			}
			catch (std::invalid_argument ex)
			{
				std::cout << ex.what() << '\n';
			}
			catch (std::exception ex)
			{
				std::cout << ex.what() << '\n';
			}
			std::cin.clear();
			std::cin.ignore(255, '\n');
			break;
		}
		case 4: // добавление в начало
		{
			T value;
			try
			{
				if (std::cin >> value)
				{
					deq.push_front(value);
					std::cout << "Элемент добавлен в конец дека\n";
				}
				else
				{
					std::cout << "Данные не корректны\n";
					std::cin.clear();
					std::cin.ignore(255, '\n');
				}
			}
			catch (std::invalid_argument ex)
			{
				std::cout << ex.what() << '\n';
			}
			catch (std::exception ex)
			{
				std::cout << ex.what() << '\n';
			}
			std::cin.clear();
			std::cin.ignore(255, '\n');
			break;
		}
		case 5: // получение значения первого элемента
			try
			{
				std::cout << deq.front() << '\n';
			}
			catch (std::out_of_range ex)
			{
				std::cout << ex.what() << '\n';
			}
			break;
		case 6: // получение значения последнего элемента
			try
			{
				std::cout << deq.back() << '\n';
			}
			catch (std::out_of_range ex)
			{
				std::cout << ex.what() << '\n';
			}
			break;
		case 7: // извлечение элемента из начала
			try
			{
				std::cout << deq.pop_front() << '\n';
			}
			catch (std::out_of_range ex)
			{
				std::cout << ex.what();
			}
			break;
		case 8: // извлечение элемента из конца
			try
			{
				std::cout << deq.pop_back() << '\n';
			}
			catch (std::out_of_range ex)
			{
				std::cout << ex.what();
			}
			break;
		case 9: // извлечение длины дека
			std::cout << deq.get_size() << '\n';
			break;
		case 10: // печать дека в консоль
		{
			char separator = type == TIME ? '\n' : ' ';
			deq.print(std::cout, separator);
			break;
		}
		case 11: // печать дека в файл
		{
			{
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				char separator = type == TIME ? '\n' : ' ';
				deq.print(file, separator);
				file.close();
				std::cout << "Данные записаны в файл " << fname << '\n';
				break;
			}
		}
		}
	} while (choice);
}
