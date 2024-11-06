#include "DemonH.h"

void read_demon(std::istream& in, Demon& demon)
{
	
	int num;
	std::string str;

	std::cout << "--- --- ---\n";
	std::cout << "Введите демона:\n";
	std::cout << "Имя > ";
	if (in >> str)
	{
		in.ignore(255, '\n');
		demon.set_name(str);

		std::cout << "Происхождение > ";
		std::getline(in, str);
		demon.set_origin(str);

		std::cout << "Рост > ";
		num = read_check_int(in, 0, 1000);
		in.ignore(255, '\n');
		demon.set_height(num);

		std::cout << "Оружие > ";
		std::getline(in, str);
		demon.set_weapon(str);

		std::cout << "Кол-во рогов (0..1000) > ";
		num = read_check_int(in, 0, 1000);
		in.ignore(255, '\n');
		demon.set_horn(num);

		std::cout << "Время жизни (0..1000) > ";
		num = read_check_int(in, 0, 1000);
		in.ignore(255, '\n');
		demon.set_time(num);

		std::cout << "Цвет > ";
		in >> str;
		num = 3;
		if (str == "Красный")
			num = 0;
		else if (str == "Синий")
			num = 1;
		else if (str == "Зелёный")
			num = 2;
		else if (str == "Белый")
			num = 3;
		demon.set_color(static_cast<Color>(num));
		std::cout << "--- --- ---\n";
	}
}

std::string Demon::get_name()
{
    return name;
}

std::string Demon::get_origin()
{
    return origin;
}

int Demon::get_height()
{
    return height;
}

std::string Demon::get_weapon()
{
    return weapon;
}

int Demon::get_horn()
{
    return horn_сount;
}

int Demon::get_time()
{
	return (int)time;
}

Color Demon::get_color()
{
    return color;
}

void Demon::set_name(std::string other_name)
{
    name = other_name;
}

void Demon::set_origin(std::string other_origin)
{
    origin = other_origin;
}

void Demon::set_height(int other_height)
{
    height = other_height;
}

void Demon::set_weapon(std::string other_weapon)
{
    weapon = other_weapon;
}

void Demon::set_horn(int other_horn_count)
{
    horn_сount = other_horn_count;
}

void Demon::set_time(int t)
{
	time = t;
}

void Demon::set_color(Color other_color)
{
    color = other_color;
}

int Demon::define_color()
{
	int colour = 15;

	switch (color)
	{
	case Color::Red:
		colour = 12;
		break;
	case Color::Blue:
		colour = 9;
		break;
	case Color::Green:
		colour = 10;
		break;
	default:
		break;
	}

	return colour;
}

bool check_demons_file(std::string file_name)
{
	std::ifstream stream(file_name);
	bool flag = true;
	std::string line;
	int i = 0;

	while (std::getline(stream, line) && flag)
	{
		if (i == 2 || i == 4 || i == 5)
		{
			try 
			{
				if ((!std::stoi(line) || (line.find(".") != std::string::npos)) && !(line == "0"))
					flag = false;
			}
			catch (...)
			{
				flag = false;
			}
		}
		else if (i == 6)
			i = -1;

		++i;
	}
	return flag;
}