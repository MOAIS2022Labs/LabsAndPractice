#include "HelpH.h"

template<class X>
bool is_valid_input(std::istream& stream, X& info)
{
	bool flag = false;
	while (!flag)
	{
		stream >> info;
		if (!stream.fail())
			flag = true;
		else
		{
			std::cout << "������.\n> ";
			stream.clear();
			stream.ignore(stream.rdbuf()->in_avail());
		}
	}
	return flag;
}



void read_min_max(std::istream& stream, int& min, int& max)
{
	std::cout << "\n������� MIN > ";
	min = read_check_int(stream, 0, 1000);
	std::cout << "\n������� MAX > ";
	max = read_check_int(stream, 0, 1000);
}


// �������� �� ������������� �����
void check_name_file(std::string& file_name)
{
	std::ifstream file;
	bool open = false;
	while (!open)
	{
		file.open(file_name);
		if (!file.is_open())
		{
			std::cin.clear();
			file_name.clear();
			std::cout << "��������� ���� > ";
			std::getline(std::cin, file_name);
		}
		else
			open = true;
	}
	file.close();
}

// ���� ����� �����
std::string name_file()
{
	std::cin.clear();
	std::cout << "������� ��� ����� > ";
	std::string file_name;
	std::cin.ignore();
	std::getline(std::cin, file_name);
	check_name_file(file_name);
	return file_name;
}


// �������� �����
int read_check_int(std::istream& stream, int min, int max)
{
	int choice;
	while (!is_valid_input(stream, choice) || !(choice >= min && choice <= max))
		std::cout << "������.\n> ";
	return choice;
}

/*
bool check_file(std::istream& stream, int choice)
{
	bool flag = true;
	
	switch (choice)
	{
	case 1:
	{
		std::string line;

		while (std::getline(stream, line) && flag)
		{
			std::stringstream ss(line); // ������� ����� ��� �������������� ������ � �����
			std::string word;
			while (ss >> word && flag)
				if (!std::stoi(word) || (word.find(".") != std::string::npos))
					flag = false;	
		}
		break;
	}
	case 2:
	{
		flag = true;
		break;
	}
	case 3:
	{
		std::string line;

		while (getline(stream, line) && flag)
		{
			std::stringstream ss(line);
			std::string word;

			while (ss >> word && flag)
				if (!std::stoi(word) || (std::stoi(word) && std::atoi(word.c_str()) <= 0))
					flag = false;
		}
		break;
	}
	}
	
	return flag;
}


*/
