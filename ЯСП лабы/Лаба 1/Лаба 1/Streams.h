#pragma once
#include "UserInteraction.h"
#include "Matrix.h"

// ���� �������� ������� � �������
void ConsoleInput(int& m, int& n);

// ���� �������� ������� �� �����
void FileInput(int& m, int& n);

void PrintToFile(int** matrix, int m, int n);

void PrintToConsole(int** matrix, int m, int n);