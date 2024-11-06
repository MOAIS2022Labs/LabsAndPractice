#include "UserInteraction.h"


void ReadAndCheck(int& input, const char* message, int a, int b)
{
	std::cout << message;
	while (!(std::cin >> input) || input <= a || input >= b) // ������� ������� �� ��� ���, 
															 // ���� ������ �� ������� ���������
	{
		std::cout << "������ �����!";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << '\n' << message;
	}
}

int OutputMenu()
{
	std::cout << "��������, ���� ������� �������\n";
	std::cout << "1. � �������\n";
	std::cout << "2. � ����\n";
	int choice;
	ReadAndCheck(choice, "->", 0, 3);
	return choice;
}

int InputMenu()
{
	std::cout << "��������, ������ ��������� ������, ��� ��������� ������\n";
	std::cout << "1. �� �������\n";
	std::cout << "2. �� �����\n";
	std::cout << "0. ��������� ������\n";
	int choice;
	ReadAndCheck(choice, "->", -1, 3);
	return choice;
}
