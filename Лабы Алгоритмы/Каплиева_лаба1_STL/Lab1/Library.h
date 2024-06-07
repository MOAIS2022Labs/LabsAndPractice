#pragma once
#include "PrintEdition.h"
#include <fstream>
#include <list>
#include <memory>

using List = std::list<std::unique_ptr<PrintEdition>>;

class Library
{
private:

	std::string name;
	List list;

public:

	Library(std::string name, std::string fname);

	List get_list()
	{
		return std::move(list);
	}

	void set_list(List& list)
	{
		this->list = std::move(list);
	}

	void sort();

	void print(std::ostream& out = std::cout);
};

