//√олукович “имофей —ергеевич
//2 курс 9 группа
//12 задача
//ƒана матрица, содержаща€ как положительные, так и отрицательные элементы.
//”далить все ее столбцы, содержащие только неотрицательные элементы.


#include "Matrix.h"

bool check_col(int* col, const int m);

int** fix_Matrix(int** matrix, const int n, int& m);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//¬ыбор способа заполнени€ матрицы
	int choice = 0;
	std::cout << "«аполнить матрицу вручную >> 1\n«аполнить матрицу с помощью текстового файла >> 2\n";
	read_and_check(choice, true, 1, 2);

	int n, m; //размерность матрицы
	int** matrix = nullptr; //пустой указатель

	//создание и заполнение матрицы согласно выбранному варианту
	if (choice == 1)
		matrix = fill_Matrix_from_console(n, m);
	if (choice == 2)
		matrix = fill_Matrix_from_file(n, m);
	
	if (matrix)
	{
		print_Matrix(matrix, n, m);

		//matrix = transpose_Matrix(matrix, n, m);

		//print_Matrix(matrix, n, m);

		matrix = fix_Matrix(matrix, n, m); //удаление строк в матрице согласно условию задачи

		//print_Matrix(matrix, n, m);
		if (matrix) //если полученна€ матрица не пуста€
		{
			//matrix = transpose_Matrix(matrix, n, m);

			print_Matrix(matrix, n, m);

			delete_Matrix(matrix, m);
		}
		else
			std::cout << "\n¬се столбцы матрицы были удалены.";
	}
	else
		std::cout << "";
	
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
	//вычисление количества строк, которые не нужно удал€ть и создание массива, показывающего, кокие столбцы надо удалить
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