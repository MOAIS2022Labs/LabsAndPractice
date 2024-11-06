#pragma once
#include <iostream>
#include <fstream>
#include <string>


// функция проверки корректности вводимых данных
void read_and_check(unsigned short& input, const char* message, int a, int b);
void read_and_check(std::string& str, const char* message);


// проверка корректности имени файла. 1, файл если открылся, -1, если файл не найден, 0, если файл пуст
bool check_file(std::string& fname);

// выбор способа инициализации объекта класса "Time"
int choose_type();

//выбор действия над объектом времени
int action_menu();

// проверка, что данная строка может быть переведена во время
bool condition_string(std::string& str);

int input_menu();

int output_menu();

std::string choose_out_file_name();

std::string choose_in_file_name();
