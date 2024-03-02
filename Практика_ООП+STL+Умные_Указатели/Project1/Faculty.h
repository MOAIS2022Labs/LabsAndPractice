#pragma once
#include <memory>
#include <vector>
#include <fstream>
#include"Person.h"

#include <algorithm>

using Vector = std::vector<std::unique_ptr<Person>>;

class Faculty
{
private:

	Vector faculty;
	std::string name;

public:

	Faculty() {}
	Faculty(std::string file_name);

	void print();

	void sort();

	Vector get_vector()
	{
		return std::move(faculty);
	}

	void set_vector(Vector& vector)
	{
		faculty = std::move(vector);
	}

};

