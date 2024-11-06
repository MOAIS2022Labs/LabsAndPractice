#pragma once
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

#include <sstream>

void read_min_max(std::istream& stream, int& min, int& max);
int read_check_int(std::istream& stream, int min, int max);


template<class X>
bool is_valid_input(std::istream& stream, X& info);

void check_name_file(std::string& file_name);
std::string name_file();



