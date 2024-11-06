#include "Streams.h"


void ConsoleInput(int& m, int& n)
{
	ReadAndCheck(m, "Введите количество строк матрицы, строк больше, чем столбцов: ", 0, INT_MAX);
	ReadAndCheck(n, "Введите количество столбцов матрицы: ", 0, INT_MAX);
}

void FileInput(int& m, int& n)
{
	std::cout << "Введите имя файла с исходными данными: ";
	std::string fname;
	std::cin >> fname;
	std::ifstream file(fname.c_str());
	file >> m >> n;
	file.close();
}

void PrintToFile(int** matrix, int m, int n)
{
	std::cout << "Введите имя файла, в который хотите записать матрицу: ";
	std::string fname;
	std::cin >> fname;
	std::ofstream file(fname.c_str());
	PrintMatrix(file, matrix, m, n);
	std::cout << "Данные записаны в файл " << fname;
	file.close();
}

void PrintToConsole(int** matrix, int m, int n)
{
	PrintMatrix(std::cout, matrix, m, n);
}
