#include "Help.h"

bool is_leap_year(int year)
{
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 != 0)
		return false;
	return true;
}

tm read_date(std::istream& in)
{
	int day, mon, year;
	std::string str;
	std::getline(in, str);
	day = std::stoi(str.substr(0, 2));
	mon = std::stoi(str.substr(3, 5));
	year = std::stoi(str.substr(6, 10));
	if (year < 1)
		throw std::invalid_argument("Неверно указан год!\n");
	if (mon < 1 || mon > 12)
		throw std::invalid_argument("Неверно указан месяц!\n");
	int days_in_month[12] = { 31, is_leap_year(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (day < 1 || day > days_in_month[mon - 1])
		throw std::invalid_argument("Неверно указан день!\n");
	tm t;
	t.tm_year = year - 1900;
	t.tm_mon = mon - 1;
	t.tm_mday = day;
	return t;
}

std::fstream choose_file()
{
	bool flag_of_out = false;
	std::string file_name;
	std::fstream file;
	while (!flag_of_out)
	{
		std::cout << "Введите имя файла: ";		
		std::getline(std::cin, file_name);
		file = std::fstream(file_name);
		if (file.peek() != EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "Файл с таким именем не существует или не содержит данные! Повторите ввод.\n";
	}
	std::cout << '\n';
	return file;
}

std::string date_to_string(int day, int mon, int year)
{
	std::string _day = day < 10 ? "0" + std::to_string(day) : std::to_string(day);
	std::string _mon = mon < 10 ? "0" + std::to_string(mon) : std::to_string(mon);
	std::string _year{};
	if (year < 10)
		_year += "000";
	else
	{
		if (year < 100)
			_year += "00";
		else
		{
			if (year < 1000)
				_year += "0";
		}
	}
	return _day + "." + _mon + "." + _year + std::to_string(year);;
}

int fill_menu()
{
	std::cout << "Выберете способ заполнения контейнера\n1. С консоли\n2. Из файла\n0. Выход\n";
	return read_and_check(0, 2);
}

int print_menu()
{
	std::cout << "1. Печать контейнера в консоль\n2. Печать контейнера в файл\n0. Не печатать контейнер\n";
	return read_and_check(0, 2);
}

int container_menu()
{
	std::cout << "1. Печать элементов контейнера\n2. Добавление элементов в контейнер\n"
		"3. Удаление элементов из контейнера\n4. Изменение элементов контейнера\n"
		"5. Выборка элементов контейнера по заданному критерию\n6. Удаление дубликатов\n"
		"7. Очистка контейнера\n0. Закончить работу с текущим контейнером\n";
	return read_and_check(0, 7);
}

std::fstream choose_empty_file()
{
	bool out_flag = false;
	std::fstream file;
	std::string file_name;
	while (!out_flag)
	{
		std::cout << "Введите имя файла:  ";
		std::cin.ignore(255, '\n');
		std::getline(std::cin, file_name);
		file = std::fstream(file_name, std::ios::trunc | std::ios::out);
		if (file.peek() == EOF)
			out_flag = true;
		else
			file.close();
		if (!out_flag)
			std::cout << "Файл с таким именем уже существует и содержит данные! Повторите ввод.\n";
	}
	std::cout << '\n';
	file.seekg(0);
	return file;
}

void show_template_multiple()
{
	std::cout << "Название вида\n";
	std::cout << "dd.mm.yyyy\n";
	std::cout << "Класс членистоногоо Ракообразное/Паукообразное/Насекомое\n";
	std::cout << "Число конечностей\n";
	std::cout << "Число крыльев\n";
	std::cout << "Максимальная длина\n";
	std::cout << "Максимальный вес\n";
	std::cout << "Введите CTRL+Z, чтобы закончить ввод\n\n";
}

void show_template_single()
{
	std::cout << "Название вида\n";
	std::cout << "dd.mm.yyyy\n";
	std::cout << "Класс членистоногоо Ракообразное/Паукообразное/Насекомое\n";
	std::cout << "Число конечностей\n";
	std::cout << "Число крыльев\n";
	std::cout << "Максимальная длина\n";
	std::cout << "Максимальный вес\n";
}

int selection_menu()
{
	std::cout << "Выберете, по чему будет производиться выборка\n1. Дата открытия\n2. Размер\n3. Масса\n4. Класс\n";
	return read_and_check(1, 4);
}

#pragma region SurpsizeBeauty

int menu_class()
{
	std::cout << "Выберете класс членистоногого\n"
		<< "1. Ракообразное\n2. Паукообразное\n3. Насекомое\n";
	int choice = read_and_check(1, 3);
	surprise(choice);
	return choice;
}

void draw(std::ifstream& file, int foreground)
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	const int WIDTH = 45;
	SetConsoleTextAttribute(h, (((foreground << 4) | foreground)));
	for (int i = 0; i < WIDTH; ++i)
		std::cout << ' ';
	SetConsoleTextAttribute(h, (((0 << 4) | 15)));
	std::cout << '\n';
	while (!file.eof())
	{
		std::string str;
		std::getline(file, str);
		int i = 0;
		for (; i < str.length(); ++i)
		{
			switch (str[i])
			{
			case '$':
				SetConsoleTextAttribute(h, (((0 << 4) | 0))); // чёрный
				break;
			case '#':
				SetConsoleTextAttribute(h, (((4 << 4) | 4))); // красный
				break;
			case '@':
				SetConsoleTextAttribute(h, (((255 << 0) | 255))); // белый
				break;
			case '*':
				SetConsoleTextAttribute(h, (((6 << 4) | 6))); // жёлтый
				break;
			default:
				SetConsoleTextAttribute(h, (((foreground << 4) | foreground)));
				break;
			}
			std::cout << str[i];
		}
		SetConsoleTextAttribute(h, (((foreground << 4) | foreground)));
		for (; i < WIDTH; ++i)
			std::cout << ' ';
		SetConsoleTextAttribute(h, (((0 << 4) | 15)));
		std::cout << '\n';
	}
	std::cout << '\n';
}

void surprise(int type)
{
	std::ifstream file(type == 1 ? "Crab.txt" : (type == 2 ? "Spider.txt" : "Bee.txt"));
	draw(file, type == 1 ? 6 : (type == 2 ? 255 : 3));
	file.close();
}

#pragma endregion