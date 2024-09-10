#include "Matrix.h"

void read_and_check(int& pick, const short flag, const int a, const int b)
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
			std::cout << "\n������ �����! ��������� ����\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	}
}

int** fill_Matrix_from_console(int& n, int& m) //������� ���������� ��������� �� ����������� �������
{
	//srand(GetTickCount());
	//���������� ����������� �������
	std::cout << "\n\n������� ���-�� ����� ������� ";
	read_and_check(n, 0, 0, 0);
	std::cout << "������� ���-�� �������� ������� ";
	read_and_check(m, 0, 0, 0);

	std::cout << "������� �������� ��������� �������:\n";
	int** result = new int* [m]; //�������� ������� ����������
	for (int i = 0; i < m; ++i)
		result[i] = new int[n]; //�������� ������� �� m ��������� �� ������ i-�� ��������� � ������� result
	for (int i = 0; i < m; ++i) //���� ��������� �������
		for (int j = 0; j < n; ++j)
			//result[i][j] = -10 + rand() % (21); //��� ���������� ���������� ���������� �� -10 �� 10
			read_and_check(result[i][j], -1, 0, 0);
			//std::cin >> result[i][j];

	return result;
}

int** fill_Matrix_from_file(int& n, int& m)
{
	//���� ����� ����� � �������� ����� � ��������� ������
	std::cin.ignore();
	char* name = new char[255];
	std::cout << "\n\n������� ��� ���������� ����� >> ";
	std::cin.getline(name, 255);
	std::ifstream file(name);

	file >> n >> m; //���� ����������� ������� �� �����
	int** result = new int* [m]; //�������� ������� ����������
	for (int i = 0; i < m; ++i)
		result[i] = new int[n]; //�������� ������� �� m ��������� �� ������ i-�� ��������� � ������� result
	for (int i = 0; i < m; ++i) //���� ��������� ������� �� �����
		for (int j = 0; j < n; ++j)
			file >> result[i][j];
	file.close();

	return result;
}

//������ �������
void print_Matrix(int** matrix, const int n, const int m)
{
	std::cout << "\n\n";
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			std::cout << matrix[j][i] << ' ';
		std::cout << '\n';
	}
}

////���������������� �������
////������� ���������� ��������� �� ����������������� ������� � �������������� ����������� �������
//int** transpose_Matrix(int** matrix, int&n, int&m)
//{
//	//�������� ��������������� ������ ������� � ������������ m x n
//	int** natrix = new int* [m];
//	for (int j = 0; j < m; ++j)
//	{
//		natrix[j] = new int[n];
//	}
//	//���������������� �������� ������� � �����
//	for (int i = 0; i < n; ++i)
//		for (int j = 0; j < m; ++j)
//			natrix[j][i] = matrix[i][j];
//	delete_Matrix(matrix, n, m); //�������� �������� �������
//	std::swap(n, m);
//	return natrix;
//}

//������� ������
void delete_Matrix(int** matrix, const int m)
{
	for (int i = 0; i < m; ++i)
		delete[] matrix[i];
	delete[] matrix;
}