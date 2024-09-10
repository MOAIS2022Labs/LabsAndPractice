#include "Freight_Wagon.h"
Freight_Wagon::Freight_Wagon(std::ifstream& file) : Wagon(0, 0)
{
	file >> number >> year >> tonnage;
	file.ignore();
	std::getline(file, type);
}

void Freight_Wagon::print(std::ostream& out) const
{
	out << "Ã\n";
	out << number << '\n';
	out << year << '\n';
	out << tonnage << '\n';
	out << type << '\n';
}

unsigned int Freight_Wagon::get_tonnage() const
{
	return tonnage;
}

std::string Freight_Wagon::get_type() const
{
	return type;
}
