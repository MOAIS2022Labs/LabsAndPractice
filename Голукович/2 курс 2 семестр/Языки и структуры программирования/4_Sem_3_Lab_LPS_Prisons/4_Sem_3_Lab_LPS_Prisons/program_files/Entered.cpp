#include "Entered.h"

Entered::Entered(std::string int_file_name, std::string string_file_name)
{
	entered_int_file_name = int_file_name;
	entered_int_file = std::fstream(entered_int_file_name, std::ios::in | std::ios::out);
	while (entered_int_file && !entered_int_file.eof())
	{
		int value;
		if (entered_int_file >> value)
			entered_int.push_back(value);
	}
	entered_int_size = entered_int.size();
	entered_int_file.clear();

	entered_string_file_name = string_file_name;
	entered_string_file = std::fstream(entered_string_file_name, std::ios::in | std::ios::out);
	while (entered_string_file && !entered_string_file.eof())
	{
		std::string value;
		std::getline(entered_string_file, value);
		if (!value.empty())
			entered_string.push_back(value);
	}
	entered_string_size = entered_string.size();
	entered_string_file.clear();
}

Entered::~Entered()
{
	entered_int_file.close();
	entered_string_file.close();
}

bool Entered::empty()
{
	return entered_int.empty() && entered_string.empty();
}

void Entered::push_back(int value)
{
	entered_int.push_back(value);
	entered_int_file << value << std::endl;
}

void Entered::push_back(std::string value)
{
	entered_string.push_back(value);
	entered_string_file << value << std::endl;
}

bool Entered::front(int& value)
{
	if (int_iterator >= entered_int_size)
		return false;

	value = entered_int[int_iterator];
	int_iterator++;
	return true;
}

bool Entered::front(std::string& value)
{
	if (string_iterator >= entered_string_size)
		return false;

	value = entered_string[string_iterator];
	string_iterator++;
	return true;
}

void Entered::clear()
{
	using path = std::experimental::filesystem::path;

	resize_file(path(entered_int_file_name), 0);
	entered_int_file.clear();
	entered_int_file.seekg(0);
	entered_int_file.seekp(0);
	entered_int.clear();
	entered_int_size = 0;
	int_iterator = 0;

	resize_file(path(entered_string_file_name), 0);
	entered_string_file.clear();
	entered_string_file.seekg(0);
	entered_string_file.seekp(0);
	entered_string.clear();
	entered_string_size = 0;
	string_iterator = 0;
}
