#pragma once
#include <iostream>
#include <fstream>
 

// Печать матрицы в выбранный поток. Поток передаётся параметром.
void PrintMatrix(std::ostream& stream, int** matrix, int rows, int columns);

// Выделение памяти под двумерный массив.
int** MemoryAllocation(int rows, int columns);

// Очистка памяти.
void DeleteMatrix(int**& matrix, int rows);

// Заполнение случайным образом матрицы нулями и единицами, кличество единиц в столбце равно номеру столбца (нумерация с нуля).
bool FillMatrixOneZero(int** matrix, int rows, int columns);
