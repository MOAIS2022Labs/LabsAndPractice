/* 
Канатников Максим, 2 курс 9 группа
	1. «Членистоногое» представляет собой структуру с полями: название вида, дата 
открытия вида (использовать одну из предлагаемых языком структур), класс
(перечисление [насекомое, ракообразное…]), число конечностей, число крыльев, 
максимальная длина, максимальная масса. Выборка членистоногих производится 
путем указания пользователем подходящего интервала по одному из критериев: 
дата открытия, размер, масса. Также выборка всех членистоногих из указанного 
пользователем класса или классов. Шаблонный класс должен иметь 
дополнительный метод — удаление членистоногих с одинаковым названием.
*/

#include "Container.h"
#include <vector>
#include "Arthropod.h"
#include "Help.h"

int add_element(Container<Arthropod>& container);
void add_from_console(Container<Arthropod>& container);
void fill_from_file(Container<Arthropod>& container);
void container_actions(Container<Arthropod>& container);
void print_container(Container<Arthropod>& container);
void remove_element(Container<Arthropod>& container);
void change_element(Container<Arthropod>& container);
std::list<Arthropod> select_from_container(Container<Arthropod>& container);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Container<Arthropod> container;
	int choice = 0;
	do
	{
		choice = add_element(container);
		if (choice)
			container_actions(container);
	} while (choice != 0);

	return 0;
}

int add_element(Container<Arthropod>& container)
{
	int choice = fill_menu();
	switch (choice)
	{
	case 1:
		add_from_console(container);
		break;
	case 2:
		fill_from_file(container);
		break;
	case 0:
		break;
	}
	return choice;
}

void add_from_console(Container<Arthropod>& container)
{
	std::cout << "Введите данные по шаблону\n\n";
	show_template_multiple();
	try
	{		
		std::cin.ignore(255, '\n');
		std::istream_iterator<Arthropod> it(std::cin);
		std::istream_iterator<Arthropod> eof;
		while (it != eof)
		{
			bool t = std::cin.eof();
			container.add(*it);
			surprise((int)it->get_class());
			std::cout << "Введите данные по шаблону\n\n";
			show_template_multiple();
			++it;
		}
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "Ошибка чтения! " << exception.what() << '\n';
	}
}

void fill_from_file(Container<Arthropod>& container)
{
	std::cin.ignore(255, '\n');
	std::fstream file = choose_file();
	try
	{		
		std::istream_iterator<Arthropod> it(file);
		container.read(it);
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "Ошибка чтения файла! " << exception.what() << '\n';
	}
	file.close();
	std::cout << "Информация успешно считана, контейнер заполнен\n\n";
}

void container_actions(Container<Arthropod>& container)
{
	int choice = 1;
	while (choice != 0)
	{
		choice = container_menu();
		switch (choice)
		{
		case 1:
			print_container(container);
			break;
		case 2:
			add_from_console(container);
			break;
		case 3:
			remove_element(container);
			break;
		case 4:
			change_element(container);
			break;
		case 5:
		{
			auto res = select_from_container(container);
			std::cout << "Результат выборки\n";
			if (res.size() > 0)
				std::copy(res.begin(), res.end(), std::ostream_iterator<Arthropod>(std::cout, "----------------\n"));
			else
				std::cout << "Выборка пуста\n";
		}
			break;
		case 6:
			if (container.size() > 0)
			{
				container.remove_duplicates();
				std::cout << "Дубликаты удалены\n";
			}
			else
				std::cout << "Текущий контейнер пуст!\n";
			break;
		case 7:
			container.clear();
			break;
		case 0:
			break;
		}
		std::cout << '\n';
	}
}

void print_container(Container<Arthropod>& container)
{
	int choice = 0;
	if (container.size() > 0)
	{
		choice = print_menu();
		switch (choice)
		{
		case 1:
		{
			auto writer = std::ostream_iterator<Arthropod>(std::cout, "----------------\n");
			container.print(writer);
			break;
		}
		case 2:
		{
			std::fstream file = choose_empty_file();
			auto writer = std::ostream_iterator<Arthropod>(file);
			container.print(writer);
			file.close();
			std::cout << "Информация успешно записана в файл\n";
			break;
		}
		case 0:
			break;
		}
	}
	else
		std::cout << "Текущий контейнер пуст!\n";
}

