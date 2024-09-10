#include "SearchTree.h"
#include "Bin.h"

/*
��������� ������� 2 ���� 9 ������

������ 9
����������� ������ ������ ������ ��������� ������ BinaryTree<X>, �������� �������� ������������� ����.
����� ������ � ������������ ������� ��������� ������:
- ������� �������� � ������;
- �������� �������� �� ������;
- ����� ��������;
- ���������� ������ ������ � ��� �������;
- ������ ������ �� �������;
- ����� ������ � ����;
- ������������� ������ �� �����.
*/

void pick_and_check(int& choice, const int a, const int b, const char* message);

void tree_from_console_menu();

bool check_file_type(const std::string name_of_file, const int check);

void tree_from_file_menu();

template <typename X>
void work_with_tree(BinaryTree<X>& tree);

int main() {
	SetConsoleOutputCP(1251);
	int choice;
	do 
	{
		pick_and_check(choice, 0, 2, "������ � ������ ������� >> 1\n��������� ������ � ������� ����� >> 2\n����� �� ��������� >> 0\n");
		switch (choice)
		{
		case 1:
			tree_from_console_menu();
			break;
		case 2:
			tree_from_file_menu();
			break;
		case 0:
			break;
		}
	} while (choice != 0);
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
			std::cout << "������ �����! ��������� ����\n";
			std::cin.clear(); //������� ������ ������ cin
			std::cin.ignore(255, '\n');
		}
	}
	std::cout << '\n';
}

std::string pick_name_of_file()
{
	std::string name_of_file;
	bool flag_of_out = false;
	std::cin.ignore();
	while (!flag_of_out)
	{
		std::cout << "������� ��� ����� >> ";
		std::getline(std::cin, name_of_file);
		std::ifstream file(name_of_file);
		if (file)
			flag_of_out = true;
		file.close();
		if (!flag_of_out)
			std::cout << "����� � ����� ������ �� ����������! ��������� ����.\n";
	}
	std::cout << '\n';
	return name_of_file;
}

bool check_file_type(const std::string name_of_file, const int check)
{
	bool result = true;
	switch (check)
	{
	case 1:
	{
		std::ifstream file(name_of_file);
		while (!file.eof() && result)
		{
			int x;
			if (!(file >> x))
				result = false;
		}
		file.close();
		break;
	}
	case 2:
		break;
	case 3:
	{
		std::ifstream file(name_of_file);
		while (!file.eof() && result)
		{
			std::string elem;
			std::getline(file, elem);
			if (elem.find_first_not_of("10") != std::string::npos)
				result = false;
		}
		file.close();
		break;
	}
	}
	return result;
}

void tree_from_console_menu()
{
	//����� ���� ������
	int type = 0;
	pick_and_check(type, 1, 3, "������� ��� ������ ��� ��������� ������:\nint >> 1\nstd::string >> 2\nBinary >> 3\n");
	std::cout << '\n';
	//���������� ������
	switch (type)
	{
	case 1:
	{
		BinaryTree<int> tree;
		work_with_tree(tree);
		break;
	}
	case 2:
	{
		BinaryTree<std::string> tree;
		work_with_tree(tree);
		break;
	}
	case 3:
	{
		BinaryTree<Binary> tree;
		work_with_tree(tree);
		break;
	}
	case 0:
		break;
	}
}

