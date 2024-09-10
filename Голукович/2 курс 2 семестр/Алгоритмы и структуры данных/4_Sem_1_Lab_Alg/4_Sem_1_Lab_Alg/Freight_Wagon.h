#pragma once
#include "Wagon.h"

class Freight_Wagon : public Wagon
{
private:
	unsigned int tonnage;
	std::string type;
public:
	Freight_Wagon(std::ifstream& file);
	void print(std::ostream& out) const;
	unsigned int get_tonnage() const;
	std::string get_type() const;
};