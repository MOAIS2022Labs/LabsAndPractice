#include "SearchTree.h"
#include "Bin.h"

/*
Голукович Тимофей 2 курс 9 группа

Задача 9
Реализовать шаблон класса дерево бинарного поиска BinaryTree<X>, хранящий элементы произвольного типа.
Класс должен в обязательном порядке содержать методы:
- Вставка элемента в дерево;
- Удаление элемента из дерева;
- Поиск элемента;
- Вычисление высоты дерева и его размера;
- Печать дерева на консоль;
- Вывод дерева в файл;
- инициализация дерева из файла.
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
		pick_and_check(choice, 0, 2, "Работа с пустым деревом >> 1\nЗаполнить дерево с помощью файла >> 2\nВыход из программы >> 0\n");
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
		if (std::cout << ">> " && std::cin >> choice && a <= choice && choice <= b) //ввод целого числа и проверка на попадание в диапазон от a до b
			flag_of_out = true;
		else
		{
			std::cout << "Ошибка ввода! Повторите ввод\n";
			std::cin.clear(); //очистка флагов потока cin
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
		std::cout << "Введите имя файла >> ";
		std::getline(std::cin, name_of_file);
		std::ifstream file(name_of_file);
		if (file)
			flag_of_out = true;
		file.close();
		if (!flag_of_out)
			std::cout << "Файла с таким именем не существует! Повторите ввод.\n";
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
	//выбор типа данных
	int type = 0;
	pick_and_check(type, 1, 3, "Введите тип данных для бинарного дерева:\nint >> 1\nstd::string >> 2\nBinary >> 3\n");
	std::cout << '\n';
	//заполнение дерева
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
	//выбор имени файла
	std::string name_of_file = pick_name_of_file();
	//выбор типа данных
	int type = 0;
	pick_and_check(type, 1, 3, "Введите тип данных для бинарного дерева:\nint >> 1\nstd::string >> 2\nBinary >> 3\n");
	//заполнение дерева
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
			std::cout << "Ошибка! Выбранный файл содержит недопустимые для этого типа данных значения.\n\n";
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
			std::cout << "Ошибка! Выбранный файл содержит недопустимые для этого типа данных значения.\n\n";
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
			std::cout << "Ошибка! Выбранный файл содержит недопустимые для этого типа данных значения.\n\n";
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
		pick_and_check(choice, 0, 6, "Добавить элемент в дерево >> 1\nУдалить элемент из дерева >> 2\nНайти элемент в дереве >> 3\nВычислить размеры дерева >> 4\nНапечатать дерево в консоль >> 5\nНапечатать дерево в файл >> 6\nЗавершить работу с этим деревом >> 0\n");
		switch (choice)
		{
		case 1:
		{
			X value;
			try
			{
				std::cout << "Введите элемент, который надо добавить в дерево >> ";
				if (std::cin >> value)
				{
					if (tree.add(value))
						std::cout << "Заданный элемент был добавлен в дерево.\n";
					else
					std::cout << "Заданный элемент уже есть в дереве.\n";
				}
				else
				{
					std::cout << "Ошибка ввода!\n";
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
				std::cout << "Введите элемент, который надо удалить из дерева >> ";
				if (std::cin >> value)
				{
					if (tree.remove(value))
						std::cout << "Заданный элемент был удален из дерева.\n";
					else
						std::cout << "В дереве нет элементов с таким значением.\n";
				}
				else
				{
					std::cout << "Ошибка ввода!\n";
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
				std::cout << "Введите элемент, который надо найти в дереве >> ";
				if (std::cin >> value)
				{
					Tree<X> t = tree.search(value);
					if (t)
						tree.print(t);
					else
						std::cout << "В дереве нет элементов с таким значением.\n";
				}
				else
				{
					std::cout << "Ошибка ввода!\n";
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
			std::cout << "Высота дерева: " << tree.height() << '\n';
			std::cout << "Количество различных элементов в дереве: " << tree.size() << '\n';
			break;
		}
		case 5:
			if (tree.empty())
				std::cout << "Дерево пусто.\n";
			else
				tree.print();
			break;
		case 6:
		{
			std::string name_of_file;
			std::cout << "Введите имя нового файла, в который надо напечатать дерево >> ";
			std::cin.ignore();
			std::getline(std::cin, name_of_file);
			std::ofstream file(name_of_file);
			if (file)
			{
				tree.print(file);
				std::cout << "Дерево было напечатано в выбранный файл.\n";
			}
			else
				std::cout << "Ошибка! Выбранный файл не удалось открыть или он уже существует.\n";
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