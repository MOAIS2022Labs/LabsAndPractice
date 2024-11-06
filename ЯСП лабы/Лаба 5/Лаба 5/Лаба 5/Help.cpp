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
		throw std::invalid_argument("������� ������ ���!\n");
	if (mon < 1 || mon > 12)
		throw std::invalid_argument("������� ������ �����!\n");
	int days_in_month[12] = { 31, is_leap_year(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (day < 1 || day > days_in_month[mon - 1])
		throw std::invalid_argument("������� ������ ����!\n");
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
		std::cout << "������� ��� �����: ";		
		std::getline(std::cin, file_name);
		file = std::fstream(file_name);
		if (file.peek() != EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "���� � ����� ������ �� ���������� ��� �� �������� ������! ��������� ����.\n";
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
	std::cout << "�������� ������ ���������� ����������\n1. � �������\n2. �� �����\n0. �����\n";
	return read_and_check(0, 2);
}

int print_menu()
{
	std::cout << "1. ������ ���������� � �������\n2. ������ ���������� � ����\n0. �� �������� ���������\n";
	return read_and_check(0, 2);
}

int container_menu()
{
	std::cout << "1. ������ ��������� ����������\n2. ���������� ��������� � ���������\n"
		"3. �������� ��������� �� ����������\n4. ��������� ��������� ����������\n"
		"5. ������� ��������� ���������� �� ��������� ��������\n6. �������� ����������\n"
		"7. ������� ����������\n0. ��������� ������ � ������� �����������\n";
	return read_and_check(0, 7);
}

std::fstream choose_empty_file()
{
	bool out_flag = false;
	std::fstream file;
	std::string file_name;
	while (!out_flag)
	{
		std::cout << "������� ��� �����:  ";
		std::cin.ignore(255, '\n');
		std::getline(std::cin, file_name);
		file = std::fstream(file_name, std::ios::trunc | std::ios::out);
		if (file.peek() == EOF)
			out_flag = true;
		else
			file.close();
		if (!out_flag)
			std::cout << "���� � ����� ������ ��� ���������� � �������� ������! ��������� ����.\n";
	}
	std::cout << '\n';
	file.seekg(0);
	return file;
}

void show_template_multiple()
{
	std::cout << "�������� ����\n";
	std::cout << "dd.mm.yyyy\n";
	std::cout << "����� ������������� ������������/�������������/���������\n";
	std::cout << "����� �����������\n";
	std::cout << "����� �������\n";
	std::cout << "������������ �����\n";
	std::cout << "������������ ���\n";
	std::cout << "������� CTRL+Z, ����� ��������� ����\n\n";
}

void show_template_single()
{
	std::cout << "�������� ����\n";
	std::cout << "dd.mm.yyyy\n";
	std::cout << "����� ������������� ������������/�������������/���������\n";
	std::cout << "����� �����������\n";
	std::cout << "����� �������\n";
	std::cout << "������������ �����\n";
	std::cout << "������������ ���\n";
}

int selection_menu()
{
	std::cout << "��������, �� ���� ����� ������������� �������\n1. ���� ��������\n2. ������\n3. �����\n4. �����\n";
	return read_and_check(1, 4);
}

#pragma region SurpsizeBeauty

int menu_class()
{
	std::cout << "�������� ����� ��������������\n"
		<< "1. ������������\n2. �������������\n3. ���������\n";
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
				SetConsoleTextAttribute(h, (((0 << 4) | 0))); // ������
				break;
			case '#':
				SetConsoleTextAttribute(h, (((4 << 4) | 4))); // �������
				break;
			case '@':
				SetConsoleTextAttribute(h, (((255 << 0) | 255))); // �����
				break;
			case '*':
				SetConsoleTextAttribute(h, (((6 << 4) | 6))); // �����
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