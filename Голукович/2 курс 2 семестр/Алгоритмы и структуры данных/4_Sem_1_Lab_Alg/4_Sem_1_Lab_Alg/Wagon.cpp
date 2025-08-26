#include "Wagon.h"
bool Wagon::compare(const Wagon& wagon) const
{
	return year < wagon.get_year();
}

unsigned int Wagon::get_number() const
{
	return number;
}

unsigned int Wagon::get_year() const
{
	return year;
}