void tree_from_file_menu()
{
	//����� ����� �����
	std::string name_of_file = pick_name_of_file();
	//����� ���� ������
	int type = 0;
	pick_and_check(type, 1, 3, "������� ��� ������ ��� ��������� ������:\nint >> 1\nstd::string >> 2\nBinary >> 3\n");
	//���������� ������
	switch (type)
	{
	case 1:
	{
		if (check_file_type(name_of_file, type))
		{
			std::cout << '\n';
			BinaryTree<int> tree(name_of_file);
			work_with_tree(tree);
		}
		else
			std::cout << "������! ��������� ���� �������� ������������ ��� ����� ���� ������ ��������.\n\n";
		break;
	}
	case 2:
	{
		if (check_file_type(name_of_file, type))
		{
			std::cout << '\n';
			BinaryTree<std::string> tree(name_of_file);
			work_with_tree(tree);
		}
		else
			std::cout << "������! ��������� ���� �������� ������������ ��� ����� ���� ������ ��������.\n\n";
		break;
	}
	case 3:
	{
		if (check_file_type(name_of_file, type))
		{
			std::cout << '\n';
			BinaryTree<Binary> tree(name_of_file);
			work_with_tree(tree);
		}
		else
			std::cout << "������! ��������� ���� �������� ������������ ��� ����� ���� ������ ��������.\n\n";
		break;
	}
	case 0:
		break;
	}
}

template <typename X>
void work_with_tree(BinaryTree<X>& tree)
{
	int choice;
	do {
		pick_and_check(choice, 0, 6, "�������� ������� � ������ >> 1\n������� ������� �� ������ >> 2\n����� ������� � ������ >> 3\n��������� ������� ������ >> 4\n���������� ������ � ������� >> 5\n���������� ������ � ���� >> 6\n��������� ������ � ���� ������� >> 0\n");
		switch (choice)
		{
		case 1:
		{
			X value;
			try
			{
				std::cout << "������� �������, ������� ���� �������� � ������ >> ";
				if (std::cin >> value)
				{
					if (tree.add(value))
						std::cout << "�������� ������� ��� �������� � ������.\n";
					else
					std::cout << "�������� ������� ��� ���� � ������.\n";
				}
				else
				{
					std::cout << "������ �����!\n";
					std::cin.clear();
					std::cin.ignore(255, '\n');
				}
			}
			catch (Error exception)
			{
				exception.print_Error();
			}
			break;
		}
		case 2:
		{
			X value;
			try
			{
				std::cout << "������� �������, ������� ���� ������� �� ������ >> ";
				if (std::cin >> value)
				{
					if (tree.remove(value))
						std::cout << "�������� ������� ��� ������ �� ������.\n";
					else
						std::cout << "� ������ ��� ��������� � ����� ���������.\n";
				}
				else
				{
					std::cout << "������ �����!\n";
					std::cin.clear();
					std::cin.ignore(255, '\n');
				}
			}
			catch (Error exception)
			{
				exception.print_Error();
			}
			break;
		}	
		case 3:
		{
			X value;
			try
			{
				std::cout << "������� �������, ������� ���� ����� � ������ >> ";
				if (std::cin >> value)
				{
					Tree<X> t = tree.search(value);
					if (t)
						tree.print(t);
					else
						std::cout << "� ������ ��� ��������� � ����� ���������.\n";
				}
				else
				{
					std::cout << "������ �����!\n";
					std::cin.clear();
					std::cin.ignore(255, '\n');
				}
			}
			catch (Error exception)
			{
				exception.print_Error();
			}
			break;
		}
		case 4:
		{
			std::cout << "������ ������: " << tree.height() << '\n';
			std::cout << "���������� ��������� ��������� � ������: " << tree.size() << '\n';
			break;
		}
		case 5:
			if (tree.empty())
				std::cout << "������ �����.\n";
			else
				tree.print();
			break;
		case 6:
		{
			std::string name_of_file;
			std::cout << "������� ��� ������ �����, � ������� ���� ���������� ������ >> ";
			std::cin.ignore();
			std::getline(std::cin, name_of_file);
			std::ofstream file(name_of_file);
			if (file)
			{
				tree.print(file);
				std::cout << "������ ���� ���������� � ��������� ����.\n";
			}
			else
				std::cout << "������! ��������� ���� �� ������� ������� ��� �� ��� ����������.\n";
			file.close();
			break;
		}
		case 0:
			break;
		}
		std::cout << '\n';
	} while (choice != 0);
	std::cout << '\n';
}