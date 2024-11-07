#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Wagon
{
protected:
	unsigned int number;
	unsigned int year;
public:
	Wagon(unsigned int number, unsigned int year) : number(number), year(year) {};
	virtual void print(std::ostream& out) const {};
	bool compare(const Wagon& wagon) const;
	unsigned int get_number() const;
	unsigned int get_year() const;
};