//Голукович Тимофей Сергеевич
//2 курс 9 группа
//12 задача
//Дана матрица, содержащая как положительные, так и отрицательные элементы.
//Удалить все ее столбцы, содержащие только неотрицательные элементы.


#include "Matrix.h"

bool check_col(int* col, const int m);

int** fix_Matrix(int** matrix, const int n, int& m);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice = 1;
	while (choice == 1)
	{
		//Выбор способа заполнения матрицы
		
		std::cout << "Заполнить матрицу вручную >> 1\nЗаполнить матрицу с помощью текстового файла >> 2\n";
		read_and_check(choice, 1, 1, 2);

		int n, m; //размерность матрицы
		int** matrix = nullptr; //пустой указатель

		//создание и заполнение матрицы согласно выбранному варианту
		if (choice == 1)
			matrix = fill_Matrix_from_console(n, m);
		if (choice == 2)
			matrix = fill_Matrix_from_file(n, m);

		if (matrix)
		{
			print_Matrix(matrix, n, m, 1, 3, "\nВывести матрицу в консоль >> 1\nВывести матрицу в файл >> 2\nНе Выводить матрицу >> 3\n");

			matrix = fix_Matrix(matrix, n, m); //удаление строк в матрице согласно условию задачи
			if (matrix) //если полученная матрица не пустая
			{
				print_Matrix(matrix, n, m, 1, 2, "\nВывести новую матрицу в консоль >> 1\nВывести новую матрицу в файл >> 2\n");
				delete_Matrix(matrix, m);
			}
			else
				std::cout << "\nВсе столбцы матрицы были удалены.";
		}
		else
			std::cout << "\nТакого файла не существует!";

		std::cout << "Продолжить выполнение программы?\nДа >> 1\nНет >> 2\n";
		read_and_check(choice, 1, 1, 2);
	}
	
	std::cout << "\n";
	std::cin.get();
	return 0;
}

//проверка строки на наличие в ней отрицательных элементов
bool check_col(int* col,  const int n)
{
	bool result = false;
	for (int j = 0; j < n && !result; ++j)
		if (col[j] < 0)
			result = true;
	return result;
}

//удаление из матрицы строк, не содержащих отрицательных элементов и переопределение количества строк в матрице
//если матрица 
int** fix_Matrix(int** matrix, const int n, int& m)
{
	int** result = nullptr;
	//вычисление количества строк, которые не нужно удалять и создание массива, показывающего, кокие столбцы надо удалить
	bool* k = new bool[m];
	int kK = 0;
	for (int i = 0; i < m; ++i)
		if (check_col(matrix[i], n))
		{
			k[i] = true;
			kK += 1;
		}
		else
			k[i] = false;
	if (kK != 0)
	{
		result = new int*[kK]; //создание массива указателей из k элементов
		int l = 0; //дополнительный счетчик
		for (int i = 0; i < m; ++i)
		{
			//копирование строк, содержащих отрицательные элементы в новую матрицу
			if (k[i])
			{
				result[l] = new int[n];
				for (int j = 0; j < n && l < kK; ++j)
					result[l][j] = matrix[i][j];
				l += 1;
			}
		}
		delete_Matrix(matrix, m); //удаление исходной матрицы
		m = kK; //новое количество строк в матрице
	}
	return result;
}