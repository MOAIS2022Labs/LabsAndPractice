#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include "Passenger_Wagon.h"
#include "Freight_Wagon.h"

class Depo
{
private:
	std::string name;
	std::vector<std::shared_ptr<Wagon>> wagon_vector;
public:
	Depo(std::string file_name);
	void print(std::ostream& out) const;
	void sort();
	std::vector<std::shared_ptr<Wagon>>& get_wagon_vector();
	void set_wagon_vector(std::vector<std::shared_ptr<Wagon>>& vector);
};