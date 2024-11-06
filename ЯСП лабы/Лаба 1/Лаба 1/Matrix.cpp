#include "Matrix.h"


int** MemoryAllocation(int rows, int columns)
{
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new int[columns];
    return matrix;
}

void DeleteMatrix(int**& matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
    matrix = nullptr;
}

void PrintMatrix(std::ostream& stream, int** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
            stream << matrix[i][j] << '\t';
        stream << '\n';
    }
}

bool FillMatrixOneZero(int** matrix, int rows, int columns)
{
    bool result = true; // �������� �� ������������� ������� ����� �������� � ����������� �������
    if (rows >= columns - 1) // ��������, ��� � ������� ���� ���������� �������, 
                             // ����� �������� ���������� ������, ������ ������ �������
    {
        for (int j = 0; j < columns; ++j)
        {
            int count = 0; // ���������� ������ � ������� �������
            for (int i = 0; i < rows; ++i)
            {
                if (count == j) // ���� ������ ���������� ������ ���������, ��������� �������� ������� ����� ����
                    matrix[i][j] = 0;
                else
                {
                    if (rows - 1 - i > j - count) // j - count � ������� �������� �������� ������
                                                  // rows - 1 - i � ������� ��������� ������� ��� �� �������������
                    {
                        matrix[i][j] = rand() % 2;
                        if (matrix[i][j] == 1)
                            ++count;
                    }
                    else // ��� ���������� ������� ���������� ���� ���������� ������� ��������� ���������
                    {
                        matrix[i][j] = 1;
                        ++count;
                    }
                }
            }
        }
    }
    else
        result = false;
    return result;
}