void remove_element(Container<Arthropod>& container)
{
	std::cout << "Введите индекс удаляемого элемента, индексация с нуля\n";
	size_t index = read_and_check(unsigned(0), UINT_MAX);
	try
	{
		container.remove(index);
		std::cout << "Элемент успешно удалён\n";
	}
	catch (std::out_of_range ex)
	{
		std::cout << '\n' << ex.what() << '\n';
	}
}

void change_element(Container<Arthropod>& container)
{
	std::cout << "Введите индекс удаляемого элемента, индексация с нуля\n";
	size_t index = read_and_check(unsigned(0), UINT_MAX);
	try
	{
		Arthropod new_element;
		std::cout << "Введите новое значение по указанному шаблону\n";
		show_template_single();
		std::cin.ignore(255, '\n');
		while (!(std::cin >> new_element))
		{
			std::cout << "Ошибка ввода!\nВведите новое значение по указанному шаблону\n";
			show_template_single();
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
		container.change(index, new_element);
		std::cout << "Элемент успешно изменён\n";
	}
	catch (std::out_of_range ex)
	{
		std::cout << '\n' << ex.what() << '\n';
	}
}

std::list<Arthropod> select_from_container(Container<Arthropod>& container)
{
	switch (selection_menu())
	{
	case 1:
	{
		tm left, right;
		bool flag = true;
		std::cin.ignore(255, '\n');
		while (flag)
		{
			try
			{
				std::cout << "Введите левое значение интервала даты dd.mm.yyyy\n";
				
				left = read_date(std::cin);
				std::cout << "Введите правое значение интервала даты\n";
				right = read_date(std::cin);
				if (right > left)
					flag = false;
				else
					std::cout << "Правая граница не должна быть меньше левой\n";
			}
			catch (std::invalid_argument ex)
			{
				std::cout << ex.what() << '\n';
			}
		}
		return container.selection(
			[left, right](const Arthropod& elem) 
			{return right > elem.get_discovery_date() && left <= elem.get_discovery_date(); });
	}
	case 2:
	{
		std::cout << "Введите левое значение интервала размера\n";
		double left = read_and_check(0.001, DBL_MAX);
		std::cout << "Введите правое значение интервала размера\n";
		double right = read_and_check(left, DBL_MAX);
		return container.selection(
			[left, right](const Arthropod& elem) 
			{return elem.get_max_length() < right && elem.get_max_length() >= left; });
	}
	case 3:
	{
		std::cout << "Введите левое значение интервала массы\n";
		double left = read_and_check(0.001, DBL_MAX);
		std::cout << "Введите правое значение интервала массы\n";
		double right = read_and_check(left, DBL_MAX);
		return container.selection(
			[left, right](const Arthropod& elem) 
			{return elem.get_max_weight() < right && elem.get_max_weight() >= left; });
	}
	case 4:
	{
		std::cout << "По скольким классам сделать выборку?\n";
		int count = read_and_check(0, 3);
		std::vector<Class> valid_classes{ Insect, Crustacean, Arachnid };
		std::unordered_set<Class> classes;
		for (int i = 0; i < count; ++i)
		{
			Class clss;
			std::cout << "Доступные классы\n";
			for (int i = 0; i < valid_classes.size(); ++i)
				std::cout << i + 1 << ". " << class_to_string(valid_classes[i]) << '\n';	
			int index = read_and_check(1, (int)valid_classes.size()) - 1;
			classes.insert(valid_classes[index]);
			valid_classes.erase(valid_classes.begin() + index);
		}
		return container.selection(
			[&classes](const Arthropod& elem) 
			{return classes.count(elem.get_class()); });
	}
	}
}