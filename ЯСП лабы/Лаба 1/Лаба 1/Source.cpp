/*
  ���������� ������ ���������, 9 ������
  15. ������������ ��������� ������� m x n, ��������� �� ����� � ������, 
  ������ � ������ ������� ����� ������ ����� ������ �������.
*/


#include <Windows.h>
#include "Matrix.h"
#include "Streams.h"


void MainTask(int m, int n);


int main()
{
	SetConsoleOutputCP(1251);
	srand(GetTickCount());
	int m, n;
	int choice = 0;
	do
	{
		choice = InputMenu();
		switch (choice)
		{
		case 1: // ���� � �������
			ConsoleInput(m, n);
			MainTask(m, n);
			break;
		case 2: // ������ �� �����
			FileInput(m, n);
			MainTask(m, n);
			break;
		}
	} while (choice != 0);
	return 0;
}


void MainTask(int m, int n)
{
	int** matrix = MemoryAllocation(m, n);
	if (!FillMatrixOneZero(matrix, m, n)) // ��������� ��������� ������� �� ����� � ������ �������� �������
		std::cout << "��������� ������� ���� �������� ����� ������� ����������!";
	else
	{
		switch (OutputMenu())
		{
		case 1: // ����� �� �������
			PrintToConsole(matrix, m, n);
			break;
		case 2: // ����� � ����
			PrintToFile(matrix, m, n);
			break;
		}
	}
	DeleteMatrix(matrix, m);
}
