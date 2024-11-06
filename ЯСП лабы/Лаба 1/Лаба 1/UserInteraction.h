#pragma once
#include <iostream>
#include <fstream>


// Функция проверки корректности вводимых данных.
void ReadAndCheck(int& input, const char* message, int a, int b);

// Выбор места вывода информации.
int OutputMenu();

// Выбор места с исходными данными.
int InputMenu();
