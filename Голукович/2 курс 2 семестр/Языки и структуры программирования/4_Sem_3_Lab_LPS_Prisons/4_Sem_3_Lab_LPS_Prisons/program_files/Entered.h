#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental\filesystem>

class Entered
{
private:
	//работа с int
	std::string entered_int_file_name;
	std::fstream entered_int_file;
	size_t int_iterator = 0;
	size_t entered_int_size;
	std::vector<int> entered_int{};
	//работа string
	std::string entered_string_file_name;
	std::fstream entered_string_file;
	size_t string_iterator = 0;
	size_t entered_string_size;
	std::vector<std::string> entered_string{};
public:
	Entered(std::string int_file_name, std::string string_file_name);
	~Entered();

	bool empty();
	void push_back(int value);
	void push_back(std::string value);
	bool front(int& value);
	bool front(std::string& value);
	bool pop(bool type_flag);
	void clear();
};