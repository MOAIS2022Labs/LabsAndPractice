#include "Villain.h"

int Villain::compare_date(const tm& value)
{
	if (date.tm_year > value.tm_year)
		return 1;
	if (date.tm_year < value.tm_year)
		return -1;

	if (date.tm_mon > value.tm_mon)
		return 1;
	if (date.tm_mon < value.tm_mon)
		return -1;

	if (date.tm_mday > value.tm_mday)
		return 1;
	if (date.tm_mday < value.tm_mday)
		return -1;

	if (date.tm_hour > value.tm_hour)
		return 1;
	if (date.tm_hour < value.tm_hour)
		return -1;

	if (date.tm_min > value.tm_min)
		return 1;
	if (date.tm_min < value.tm_min)
		return -1;

	if (date.tm_sec > value.tm_sec)
		return 1;
	if (date.tm_sec < value.tm_sec)
		return -1;

	return 0;
}

int Villain::compare(const Villain& value)
{
	int comparator = compare_date(value.date);
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

std::string Villain::get_nickname() { return nickname; }
std::string Villain::get_name() { return name; }
Monster Villain::get_creature() { return creature; }
tm Villain::get_date() { return date; }
bool Villain::get_is_catched() { return is_catched; }