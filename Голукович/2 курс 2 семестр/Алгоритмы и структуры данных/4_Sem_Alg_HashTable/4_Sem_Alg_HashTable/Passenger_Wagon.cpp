#include "Passenger_Wagon.h"

Passenger_Wagon::Passenger_Wagon(std::ifstream& file) : Wagon(0, 0)
{
	file >> number >> year >> seats_count >> is_shower_room;
	file.ignore();
	std::getline(file, type);
}

void Passenger_Wagon::print(std::ostream& out) const
{
	out << "Ï\n";
	out << number << '\n';
	out << year << '\n';
	out << seats_count << '\n';
	out << is_shower_room << '\n';
	out << type << '\n';
}

std::string Passenger_Wagon::get_type() const
{
	return type;
}

unsigned int Passenger_Wagon::get_seats_count() const
{
	return seats_count;
}

bool Passenger_Wagon::get_is_shower_room() const
{
	return is_shower_room;
}