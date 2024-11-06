#pragma once
#include "UserInteraction.h"
#include "Matrix.h"

// ввод размеров матрицы с консоли
void ConsoleInput(int& m, int& n);

// ввод размеров матрицы из файла
void FileInput(int& m, int& n);

void PrintToFile(int** matrix, int m, int n);

void PrintToConsole(int** matrix, int m, int n);