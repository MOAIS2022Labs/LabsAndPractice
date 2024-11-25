//��������� ������� 2 ���� 9 ������ 

//20 ������
//������� ����� Binary ��� ������ � ������������ ������ ��������� �������,
//��������� ��� ������������� ������ �� 100 ��������� ���� unsigned char,
//������ ������� ��������� �������� �������� ������.
//������� ����� ����� ������� ������ (������� - � ������� �������� �������).
//�������� ������ �������� ��� �������� ������������ �������������.
//����������� �������������� ��������, ����������� ���������� ��� ����� � C++, � �������� ���������.

#include "Bin.h"
#include <Windows.h>

void pick_and_check(int& choice, const int a, const int b, const char* message);

Binary pick_num();

void one_number_menu(Binary& num_l);

void two_numbers_menu();

void main_menu(int choice);

int main()
{
	SetConsoleOutputCP(1251);

	//Binary num("1010");
	//std::cout << num.to_cstring();

	int choice = 1;
	while (choice)
	{
		pick_and_check(choice, 0, 2, "\n������ � ����� ������ >> 1\n������ � ����� ������� >> 2\n��������� ������ �������� >> 0\n");
		main_menu(choice);
	}
	std::cin.get();
	return 0;
}

void pick_and_check(int& choice, const int a, const int b, const char* message)
{
	std::cout << message;
	bool flag_of_out = false;
	while (!flag_of_out)
	{
		if (std::cout << ">> " && std::cin >> choice && a <= choice && choice <= b) //���� ������ ����� � �������� �� ��������� � �������� �� a �� b
			flag_of_out = true;
		else
		{
			std::cout << "\n������ �����! ��������� ����\n";
			std::cin.clear(); //������� ������ ������ cin
			std::cin.ignore(255, '\n');
		}	
	}
}

Binary pick_num()
{
	try //����������� ��� ������ ����������
	{
		int choice;
		Binary result;
		pick_and_check(choice, 1, 2, "���� ����� ������� >> 1\n���� ����� � ������� ���������� ����� >> 2\n");
		if (choice == 1)
		{
			pick_and_check(choice, 0, MAX, "������� ������ ����� � �����\n");
			result = Binary(choice); //������������� ��������� �����
		}
		else
			if (choice == 2)
			{
				char* name_of_file = new char[255];
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "������� ��� ����� >> ";
				std::cin.getline(name_of_file, 255);
				std::ifstream file(name_of_file);
				if (file)
					result = Binary(file); //������������� ��������� ����� � ������� �����
				else
					throw Error(404, "File cannot be opend correctly!");
				file.close();
				delete[] name_of_file;
				name_of_file = nullptr;
			}
		return result;
	}
	catch (const Error error) { throw error; } //��������� ����������
}

void one_number_menu(Binary& num_l)
{
	int choice = 1;
	while (choice != 0)
	{
		pick_and_check(choice, 0, 9, "���������� ������� ����� >> 1\n���������� ������� ����� � ���� >> 2\n��������� ������� ����� �� ����� >> 3\n��������� ������� ����� �� ����� >> 4\n�������� ������� ����� �� ����� >> 5\n��������� ������� ����� �� ����� >> 6\n������� �� ������� �������� ����� �� ����� >> 7\n��������� ������� ����� �� 1 >> 8\n��������� ������� ����� �� 1 >> 9\n��������� ������ � ������� ������ >> 0\n");
		try
		{
			Binary num_r;
			switch (choice)
			{
			case 1:
				std::cout << "\n������� ����� >> " << num_l << "\n\n";
				break;
			case 2:
			{
				char* name_of_file = new char[255];
				std::cout << "������� ��� ����� >> ";
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cin.getline(name_of_file, 255);
				std::ofstream file(name_of_file);
				if (file)
					file << num_l << '\n';
				else
					throw Error(404, "File cannot be opend correctly!");
				file.close();
				break;
			}
			case 3:
				num_r = pick_num(); //������������� ������� �����
				std::cout << ' ' << num_l << "\n+\n " << num_r << "\n=\n ";;
				num_l += num_r;
				std::cout << num_l << "\n\n";
				break;
			case 4:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n-\n " << num_r << "\n=\n ";;
				num_l -= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 5:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n*\n " << num_r << "\n=\n ";;
				num_l *= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 6:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n/\n " << num_r << "\n=\n ";;
				num_l /= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 7:
				num_r = pick_num();
				std::cout << ' ' << num_l << "\n%\n " << num_r << "\n=\n ";;
				num_l %= num_r;
				std::cout << num_l << "\n\n";
				break;
			case 8:
				++num_l;
				break;
			case 9:
				--num_l;
				break;
			default:
				break;
			}
		}
		catch (const Error error) { error.print_Error(); } //��������� ���������� (������ ������ � �������)
	}
}

void two_numbers_menu()
{
	try
	{
		Binary num_l = pick_num();
		Binary num_r = pick_num();
		int choice = 1;
		pick_and_check(choice, 0, 5, "�������� ������� � ������� ����� >> 1\n������� �� ������� ����� ������ >> 2\n�������� ������ ����� �� ������ >> 3\n��������� ������ ����� �� ������ >> 4\n������� �� ������� ������� ����� �� ������ >> 5\n");
		switch (choice)
		{
		case 1:
			std::cout << ' ' << num_l << "\n+\n " << num_r << "\n=\n " << num_l + num_r << "\n\n";
			break;
		case 2:
			std::cout << ' ' << num_l << "\n-\n " << num_r << "\n=\n " << num_l - num_r << "\n\n";
			break;
		case 3:
			std::cout << ' ' << num_l << "\n*\n " << num_r << "\n=\n " << num_l * num_r << "\n\n";
			break;
		case 4:
			std::cout << ' ' << num_l << "\n/\n " << num_r << "\n=\n " << num_l % num_r << "\n\n";
			break;
		case 5:
			std::cout << ' ' << num_l << "\n%\n " << num_r << "\n=\n " << num_l % num_r << "\n\n";
			break;
		}
	}
	catch (const Error error) { throw error; }
}

void main_menu(int choice)
{
	try
	{
		if (choice == 1)
		{
			Binary num = pick_num();
			one_number_menu(num);
		}
		if (choice == 2)
			two_numbers_menu();
	}
	catch (const Error error) { error.print_Error(); }
}