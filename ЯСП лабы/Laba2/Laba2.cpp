//Гонных Александр 91 группа
//Лабораторная работа №2, вариант №1
//«Членистоногое» представляет собой структуру с полями: название вида, дата
//открытия вида(использовать одну из предлагаемых языком структур), класс
//(перечисление[насекомое, ракообразное…]), число конечностей, число крыльев,
//максимальная длина, максимальная масса.Выборка членистоногих производится
//путем указания пользователем подходящего интервала по одному из критериев :
//дата открытия, размер, масса.Также выборка всех членистоногих из указанного
//пользователем класса или классов.Шаблонный класс должен иметь
//дополнительный метод — удаление членистоногих с одинаковым названием.
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Arthropod_list.h"
#include "Arthropod.h"

Arthropod_list<Arthropod> selection(Arthropod_list<Arthropod>& container,
	int choice)
{
	std::string fam1, fam2, pol;
	Arthropod_list<Arthropod> result;
	switch (choice)
	{
	case 0: {
		time_t date1, date2;
		std::cout << "Введите первую дату\n-->";
		is_valid_input(date1);
		std::cout << "Введите вторую дату\n-->";
		is_valid_input(date2);
		result = container.selection([date1, date2](Arthropod elem)
			{
				return (elem.get_date() >= date1 && elem.get_date() <= date2);
			});
		std::cout << result;
		break;
	}
	case 1: {
		double lenght1,lenght2;
		std::cout << "Введите первый размер\n-->";
		lenght1 = input_in_range(0.0, DBL_MAX);
		std::cout << "Введите второй размер\n-->";
		lenght2 = input_in_range(0.0, DBL_MAX);
		result = container.selection([lenght1, lenght2](Arthropod elem)
			{
				return (elem.get_max_length() >= lenght1 && elem.get_max_length() <= lenght2);
			});
		std::cout << result;
		break;
	}
	case 2: {
		double weight1, weight2;
		std::cout << "Введите первую массу\n-->";
		weight1 = input_in_range(0.0, DBL_MAX);
		std::cout << "Введите вторую массу\n-->";
		weight2 = input_in_range(0.0, DBL_MAX);
		result = container.selection([weight1, weight2](Arthropod elem)
			{
				return (elem.get_max_weight() >= weight1 && elem.get_max_weight() <= weight2);
			});
		std::cout << result;
		break;
	}
	case 3: {
		std::vector < std::string > classes;
		std::string input_class="";
		int size;
		std::cout << "Сколько классов вы хотите ввести?\n-->";
		size=input_in_range(1, INT_MAX);
		std::cout << "Введите классы\n-->";
		for (int i = 0; i < size; ++i) {
			std::cin >> input_class;
			classes.push_back(input_class);
		}

		result = container.selection([classes](Arthropod elem)
			{

				return std::find(classes.begin(),classes.end(),elem.get_class_animal_string())!=classes.end();
			});
		std::cout << result;
		break;
	}
	}
	return result;
}
void menu_print_to_file(Arthropod_list<Arthropod>& result) {
	std::cout << "\n0. Желаете ли сохранить результат в файл?(1|0)\n";
	int n = input_in_range(0, 1);
	if (n == 1) {
		std::string filename;
		std::cout << "Введите имя текстового файла --> ";
		std::cin >> filename;
		std::ofstream file(filename);
		file << result;
	}
}
void menu_selection(Arthropod_list<Arthropod>& container)
{
	int n;
	std::cout << "\n0. выборка по дате открытия\n"
		<< "1. выборка по размеру\n"
		<< "2. выборка по массе\n"
		<< "3. выборока по классу\n"
		<< " --> ";
	n = input_in_range(0, 3);
	Arthropod_list<Arthropod> result = selection(container, n);
	menu_print_to_file(result);
}
void fill(Arthropod_list<Arthropod>& container) {
	std::cout << "Как заполнить контейнер?(файл - 1, консоль - 2, никак - 0)\n--> ";
	int choice;
	choice = input_in_range(0, 2);
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	switch (choice)
	{
	case 1:
	{
		std::string filename;
		std::cout << "Введите имя файла\n--> ";
		std::cin >> filename;
		std::ifstream file(filename);
		try {
			file >> container;
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}
		break; }
	case 2:
	{
		std::cout << "Введите животных\n--> ";
		std::cin >> container;
		break;
	}
	default:
		break;
	}

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool flag = true;
	while (flag)
	{
		int choice;
		Arthropod arthropod{};

		Arthropod_list<Arthropod> container;
		fill(container);
		bool fl1 = true;
		while (fl1)
		{
			std::cout << "\n----------------------------------------------------------\n"
				<< "1. выборка\n"
				<< "2. добавить элемент в контейнер\n"
				<< "3. удалить элемент контейнера\n"
				<< "4. удалить повторяющиеся элементы\n"
				<< "5. изменить элемент контейнера\n"
				<< "6. печать в консоль\n"
				<< "7. печать в файл\n"
				<< "8. выход"
				<< "\n----------------------------------------------------------\n"
				<< " --> ";
			choice = input_in_range(0, 8);
			switch (choice)
			{
			case 1:
				if (container.size() > 0) {
					menu_selection(container);
				}
				else
				{
					std::cout << "Контейнер пуст, выбирать не из чего\n";
				}
				break;
			case 2:
				std::cout << "Введите информацию о животном\n";
				arthropod.read_console();
				container.add(arthropod);
				break;
			case 3:
			{
				int elem;
				if (container.size() > 0)
				{
					std::cout << "Введите номер записи\n-->";
					elem = input_in_range(1, container.size());
					container.del(elem);
					std::cout << "Запись удалена\n";
				}
				else
				{
					std::cout << "Контейнер пуст, удалять нечего\n";
				}
				break;
			}
			case 4: {
				container.remove_duplicates();
				std::cout << "Повторные записи удалены\n";
				break;
			}
			case 5:
			{
				int pos;
				if (container.size() > 0)
				{
					std::cout << "Введите номер записи\n-->";
					pos = input_in_range(1, container.size());
					std::cout << "Введите нового животного\n";
					arthropod.read_console();
					container.change(pos, arthropod);
					std::cout << "Запись обновлена";
				}
				else
				{
					std::cout << "Контейнер пуст, изменять нечего";
				}
				break;
			}
			case 6:
				std::cout << container;
				break;
			case 7:
			{
				std::string filename;
				std::cout << "Введите имя текстового файла --> ";
				std::cin >> filename;
				std::ofstream file(filename);
				file << container;
				break;
			}
			case 8:
				fl1 = false;
				break;
			}
		}
		std::cout << "Закончить?\nДа - 0\nНет - 1\n--> ";
		choice = input_in_range(0, 1);
		flag = choice == 1;
	}

}
