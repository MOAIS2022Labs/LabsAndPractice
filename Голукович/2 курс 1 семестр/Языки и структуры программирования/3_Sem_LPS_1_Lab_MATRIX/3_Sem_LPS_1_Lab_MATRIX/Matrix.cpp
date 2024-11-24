#include "Matrix.h"

void read_and_check(int& pick, const short flag, const int a, const int b) //ввод и проверка данных с консоли
{
	bool end = false;
	while (!end)
	{
		if (std::cout << ">> " && std::cin >> pick)
			//if (flag == -1 || (flag == 0 && pick > 0) || (flag == 1 && pick >= a && pick <= b))
			switch (flag)
			{
			case -1:
				end = true;
				break;
			case 0:
				if (pick > 0)
					end = true;
				break;
			case 1:
				if (pick >= a && pick <= b)
					end = true;
				break;
			}
		if (!end)
		{
			std::cout << "\nОшибка ввода! Повторите ввод\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	}
}

int** fill_Matrix_from_console(int& n, int& m) //функция возвращает указатель на заполненную матрицу
{
	//srand(GetTickCount());
	//заполнение размерности матрицы
	std::cout << "\n\nВведите кол-во строк матрицы ";
	read_and_check(n, 0, 0, 0);
	std::cout << "Введите кол-во столбцов матрицы ";
	read_and_check(m, 0, 0, 0);

	std::cout << "Введите значения элементов матрицы:\n";
	int** result = new int* [m]; //создание массива указателей
	for (int i = 0; i < m; ++i)
		result[i] = new int[n]; //создание массива из m элементов по адресу i-го указателя в массиве result
	for (int i = 0; i < n; ++i) //ввод элементов матрицы
		for (int j = 0; j < m; ++j)
			//result[i][j] = -10 + rand() % (21); //для заполнения случайными значениями от -10 до 10
			read_and_check(result[j][i], -1, 0, 0);
			//std::cin >> result[i][j];

	return result;
}

int** fill_Matrix_from_file(int& n, int& m)
{
	//ввод имени файла и открытие файла с введенным именем
	std::cin.ignore();
	char* name = new char[255];
	std::cout << "\n\nВведите имя текстового файла >> ";
	std::cin.getline(name, 255);
	std::ifstream file(name);
	int** result = nullptr;
	if (file)
	{
		file >> n >> m; //ввод размерности матрицы из файла
		result = new int* [m]; //создание массива указателей
		for (int i = 0; i < m; ++i)
			result[i] = new int[n]; //создание массива из m элементов по адресу i-го указателя в массиве result
		for (int i = 0; i < n; ++i) //ввод элементов матрицы из файла
			for (int j = 0; j < m; ++j)
				file >> result[j][i];
	}
	file.close();
	delete[] name;
	name = nullptr;
	return result;
}

//печать матрицы
void print_Matrix(int** matrix, const int n, const int m, const int a, const int b, const char* message)
{
	int choice = 0;
	std::cout << message;
	read_and_check(choice, 1, a, b);
	switch (choice)
	{
	case 1:
		console_print_Matrix(matrix, n, m);
		break;
	case 2:
		file_print_Matrix(matrix, n, m);
		break;
	default:
		break;
	}
}

void console_print_Matrix(int** matrix, const int n, const int m)
{
	std::cout << "\n\n";
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			std::cout << std::setw(4)<< matrix[j][i] << ' ';
		std::cout << '\n';
	}
}

void file_print_Matrix(int** matrix, const int n, const int m)
{
	char* name = new char[255];
	std::cout << "\n\nВведите имя текстового файла >> ";
	std::cin.ignore();
	std::cin.getline(name, 255);
	std::ofstream file(name);
	file << n << ' ' << m << '\n';
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			file << std::setw(4) << matrix[j][i] << ' ';
		file << '\n';
	}
	delete[] name;
	name = nullptr;
	file.close();
}

////транспонирование матрицы
////функция возвращает указатель на транспонированную матрицу и переопределяет размерность матрицы
//int** transpose_Matrix(int** matrix, int&n, int&m)
//{
//	//создание вспомогательной пустой матрицы с размерностью m x n
//	int** natrix = new int* [m];
//	for (int j = 0; j < m; ++j)
//	{
//		natrix[j] = new int[n];
//	}
//	//транспонирование исходной матрицы в новую
//	for (int i = 0; i < n; ++i)
//		for (int j = 0; j < m; ++j)
//			natrix[j][i] = matrix[i][j];
//	delete_Matrix(matrix, n, m); //удаление исходной матрицы
//	std::swap(n, m);
//	return natrix;
//}

//очистка памяти
void delete_Matrix(int** matrix, const int m)
{
	for (int i = 0; i < m; ++i)
		delete[] matrix[i];
	delete[] matrix;
}