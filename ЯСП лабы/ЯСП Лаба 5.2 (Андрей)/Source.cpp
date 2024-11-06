// Аникандров 9 группа 2 курс
// 3 вариант

/*
Программа должна содержать шаблонный класс-контейнер для управления данными:
структурой или классом, указанными в задании. Для хранения данных необходимо
выбрать оптимальный с точки зрения задания контейнер.

Реализовать следующие функции:
	Добавление элемента контейнера;
	Удаление элемента контейнера;
	Изменение элемента контейнера;
	Ввод элементов контейнера с использованием потоковых итераторов на экран и в файл;
	Вывод элементов контейнера с использованием потоковых итераторов на экран и в файл;
	Выборка подмножества элементов по заданным критериям с помощью алгоритма линейного поиска.
	Выбранные подмножества должны мочь выводиться на экран и в файл.
*/

/*
«Демон» представляет собой структуру с полями:
название, происхождение (строка), рост (в см.),
оружие (строка), количество рогов, время, которое он может
провести в мире живых за один раз (использовать одну из предлагаемых языком
структур), цвет (перечисление).
*/

/*
Выборка демонов производится путем указания
пользователем подходящего интервала по одному из критериев: время, рост, число рогов.
*/

/*
Также выборка всех демонов указанного цвета, выборка всех демонов с указанным оружием.
Шаблонный класс должен иметь дополнительный метод — удаление по условию.
Реализовать удаление по: цвету, удаление по происхождению
*/

#include "DemonH.h"
#include "ListH.h"

using T = Demon;

void selection_delete(List<T>& demons)
{
	List<T> result;
	std::cout << "Удаление по..";
	std::cout << "\n0. ..цвету \n";
	std::cout << "1. ..происхождению \n> ";
	int remove_choice = read_check_int(std::cin, 0, 1);

	if (remove_choice == 0)
	{
		std::cout << "\nВведите цвет > ";
		std::string str;
		
		std::cin.ignore(255, '\n');
		std::getline(std::cin, str);

		int num;
		if (str == "Красный")
			num = 0;
		else if (str == "Синий")
			num = 1;
		else if (str == "Зелёный")
			num = 2;
		else 
			num = 3;

		Color color = static_cast<Color>(num);

		auto condition = [color](T& demon) { return demon.get_color() == color; };
		result.set(demons.get_list());
		result.condition_remove(condition);	
	}
	else
	{
		std::cout << "\nВведите происхождение: \n> ";
		std::string str;
		std::cin.ignore(255, '\n');
		std::getline(std::cin, str);

		auto condition = [str](Demon& demon) { return demon.get_origin() == str; };
		result.set(demons.get_list());
		result.condition_remove(condition);	
	}
	
	result.print_beautiful_console();
	demons = result;	
}

void selection(List<T>& demons)
{
	List<T> selection;
	std::cout << "\nВыборка по.. \n";
	std::cout << "\n1. ..времени \n";
	std::cout << "2. ..росту \n";
	std::cout << "3. ..рогов \n";
	std::cout << "4. ..цвету \n";
	std::cout << "5. ..оружию\n> ";

	int selection_choice = read_check_int(std::cin, 1, 5);
	std::cin.ignore(255, '\n');

	if (selection_choice == 1) // по времени
	{
		int min_num, max_num;
		read_min_max(std::cin, min_num, max_num);

		auto condition = [&min_num, &max_num](T demon) { return demon.get_time() >= min_num && demon.get_time() <= max_num; };
		selection.set(demons.get_by_condition(condition));
	}
	else if (selection_choice == 2) // по росту
	{
		int min_num, max_num;
		read_min_max(std::cin, min_num, max_num);

		auto condition = [min_num, max_num](T demon) { return demon.get_height() >= min_num && demon.get_height() <= max_num; };
		selection.set(demons.get_by_condition(condition));
		
	}
	else if (selection_choice == 3) // по рогам
	{
		int min_num, max_num;
		read_min_max(std::cin, min_num, max_num);

		auto condition = [&min_num, &max_num](T demon) { return demon.get_horn() >= min_num && demon.get_horn() <= max_num; };
		selection.set(demons.get_by_condition(condition));
		
	}
	else if (selection_choice == 4) // по цвету
	{
		std::cout << "\nВведите цвет > ";
		std::string str;
		std::getline(std::cin, str);
		int num;
		if (str == "Красный")
			num = 0;
		else if (str == "Синий")
			num = 1;
		else if (str == "Зелёный")
			num = 2;
		else 
			num = 3;
		Color color(static_cast<Color>(num));
		auto condition = [&color](T demon) { return demon.get_color() == color; };
		selection.set(demons.get_by_condition(condition));
		
	}
	else if (selection_choice == 5) // по оружию
	{
		std::cout << "\nВведите оружие > ";
		std::string str;
		std::getline(std::cin, str);

		auto condition = [&str](T demon) { return demon.get_weapon() == str; };
		selection.set(demons.get_by_condition(condition));
	}
	if (!selection.check_empty())
	{
		std::cout << "\nВыборка:\n";
		//selection.print_list();
		selection.print_beautiful_console();
	}
	else
		std::cout << "\nВыборка пуста\n";
}

