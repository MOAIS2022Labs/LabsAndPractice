#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum Monster
{
	Vampire = 1, Zombie, Ghost, Werwolf, Skeleton, EvilClown, NotSpecified
};

class Villain
{
private:
	std::string nickname{};
	std::string name{};
	Monster creature = NotSpecified;
	tm date;
	bool is_catched = false;
	int compare_date(const tm& value);
public:
	//неинициализирующий конструктор
	Villain() { date.tm_mday = 1; };

	//инициализирующий конструктор
	Villain(std::string nickname, std::string name, Monster creature, tm date, bool is_catched) :
		nickname(nickname), name(name), creature(creature), date(date), is_catched(is_catched) {}

	//компаратор
	int compare(const Villain& value);

	//геттеры

	std::string get_nickname();
	std::string get_name();
	Monster get_creature();
	tm get_date();
	bool get_is_catched();

	//перегрузка оператора вывода
	friend std::ostream& operator<<(std::ostream& out, const Villain& villain)
	{
		if (villain.nickname.empty())
		{
			out << '\n';
			return out;
		}
		out << villain.nickname << '\n';

		if (villain.is_catched)
			out << villain.name << '\n';
		else
		{
			for (int i = 0; i < (int)villain.name.size(); ++i)
				out << '*';
			out << '\n';
		}

		switch (villain.creature) 
		{
		case Vampire:
			out << "Vampire\n";
			break;
		case Zombie:
			out << "Zombie\n";
			break;
		case Ghost:
			out << "Ghost\n";
			break;
		case Werwolf:
			out << "Werwolf\n";
			break;
		case Skeleton:
			out << "Skeleton\n";
			break;
		case EvilClown:
			out << "EvilClown\n";
			break;
		default:
			out << "NotSpecified\n";
			break;
		}

		out << villain.date.tm_mday + 1 << ' ' << villain.date.tm_mon + 1 << ' ' << villain.date.tm_year + 1900 << '\n';
		out << villain.date.tm_hour << ' ' << villain.date.tm_min << ' ' << villain.date.tm_sec << '\n';

		if (villain.is_catched)
			out << "Catched\n";
		else
			out << "Wanted\n";
		return out;
	}
	
	//перегрузка оператора вывода
	friend std::istream& operator>>(std::istream& in, Villain& villain)
	{
		std::string str;
		std::getline(in, str);
		if (str.find_first_not_of('-') == std::string::npos)
		{
			in.setstate(std::ios::badbit);
			return in;
		}
		villain.nickname = str;

		std::getline(in, str);
		villain.name = str;
		
		std::getline(in, str);
		if (!(str == "Vampire" && (villain.creature = Vampire)) && !(str == "Zombie" && (villain.creature = Zombie))
			&& !(str == "Ghost" && (villain.creature = Ghost)) && !(str == "Werwolf" && (villain.creature = Werwolf))
			&& !(str == "Skeleton" && (villain.creature = Skeleton)) && !(str == "EvilClown" && (villain.creature = EvilClown))
			&& !(str == "NotSpecified" && (villain.creature = NotSpecified)))
		{
			throw std::invalid_argument("Монстр!");
		}

		int value;
		if (in >> value && value >= 1 && value <= 31)
			villain.date.tm_mday = value;
		else
			throw std::invalid_argument("День!");
		if (in >> value && value >= 1 && value <= 12)
		{
			if (villain.date.tm_mday > 29 && value == 2)
				throw std::invalid_argument("В феврале не может быть больше 29 дней!");
			else
				villain.date.tm_mon = value - 1;
		}
		else
			throw std::invalid_argument("Месяц!");
		if (in >> value)
			villain.date.tm_year = value - 1900;
		else
			throw std::invalid_argument("Год!");
		if (in >> value && value >= 0 && value <= 23)
			villain.date.tm_hour = value;
		else
			throw std::invalid_argument("Час!");
		if (in >> value && value >= 0 && value <= 59)
			villain.date.tm_min = value;
		else
			throw std::invalid_argument("Минута!");
		if (in >> value && value >= 0 && value <= 59)
			villain.date.tm_sec = value;
		else
			throw std::invalid_argument("Секунда!");

		in.ignore(255, '\n');
		str = std::string{};
		std::getline(in, str);
		if (!(str == "Catched" && (villain.is_catched = true))
			&& !(str == "Wanted" && (!(villain.is_catched = false))))
			throw std::invalid_argument("Пойман ли!");
		return in;
	}

	bool operator>(const Villain& value)
	{
		if (compare(value) > 0)
			return false;
		return true;
	}

	bool operator>=(const Villain& value)
	{
		if (compare(value) >= 0)
			return true;
		return false;
	}

	bool operator<(const Villain& value)
	{
		if (compare(value) < 0)
			return true;
		return false;
	}

	bool operator<=(const Villain& value)
	{
		if (compare(value) <= 0)
			return true;
		return false;
	}

	bool operator==(const Villain& value)
	{
		if (compare(value) == 0)
			return true;
		return false;
	}

	bool operator!=(const Villain& value)
	{
		if (compare(value) != 0)
			return true;
		return false;
	}
};