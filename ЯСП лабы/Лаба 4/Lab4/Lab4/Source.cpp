// ���������� ������ ���������, 9 ������
// 19d. ��������� ��� ������������� ����� �� ���������� ��������������� ����� (std::forward_list).


#include "Container.h"
#include <Windows.h>

std::fstream fill_file_cycle(const std::string& fname, const int N, const int M);

std::fstream fill_file_generate(const std::string& fname, const int N, const int M);

//�������� ������������ ��������� ������
void read_and_check(size_t& input, size_t min = 0, size_t max = MAXINT);

// ����� �������� � �����������
size_t action_menu();

// ������ ���������� �����
size_t fill_menu();

// ����� ���������� ������ modify
size_t modify_menu();

// ����� ����� ������ ����������
size_t output_menu();

std::string choose_file_name();

std::pair<iterator, iterator> read_borders(Container& container);

std::forward_list<int> modify(Container& container);


int main()
{
	SetConsoleOutputCP(1251);
	while (true)
	{
		std::cout << "\n��������� ���� ����������� N ������ ���������� ������� � ��������� �� - M �� M\n\n"
			<< "������� ����� N\n";
		size_t N{};
		read_and_check(N, 1);
		std::cout << "������� ����� M\n";
		size_t M{};
		read_and_check(M, 1);
		std::string fname = choose_file_name();
		std::fstream file = fill_menu() == 1 ? fill_file_cycle(fname, N, M) 
			: fill_file_generate(fname, N, M);
		Container container(file);
		file.close();
		bool action = true;
		while (action)
		{
			switch (action_menu())
			{
			case 1: // modify
			{
				std::forward_list<int> new_fl = modify(container);
				if (new_fl.empty())
					std::cout << "���������������� ��������� ����";
				else
					for (int elem : new_fl)
						std::cout << elem << ' ';
				std::cout << '\n';
				break;
			}

			case 2: // sum
				std::cout << "����� ����� " << container.sum() << '\n';
				break;

			case 3: // average
				std::cout << "������� �������������� ����� " << container.average() << '\n';
				break;

			case 4: // print
				if (output_menu() == 1)
					container.print_console();
				else
					container.print_file(choose_file_name());
				break;

			case 0:
				action = false;
				break;
			}
		}
		char is_exit{};
		std::cout << "��������� ���������� ���������? 0, ���� ��\n-> ";
		std::cin >> is_exit;
		if (is_exit == '0')
			break;
	}
	return 0;
}

std::fstream fill_file_cycle(const std::string& fname, const int N, const int M)
{
	srand(GetTickCount());
	std::fstream result(fname, std::ios::in | std::ios::out | std::ios::trunc);
	for (int i = 0; i < N; ++i)
		result << rand() % (M * 2) - M << ' ';
	result.seekg(0);
	return result;
}

std::fstream fill_file_generate(const std::string& fname, const int N, const int M)
{
	srand(GetTickCount());
	std::fstream result(fname,	std::ios::in | std::ios::out | std::ios::trunc);
	std::generate_n(std::ostream_iterator<int>(result, " "), N, 
		[M]() {return rand() % (M * 2) - M; });
	result.seekg(0);
	return result;
}

void read_and_check(size_t& input, size_t min, size_t max)
{
	std::cout << "-> ";
	while (!(std::cin >> input) || input > max || input < min)
	{
		std::cout << "������ �����!\n";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << "-> ";
	}
}

size_t action_menu()
{
	std::cout << "�������� ��������\n"
		<< "1. �������������� ���������\n"
		<< "2. ����� ����� ��������� ����������\n"
		<< "3. ����� ������� �������������� ��������� ����������\n"
		<< "4. ������� ���������\n"
		<< "0. ��������� ������ � ������� ����������\n";
	size_t choice{};
	read_and_check(choice, 0, 4);
	return choice;
}

size_t fill_menu()
{
	std::cout << "�������� ������ ���������� �����\n"
		<< "1. ��������� ����\n"
		<< "2. ��������� generate_n\n";
	size_t choice{};
	read_and_check(choice, 1, 2);
	return choice;
}

size_t modify_menu()
{
	std::cout << "�������� ������ ����������� ����������\n"
		<< "1. ��������� ���� for\n"
		<< "2. ��������� std::transform\n"
		<< "3. ��������� std::for_each\n";
	size_t choice{};
	read_and_check(choice, 1, 3);
	return choice;
}

size_t output_menu()
{
	std::cout << "�������� ������ ������ ����������\n"
		<< "1. � �������\n"
		<< "2. � ����\n";
	size_t choice{};
	read_and_check(choice, 1, 2);
	return choice;
}

std::string choose_file_name()
{
	std::cout << "������� ��� �����: ";
	std::string fname;
	std::cin >> fname;
	return fname;
}

std::pair<iterator, iterator> read_borders(Container& container)
{
	std::pair<iterator, iterator> result;
	while (true)
	{
		size_t left{}, right{};
		std::cout << "������� ���������� ����� ������� ��������. 0, ���� ������������ ����� begin\n";
		read_and_check(left, 0);
		std::cout << "������� ���������� ����� ���������� �������� (��������� �� �����������!). 0, ���� ������������ ����� end\n";
		read_and_check(right, 0);
		if (left > right && right)
			std::cout << "������� ������� �����������! ��������� ����\n";
		else
		{
			if (!left)
				result.first = container.begin();
			else
				result.first = container.get_iterator(left);
			if (!right)
				result.second = container.end();
			else
				result.second = container.get_iterator(right);
			break;
		}
	}
	return result;
}

std::forward_list<int> modify(Container& container)
{
	std::pair<iterator, iterator> borders = read_borders(container);
	size_t choice = modify_menu();
	if (choice == 1)
		return container.modify_for(borders.first, borders.second);
	if (choice == 2)
		return container.modify_transform(borders.first, borders.second);
	return container.modify_for_each(borders.first, borders.second);
}