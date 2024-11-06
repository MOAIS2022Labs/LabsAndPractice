#pragma once
#include <iostream>
#include <fstream>
 

// ������ ������� � ��������� �����. ����� ��������� ����������.
void PrintMatrix(std::ostream& stream, int** matrix, int rows, int columns);

// ��������� ������ ��� ��������� ������.
int** MemoryAllocation(int rows, int columns);

// ������� ������.
void DeleteMatrix(int**& matrix, int rows);

// ���������� ��������� ������� ������� ������ � ���������, ��������� ������ � ������� ����� ������ ������� (��������� � ����).
bool FillMatrixOneZero(int** matrix, int rows, int columns);
