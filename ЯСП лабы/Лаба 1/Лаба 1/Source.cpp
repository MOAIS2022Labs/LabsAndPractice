/*
  Канатников Максим Андреевич, 9 группа
  15. Сформировать случайную матрицу m x n, состоящую из нулей и единиц, 
  причем в каждом столбце число единиц равно номеру столбца.
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
		case 1: // ввод с консоли
			ConsoleInput(m, n);
			MainTask(m, n);
			break;
		case 2: // чтение из файла
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
	if (!FillMatrixOneZero(matrix, m, n)) // генерация случайной матрицы из нулей и единиц согласно условию
		std::cout << "Заполнить матрицу этих размеров таким образом невозможно!";
	else
	{
		switch (OutputMenu())
		{
		case 1: // вывод на консоль
			PrintToConsole(matrix, m, n);
			break;
		case 2: // вывод в файл
			PrintToFile(matrix, m, n);
			break;
		}
	}
	DeleteMatrix(matrix, m);
}
