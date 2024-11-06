#include "UserInteraction.h"

void read_and_check(unsigned short& input, const char* message, int a, int b)
{
	std::cout << message;
	while (!(std::cin >> input) || input < a || input > b) // ������� ������� �� ��� ���, 
														   // ���� ������ �� ������� ���������
	{
		std::cout << "������ �����!";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << '\n' << message;
	}
}

void read_and_check(std::string& str, const char* message)
{
	std::cout << message;
	std::cin >> str;
	while (!condition_string(str))
	{
		std::cout << "������ �����!\n" << message;
		std::cin >> str;
	}
}

bool check_file(std::string& fname)
{
	std::ifstream file(fname.c_str());
	int result = 1;
	if (!file)
		result = 0;
	file.close();
	return result;
}

int initialization_menu()
{
	std::cout << "�������� ������ ������������� �������\n";
	std::cout << "1. �������\n";
	std::cout << "2. �������\n";
	std::cout << "3. ���������\n";
	std::cout << "4. ��������\n";
	std::cout << "0. ��������� ������\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 0, 4);
	std::cout << '\n';
	return choice;
}

int action_menu()
{
	std::cout << "\n�������� ��������\n";
	std::cout << "1.  ������� ��������� ���������� ������\n";
	std::cout << "2.  �������� ��������� ���������� ������\n";
	std::cout << "3.  ��������� ����� � �������\n";
	std::cout << "4.  ��������� ����� � ������\n";
	std::cout << "5.  ������� ������ ������� �� �����\n";
	std::cout << "6.  ���������� ������ ������� � ����\n";
	std::cout << "7.  ������� �� ����� ��������� �������������\n";
	std::cout << "8.  ������� 2 ������� �������\n";
	std::cout << "9.  ������� ����� � �������\n";
	std::cout << "10. ������� ���� ������ ������� �� �������\n";
	std::cout << "11. ������� ������� �� �������\n";
	std::cout << "12. ��������� ������� ������� �� ���������\n";
	std::cout << "13. ��������� ������� ������� �� �����������(!=)\n";
	std::cout << "14. ��������� ������� ������� �� �����������(>)\n";
	std::cout << "15. ��������� ������� ������� �� �����������(<)\n";
	std::cout << "16. ��������� ������� ������� �� �����������(>=)\n";
	std::cout << "17. ��������� ������� ������� �� �����������(<=)\n";
	std::cout << "18. ��������� ������� � �������� ����� ����� ��������� �������\n";
	std::cout << "0.  ��������� �������� � ������� �������� �������\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 0, 18);
	std::cout << '\n';
	return choice;
}

int input_menu()
{
	std::cout << "��������, ������ ������� ������\n";
	std::cout << "1. �� �������\n";
	std::cout << "2. �� �����\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 1, 2);
	std::cout << '\n';
	return choice;
}

int output_menu()
{
	std::cout << "��������, ���� ������� ������\n";
	std::cout << "1. � �������\n";
	std::cout << "2. � ����\n";
	unsigned short choice;
	read_and_check(choice, "->\t", 1, 2);
	std::cout << '\n';
	return choice;
}

std::string choose_out_file_name()
{
	std::cout << "������� ��� �����: ";
	std::string fname;
	std::cin >> fname;
	return fname;
}

std::string choose_in_file_name()
{
	std::cout << "������� ��� �����: ";
	std::string fname;
	std::cin >> fname;
	while (!check_file(fname))
	{
		std::cout << "������, ������� ������ ��� �����: ";
		std::cin >> fname;
	}
	return fname;
}
