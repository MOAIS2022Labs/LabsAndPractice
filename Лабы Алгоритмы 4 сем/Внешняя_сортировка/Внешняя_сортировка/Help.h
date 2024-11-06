#pragma once
#include "Elem.h"
#include <fstream>
#include <iostream>
#include <string>

void fill_file(std::fstream& file, size_t count_elements);

bool check_file_orderliness(std::fstream& file);

bool check_file_correctness(std::fstream& file);

void print_file(std::fstream& file);

int read_and_check(int min, int max);

std::string read_file_name();

std::fstream choose_file();

std::string choose_file_name();

std::fstream choose_empty_file();

int main_menu();

bool check_file_name(std::string filename);