#include "Help.h"

void fill_file(std::fstream& file, size_t count_elements)
{
	Elem x;
	for (int i = 0; i < count_elements; ++i)
	{
		x.make_rand(count_elements);
		file.write((char*)&x, sizeof(Elem));
	}
}

bool check_file_orderliness(std::fstream& file)
{
	bool result = true;
	Elem x, y;
	file.read((char*)&x, sizeof(Elem));
	while (!file.eof() && result)
	{
		file.read((char*)&y, sizeof(Elem));
		result = (x <= y);
		x = y;
	}
	return result;
}

bool check_file_correctness(std::fstream& file)
{
	bool result = true;
	Elem elem;
	while (file.read((char*)&elem, sizeof(Elem)));
	// TODO: ��������
	return result;
}

void print_file(std::fstream& file)
{
	Elem x;
	file.read((char*)&x, sizeof(Elem));
	int count{};
	while (!file.eof())
	{
		std::cout << x << "    ";
		file.read((char*)&x, sizeof(Elem));
		++count;
	}
	std::cout << "\n---------------------------------\n";
}

int read_and_check(int min, int max)
{
	std::cin.clear();
	int input;
	std::cout << "-> ";
	while (!(std::cin >> input) || input > max || input < min)
	{
		std::cout << "������ �����!\n";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << "-> ";
	}
	return input;
}

std::string read_file_name()
{
	std::cin.clear();
	std::string input;
	std::cout << "������� ���  ��������� ����� (���������� .bin ������� �� �����): ";
	while (!(std::getline(std::cin, input)) || !check_file_name(input))
	{
		std::cout << "������ �����, ���������� ����������������� �������!\n";
		std::cin.clear();
		std::cout << "������� ���  ��������� ����� (���������� .bin ������� �� �����): ";
	}
	return input + ".bin";
}

std::fstream choose_file()
{
	bool flag_of_out = false;
	std::string file_name;
	std::fstream file;
	std::cin.ignore(255, '\n');
	while (!flag_of_out)
	{
		file_name = read_file_name();
		file = std::fstream(file_name, std::ios::in | std::ios::binary);
		if (file.peek() != EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "���� � ����� ������ �� ���������� ��� �� �������� ������! ��������� ����\n";
	}
	std::cout << '\n';
	return file;
}

std::string choose_file_name()
{
	bool flag_of_out = false;
	std::string file_name;
	std::fstream file;
	std::cin.ignore(255, '\n');
	while (!flag_of_out)
	{
		file_name = read_file_name();
		file = std::fstream(file_name, std::ios::in | std::ios::binary);
		if (file.peek() != EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "���� � ����� ������ �� ���������� ��� �� �������� ������! ��������� ����\n";
	}
	std::cout << '\n';
	file.close();
	return file_name;
}

std::fstream choose_empty_file()
{
	bool out_flag = false;
	std::fstream file;
	std::string file_name;
	std::cin.ignore(255, '\n');
	while (!out_flag)
	{
		file_name = read_file_name();
		file = std::fstream(file_name, std::ios::trunc | std::ios::out | std::ios::binary);
		if (file.peek() == EOF)
			out_flag = true;
		else
			file.close();
		if (!out_flag)
		{
			std::cout << "���� � ����� ������ ��� ���������� � �������� ������! �� ������ ������������ ����? (0, ���� ��)\n";
			if (std::cin.get() == '0')
				out_flag = true;
			else
				std::cout << "�������� ������ ����\n";
		}
	}
	std::cout << '\n';
	file.seekg(0);
	return file;
}

int main_menu()
{
	std::cout << "1. ������� ���� �� ���������� �������.\n"
		<< "2. ������� ���� � �������.\n"
		<< "3. ������������� ����.\n"
		<< "4. ��������� ���� �� ���������������\n"
		<< "5. ������� ���������� ����������.\n"
		<< "6. �������� ������ �������� ������ ����������.\n"
		<< "0. �����.\n";
	return read_and_check(0, 6);
}

bool check_file_name(std::string file_name)
{
	std::string forbidden_symbols = "^.*[\\\\\\/:\\*\\?\"<>\\|\\+].*$";
	return file_name.find_first_of(forbidden_symbols) == std::string::npos;
}
