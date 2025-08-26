// Голукович Тимофей Сергеевич, 9 группа
// 17d. Заменить все положительные числа самым часто встречающимся числом. (std::forward_list)

#include "ForwardList.h"
#include <Windows.h>
#include <algorithm>

void pick_and_check(int& choice, const int a, const int b, const char* message);
void pick_file_name(std::string& file_name);

std::fstream fill_random_int_file_cycle(const std::string& file_name, const int min, const int M);
std::fstream fill_random_int_file_generate(const std::string& file_name, const int min, const int M);

void main_menu(int choice);
void list_menu(std::fstream& file);

void print_forward_list_to_console_or_file(FList& forward_list);

void modify_forward_list(int choice, FList& forward_list);

void save_or_print_modified_list(FList& forward_list, std::forward_list<int>& new_list);

int main()
{
	SetConsoleOutputCP(1251);
	int choice = 1;
	while (choice != 0)
	{
		pick_and_check(choice, 0, 2, "Заполнить исходный файл с помощью цикла >> 1\nЗаполнить исходный файл с помощью generate >> 2\nВыход из программы >> 0\n");
		if (choice != 0)
			main_menu(choice);
	}
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

void pick_file_name(std::string& file_name)
{
	bool flag_of_out = false;
	while (!flag_of_out)
	{
		std::cout << "Введите имя файла >> ";
		std::getline(std::cin, file_name);
		std::ifstream file(file_name);
		if (file.peek() == EOF)
			flag_of_out = true;
		file.close();
		if (!flag_of_out)
			std::cout << "Файл с таким именем уже существует! Повторите ввод.\n";
	}
}

void main_menu(int choice)
{
	std::fstream file;
	std::string file_name;
	std::cin.ignore();
	pick_file_name(file_name);
	std::cout << '\n';
	int N = 1, M = 0;
	pick_and_check(N, 0, INT_MAX, "Введите N (количество элементов в листе)\n");
	pick_and_check(M, 0, INT_MAX, "Введите M (диапазон значений в листе от -M до M)\n");

	if (choice == 1)
		file = fill_random_int_file_cycle(file_name, N, M);
	else
		file = fill_random_int_file_generate(file_name, N, M);
	list_menu(file);
}

void list_menu(std::fstream& file)
{
	FList forward_list(file);
	int choice = 1;
	while (choice != 0)
	{
		pick_and_check(choice, 0, 7, "Печать элементов листа >> 1\nНайти сумму элементов листа >> 2\nНайти среднее арифметическое элементов листа >> 3\nМодифицировать лист с помощью цикла for >> 4\nМодифицировать лист с помощью std::transform >> 5\nМодифицировать лист с помощью std::for_each >> 6\nЗавершить работу с текущим листом >> 0\n");
		switch (choice)
		{
		case 1:
			print_forward_list_to_console_or_file(forward_list);
			break;
		case 2:
			std::cout << "Количество элементов в листе: " << forward_list.get_size() << '\n';
			break;
		case 3:
			std::cout << "Сумма элементов листа: " << forward_list.find_sum() << '\n';
			break;
		case 4:
			std::cout << "Среднее арифметическое элементов листа: " << forward_list.find_average() << '\n';
			break;
		case 5:
			modify_forward_list(1, forward_list);
			break;
		case 6:
			modify_forward_list(2, forward_list);
			break;
		case 7:
			modify_forward_list(3, forward_list);
			break;
		default:
			break;
		}
		std::cout << '\n';
	}
}

std::fstream fill_random_int_file_cycle(const std::string& file_name, const int N, const int M)
{
	srand(GetTickCount());
	std::fstream file(file_name, std::ios::in | std::ios::out | std::ios::trunc);
	for (int i = 0; i < N; ++i)
		file << rand() % (M * 2) - M << ' ';
	file.close();
	return std::fstream(file_name);
}

std::fstream fill_random_int_file_generate(const std::string& file_name, const int N, const int M)
{
	srand(GetTickCount());
	std::ofstream result(file_name, std::ios::in | std::ios::out | std::ios::trunc);
	std::generate_n(std::ostream_iterator<int>(result, " "), N, [M]() {return rand() % (M * 2) - M; });
	result.close();
	return std::fstream(file_name);
}

void print_forward_list_to_console_or_file(FList& forward_list)
{
	int choice;
	pick_and_check(choice, 0, 2, "Вывести элементы листа в консоль >> 1\nСохранить лист в файл >> 2\n");
	switch (choice)
	{
	case 1:
		std::cout << forward_list;
		break;
	case 2:
	{
		std::string file_name;
		std::cin.ignore();
		pick_file_name(file_name);
		std::ofstream file(file_name);
		file << forward_list;
		file.close();
		break;
	}
	default:
		break;
	}
}

void modify_forward_list(int choice, FList& forward_list)
{
	std::forward_list<int> new_list;
	int begin = 0, end = -1;
	while (begin > end)
	{
		std::cout << "Введите границы интервала изменения (текущие границы 0-" << forward_list.get_size() - 1 << "):\n\n";
		pick_and_check(begin, 0, forward_list.get_size(), "Введите левую границу интервала");
		pick_and_check(end, 0, forward_list.get_size(), "Введите правую границу интервала");
		if (begin > end)
			std::cout << "\nОшибка! Левая граница интервала больше правой.\nПовторите ввод\n";
	}
	std::forward_list<int>::iterator iterator_begin, iterator_end;
	forward_list.set_iterators(iterator_begin, iterator_end, begin, end);
	switch (choice)
	{
	case 1:
		new_list = forward_list.modify_ver_1(iterator_begin, iterator_end);
		break;
	case 2:
		new_list = forward_list.modify_ver_2(iterator_begin, iterator_end);
		break;
	case 3:
		new_list = forward_list.modify_ver_3(iterator_begin, iterator_end);
		break;
	default:
		break;
	}
	save_or_print_modified_list(forward_list, new_list);
}

void save_or_print_modified_list(FList& forward_list, std::forward_list<int>& new_list)
{
	int choice;
	pick_and_check(choice, 1, 2, "Печать элементов измененного листа >> 1\nСохранить изменения в текущий лист >> 2\n");
	if (choice == 1)
		std::cout << FList(new_list);
	else
		forward_list.set(new_list);
}