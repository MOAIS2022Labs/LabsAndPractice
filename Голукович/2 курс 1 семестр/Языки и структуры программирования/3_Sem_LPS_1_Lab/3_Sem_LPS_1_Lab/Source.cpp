//��������� ������� ���������
//2 ���� 9 ������
//12 ������
//���� �������, ���������� ��� �������������, ��� � ������������� ��������.
//������� ��� �� �������, ���������� ������ ��������������� ��������.


#include "Matrix.h"

bool check_col(int* col, const int m);

int** fix_Matrix(int** matrix, const int n, int& m);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//����� ������� ���������� �������
	int choice = 0;
	std::cout << "��������� ������� ������� >> 1\n��������� ������� � ������� ���������� ����� >> 2\n";
	read_and_check(choice, true, 1, 2);

	int n, m; //����������� �������
	int** matrix = nullptr; //������ ���������

	//�������� � ���������� ������� �������� ���������� ��������
	if (choice == 1)
		matrix = fill_Matrix_from_console(n, m);
	if (choice == 2)
		matrix = fill_Matrix_from_file(n, m);
	
	if (matrix)
	{
		print_Matrix(matrix, n, m);

		//matrix = transpose_Matrix(matrix, n, m);

		//print_Matrix(matrix, n, m);

		matrix = fix_Matrix(matrix, n, m); //�������� ����� � ������� �������� ������� ������

		//print_Matrix(matrix, n, m);
		if (matrix) //���� ���������� ������� �� ������
		{
			//matrix = transpose_Matrix(matrix, n, m);

			print_Matrix(matrix, n, m);

			delete_Matrix(matrix, m);
		}
		else
			std::cout << "\n��� ������� ������� ���� �������.";
	}
	else
		std::cout << "";
	
	std::cin.get();
	return 0;
}

//�������� ������ �� ������� � ��� ������������� ���������
bool check_col(int* col,  const int n)
{
	bool result = false;
	for (int j = 0; j < n && !result; ++j)
		if (col[j] < 0)
			result = true;
	return result;
}

//�������� �� ������� �����, �� ���������� ������������� ��������� � ��������������� ���������� ����� � �������
//���� ������� 
int** fix_Matrix(int** matrix, const int n, int& m)
{
	int** result = nullptr;
	//���������� ���������� �����, ������� �� ����� ������� � �������� �������, �������������, ����� ������� ���� �������
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
		result = new int*[kK]; //�������� ������� ���������� �� k ���������
		int l = 0; //�������������� �������
		for (int i = 0; i < m; ++i)
		{
			//����������� �����, ���������� ������������� �������� � ����� �������
			if (k[i])
			{
				result[l] = new int[n];
				for (int j = 0; j < n && l < kK; ++j)
					result[l][j] = matrix[i][j];
				l += 1;
			}
		}
		delete_Matrix(matrix, m); //�������� �������� �������
		m = kK; //����� ���������� ����� � �������
	}
	return result;
}