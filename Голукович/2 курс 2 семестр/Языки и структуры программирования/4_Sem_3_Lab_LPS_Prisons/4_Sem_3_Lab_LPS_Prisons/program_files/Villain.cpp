#include "Villain.h"

int compare_date(const tm& left_value, const tm& right_value)
{
	if (left_value.tm_year > right_value.tm_year)
		return 1;
	if (left_value.tm_year < right_value.tm_year)
		return -1;

	if (left_value.tm_mon > right_value.tm_mon)
		return 1;
	if (left_value.tm_mon < right_value.tm_mon)
		return -1;

	if (left_value.tm_mday > right_value.tm_mday)
		return 1;
	if (left_value.tm_mday < right_value.tm_mday)
		return -1;

	if (left_value.tm_hour > right_value.tm_hour)
		return 1;
	if (left_value.tm_hour < right_value.tm_hour)
		return -1;

	if (left_value.tm_min > right_value.tm_min)
		return 1;
	if (left_value.tm_min < right_value.tm_min)
		return -1;

	if (left_value.tm_sec > right_value.tm_sec)
		return 1;
	if (left_value.tm_sec < right_value.tm_sec)
		return -1;

	return 0;
}

tm input_date(std::istream& in)
{
	tm date;
	int value;
	if (in >> value && value >= 1 && value <= 31)
		date.tm_mday = value;
	else
		throw std::invalid_argument("День!");
	if (in >> value && value >= 1 && value <= 12)
	{
		if (date.tm_mday > 29 && value == 2)
			throw std::invalid_argument("В феврале не может быть больше 29 дней!");
		else
			date.tm_mon = value - 1;
	}
	else
		throw std::invalid_argument("Месяц!");
	if (in >> value)
		date.tm_year = value - 1900;
	else
		throw std::invalid_argument("Год!");
	if (in >> value && value >= 0 && value <= 23)
		date.tm_hour = value;
	else
		throw std::invalid_argument("Час!");
	if (in >> value && value >= 0 && value <= 59)
		date.tm_min = value;
	else
		throw std::invalid_argument("Минута!");
	if (in >> value && value >= 0 && value <= 59)
		date.tm_sec = value;
	else
		throw std::invalid_argument("Секунда!");
	return date;
}

int Villain::compare(const Villain& value)
{
	int comparator = compare_date(date, value.date);
	if (comparator != 0)
		return comparator;

	comparator = nickname.compare(value.nickname);
	if (comparator != 0)
		return comparator;

	comparator = creature - value.creature;
	if (comparator != 0)
		return comparator;

	if (is_catched > value.is_catched)
		return 1;
	if (is_catched < value.is_catched)
		return -1;

	comparator = name.compare(value.name);
	if (comparator != 0)
		return comparator;

	return 0;
}

std::string Villain::get_nickname() const { return nickname; }
std::string Villain::get_name() const { return name; }
Monster Villain::get_creature() const { return creature; }
tm Villain::get_date() const { return date; }
bool Villain::get_is_catched() const { return is_catched; }

bool Villain::set_is_catched(bool state)
{
	if (is_catched == state)
		return false;
	is_catched = state;
	return true;
}