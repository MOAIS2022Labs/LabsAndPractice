#pragma once

#include "Container.h"
#include "Villain.h"
#include <Windows.h>
#include <iomanip>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental\filesystem>


class Prison
{
private:
	std::string prison_name;
	Container<Villain> prison{};
	std::fstream* prison_file;
public:
	Prison(std::string name, std::fstream* prison_file);
	~Prison();

	void save();

	void rename(std::string new_name);

	void print(std::ostream& out, std::string parser, bool flag);

	std::string get_name() const;

	size_t size();

	const Villain& at(size_t index);

	void add(std::istream& in);
	void add(std::vector<Villain>::iterator begin, std::vector<Villain>::iterator end);

	Villain remove(size_t index);

	void edit(size_t index, const Villain& villain);

	std::vector<Villain> selection(std::function<bool(Villain&)> selector);

	void set(std::vector<Villain>& selected);

	Villain get_last();

	std::vector<Villain> clear();
};