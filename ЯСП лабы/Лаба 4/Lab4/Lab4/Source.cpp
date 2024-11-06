// Канатников Максим Андреевич, 9 группа
// 19d. Увеличить все положительные числа на количество неотрицательных чисел (std::forward_list).


#include "Container.h"
#include <Windows.h>

std::fstream fill_file_cycle(const std::string& fname, const int N, const int M);

std::fstream fill_file_generate(const std::string& fname, const int N, const int M);

//проверка корректности введенных данных
void read_and_check(size_t& input, size_t min = 0, size_t max = MAXINT);

// выбор действия с контейнером
size_t action_menu();

// способ заполнения файла
size_t fill_menu();

// выбор реализации метода modify
size_t modify_menu();

// выбор места вывода контейнера
size_t output_menu();

std::string choose_file_name();

std::pair<iterator, iterator> read_borders(Container& container);

std::forward_list<int> modify(Container& container);


int main()
{
	SetConsoleOutputCP(1251);
	while (true)
	{
		std::cout << "\nТекстовый файл заполняется N целыми случайными числами в диапазоне от - M до M\n\n"
			<< "Введите число N\n";
		size_t N{};
		read_and_check(N, 1);
		std::cout << "Введите число M\n";
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
					std::cout << "Модифицированный контейнер пуст";
				else
					for (int elem : new_fl)
						std::cout << elem << ' ';
				std::cout << '\n';
				break;
			}

			case 2: // sum
				std::cout << "Сумма равна " << container.sum() << '\n';
				break;

			case 3: // average
				std::cout << "Среднее арифметическое равно " << container.average() << '\n';
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
		std::cout << "Завершить выполнение программы? 0, если да\n-> ";
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
		std::cout << "Ошибка ввода!\n";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << "-> ";
	}
}

size_t action_menu()
{
	std::cout << "Выберете действие\n"
		<< "1. Модифицировать контейнер\n"
		<< "2. Найти сумму элементов контейнера\n"
		<< "3. Найти среднее арифметическое элементов контейнера\n"
		<< "4. Вывести контейнер\n"
		<< "0. Завершить работу с текущей коллекцией\n";
	size_t choice{};
	read_and_check(choice, 0, 4);
	return choice;
}

size_t fill_menu()
{
	std::cout << "Выберете способ заполнения файла\n"
		<< "1. Используя цикл\n"
		<< "2. Используя generate_n\n";
	size_t choice{};
	read_and_check(choice, 1, 2);
	return choice;
}

size_t modify_menu()
{
	std::cout << "Выберете способ модификации контейнера\n"
		<< "1. Используя цикл for\n"
		<< "2. Используя std::transform\n"
		<< "3. Используя std::for_each\n";
	size_t choice{};
	read_and_check(choice, 1, 3);
	return choice;
}

size_t output_menu()
{
	std::cout << "Выберете способ вывода контейнера\n"
		<< "1. В консоль\n"
		<< "2. В файл\n";
	size_t choice{};
	read_and_check(choice, 1, 2);
	return choice;
}

std::string choose_file_name()
{
	std::cout << "Введите имя файла: ";
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
		std::cout << "Введите порядковый номер первого элемента. 0, если использовать метод begin\n";
		read_and_check(left, 0);
		std::cout << "Введите порядковый номер последнего элемента (последний не учитывается!). 0, если использовать метод end\n";
		read_and_check(right, 0);
		if (left > right && right)
			std::cout << "Границы введены некорректно! Повторите ввод\n";
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