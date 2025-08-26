#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum Monster
{
	Vampire = 1, Zombie, Ghost, Werwolf, Skeleton, EvilClown, NotSpecified
};

int compare_date(const tm& left_value, const tm& right_value);
tm input_date(std::istream& in);

class Villain
{
private:
	std::string nickname{};
	std::string name{};
	Monster creature = NotSpecified;
	tm date;
	bool is_catched = false;
public:
	//неинициализирующий конструктор
	Villain() { date.tm_mday = 1; };

	//инициализирующий конструктор
	Villain(std::string nickname, std::string name, Monster creature, tm date, bool is_catched) :
		nickname(nickname), name(name), creature(creature), date(date), is_catched(is_catched) {}

	//компаратор
	int compare(const Villain& value);

	//геттеры

	std::string get_nickname() const;
	std::string get_name() const;
	Monster get_creature() const;
	tm get_date() const;
	bool get_is_catched() const;

	bool set_is_catched(bool state);

	//перегрузка оператора вывода
	friend std::ostream& operator<<(std::ostream& out, const Villain& villain)
	{
		if (villain.nickname.empty())
			return out;

		out << villain.nickname << '\n';

		if (!villain.is_catched && &out == &std::cout)
		{
			for (int i = 0; i < (int)villain.name.size(); ++i)
				out << '*';
			out << '\n';
		}
		else
			out << villain.name << '\n';

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

		villain.date = input_date(in);

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