void menu()
{
	List<T> demons;

	bool flag1 = true;

	std::cout << "0. Заполнить из файла \n";
	std::cout << "1. Пустой контейнер \n> ";

	int choice1 = read_check_int(std::cin, 0, 1);

	if (choice1 == 0)
	{
		std::string file_name = name_file();
		std::fstream file(file_name);

		
		if (check_demons_file(file_name))
			demons.fill_list(file);
		else
			std::cout << "Файл содержит очепятку. Создан пустой контейнер.\n";
	}

	while (flag1)
	{
		std::cout << "\n1. Добавить элементы\n";
		std::cout << "2. Удалить элемент \n";
		std::cout << "3. Изменить элемент \n";
		std::cout << "4. Печать в консоль\n";
		std::cout << "5. Вывод в файл\n";
		std::cout << "6. Выборка по условию \n";
		std::cout << "7. Удаление по условию\n";
		std::cout << "0. выход. \n> ";
		
		int choice2 = read_check_int(std::cin, 0, 7);

		switch (choice2)
		{
		case 1: // Добавить
		{
			bool flag2 = true;
			do
			{
				T demon;
				read_demon(std::cin, demon);
				demons.add_elem(demon);

				std::cout << "Продолжить добавление?\n";
				std::cout << "0. Нет	1. Да\n> ";
				int choice;
				choice = read_check_int(std::cin, 0, 1);
				if (!choice)
					flag2 = false;
			} while (flag2);

			break;
		}
		case 2: // Удалить
		{
			if (!demons.check_empty())
			{
				std::cout << "\nВведи индекс удаляемого демона (0.." << demons.get_size() - 1 << ") >";
				int index = read_check_int(std::cin, 0, demons.get_size() - 1);
				demons.delete_elem(index);
			}
			else
				std::cout << "Демонов нет\n";
			break;
		}
		case 3: // Изменить
		{
			if (!demons.check_empty())
			{
				std::cout << "\nВведи индекс изменяемого демона (0.." << demons.get_size() - 1 << ") > ";
				int index = read_check_int(std::cin, 0, demons.get_size() - 1);

				T d;
				read_demon(std::cin, d);
				demons.change_elem(index, d);
			}
			else
				std::cout << "Демонов нет\n";
			break;
		}
		case 4: // Напечатать
		{
			if (!demons.check_empty())
				demons.print_beautiful_console();
				//demons.print_list();
			else
				std::cout << "Демонов нет\n";
			break;
		}
		case 5: // Файл
		{
			if (!demons.check_empty())
			{
				std::string file_name;
				std::cout << "Введите имя файла > ";
				std::cin >> file_name;
				std::ofstream file(file_name);

				demons.print_list(file);
			}
			else
				std::cout << "Демонов нет\n";
			break;
		}
		case 6: // Выборка
		{
			if (!demons.check_empty())
				selection(demons);
			else
				std::cout << "Демонов нет\n";	
			break;
		}
		case 7: // Удаление
		{
			if (!demons.check_empty())
				selection_delete(demons);
			else
				std::cout << "Демонов нет\n";
			break;
		}
		case 0: // Выход
		{
			flag1 = false;
			break;
		}
		}
	}
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	menu();
}