#pragma once
#include "Wagon.h"

class Passenger_Wagon : public Wagon
{
private:
	std::string type;
	unsigned int seats_count;
	bool is_shower_room;
public:
	Passenger_Wagon(std::ifstream& file);
	void print(std::ostream& out) const;
	std::string get_type() const;
	unsigned int get_seats_count() const;
	bool get_is_shower_room() const;
};