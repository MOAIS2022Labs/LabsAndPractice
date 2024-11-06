// Гаршин Максим. Задача №3

// Программа должна содержать шаблонный класс - контейнер для управления данными:
// структурой или классом, указанными в задании. Для хранения данных необходимо
// выбрать оптимальный с точки зрения задания контейнер. Реализовать следующие функции:
// Добавление элемента контейнера;
// Удаление элемента контейнера;
// Изменение элемента контейнера;
// Ввод элементов контейнера с использованием потоковых итераторов на экран и в файл;
// Вывод элементов контейнера с использованием потоковых итераторов на экран и в файл;
// Выборка подмножества элементов по заданным критериям с помощью алгоритма линейного поиска.

// Выбранные подмножества должны мочь выводиться на экран и в файл.

// 3. «Демон» представляет собой структуру с полями : название, происхождение (строка), 
// рост(в см.), оружие(строка), количество рогов, время, которое он может
// провести в мире живых за один раз(использовать одну из предлагаемых языком структур), 
// цвет(перечисление). Выборка демонов производится путем указания
// пользователем подходящего интервала по одному из критериев : время, рост, число рогов. 
// Также выборка всех демонов указанного цвета, выборка всех демонов с указанным оружием.
// Шаблонный класс должен иметь дополнительный метод —
// удаление по условию. Реализовать удаление по : цвету, удаление по происхождению.

#include "DemonsContainer.h"
#include "Demon.h"
#include <Windows.h>
#include <fstream>

typedef Demon T;

void vvod_min_and_max(std::istream& stream, int& min, int& max)
{
	std::cout << "\nВведите минимальное число: \n";
	min = vvod_int(stream, 0, MAXINT);
	std::cout << "\nВведите максимальное число: \n";
	max = vvod_int(stream, 0, MAXINT);
}

// проверка на существование файла
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
			std::cout << "Введено неправильное имя файла. Повторите ввод:\n";
			std::getline(std::cin, file_name);
		}
		else
			open = true;
	}
	file.close();
}

// ввод имени файла
std::string name_file()
{
	std::cin.clear();
	std::cout << "Введите имя файла:\n";
	std::string file_name;
	std::cin.ignore();
	std::getline(std::cin, file_name);
	check_name_file(file_name);
	return file_name;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	DemonContainer<T> list_of_demons;
	bool flag1 = true;
	while (flag1)
	{

		std::cout << "0. Заполнить контейнер из файла. \n";
		std::cout << "1. Ввести элемент вручную. \n";

		int choice1 = vvod_int(std::cin, 0, 1);

		if (choice1 == 0)
		{
			std::string filename = name_file();
			std::fstream file(filename);
			std::istream_iterator<T> inputBegin(file), inputEnd;
			list_of_demons.fill_list(inputBegin, inputEnd);
		}
		else if (choice1 == 1)
		{
			std::cout << "\nВведите данные демона в следующем виде:\n\n";
			std::cout << "\nИмя\n";
			std::cout << "Происхождения \n";
			std::cout << "Рост \n";
			std::cout << "Оружие \n";
			std::cout << "Количество рогов \n";
			std::cout << "Количество часов жизни \n";
			std::cout << "Цвет \n";
			T demon;
			std::cin >> demon;
			list_of_demons.add_demon(demon);
		}
		std::cout << "\n0. Завершить работу. \n";
		std::cout << "1. Продолжить заполнение. \n";
		std::cout << "2. Перейти к основному меню. \n";
		bool flag2 = false;
		int choice = vvod_int(std::cin, 0, 2);
		if (choice == 0)
			flag1 = false;
		else if (choice == 2)
			flag2 = true;

		while (flag2)
		{
			std::cout << "\n0. Добавить элемент в контейнер. \n";
			std::cout << "1. Удалить элемент контейнера. \n";
			std::cout << "2. Изменить элемент контейнера. \n";
			std::cout << "3. Напечатать контейнер (в файл или на консоль). \n";
			std::cout << "4. Выборка по условию. \n";
			std::cout << "5. Удаление по условию. \n";
			std::cout << "6. Выход. \n";
			int choice2 = vvod_int(std::cin, 0, 6);

			switch (choice2)
			{
			case 0: // Добавить
			{
				std::cout << "\nВведите данные демона в следующем виде:\n\n";
				std::cout << "\nИмя\n";
				std::cout << "Происхождения \n";
				std::cout << "Рост \n";
				std::cout << "Оружие \n";
				std::cout << "Количество рогов \n";
				std::cout << "Количество часов жизни \n";
				std::cout << "Цвет \n";
				T demon;
				std::cin >> demon;
				list_of_demons.add_demon(demon);
				break;
			}
			case 1: // Удалить
			{
				if (list_of_demons.get_size() > 0)
				{
					std::cout << "\nВведите индекс удаляемого демона от 0 до " << list_of_demons.get_size() - 1 << "\n";
					int index = vvod_int(std::cin, 0, list_of_demons.get_size() - 1);
					list_of_demons.delete_demon(index);
				}
				else
					std::cout << "Список пустой\n";
				break;
			}
			case 2: // Изменить
			{
				if (list_of_demons.get_size() > 0)
				{
					std::cout << "\nВведите индекс изменяемого демона от 0 до " << list_of_demons.get_size() - 1 << "\n";
					int index = vvod_int(std::cin, 0, list_of_demons.get_size() - 1);
					list_of_demons.change_demon(index);
				}
				else
					std::cout << "Список пустой\n";
				break;
			}
			case 3: // Напечатать
			{
				std::cout << "\n0. Печать на консоль. \n";
				std::cout << "1. Печать в файл. \n";
				int num = vvod_int(std::cin, 0, 1);
				if (num == 0)
				{
					std::ostream_iterator<T> consoleOutput(std::cout, "");
					list_of_demons.print_list(consoleOutput);
				}
				else
				{
					std::string filename;
					std::cout << "Введите имя текстового файла --> ";
					std::cin >> filename;
					std::ofstream file(filename);
					std::ostream_iterator<T> fileOutput(file, "");
					list_of_demons.print_list(fileOutput);
				}
				break;
			}
			case 4: // Выборка
			{
				DemonContainer<T> selection;
				std::cout << "\n0. Выборка по времени. \n";
				std::cout << "1. Выборка по росту. \n";
				std::cout << "2. Выборка по числу рогов. \n";
				std::cout << "3. Выборка по цвету. \n";
				std::cout << "4. Выборка по оружию. \n";

				int selection_choice = vvod_int(std::cin, 0, 4);
				std::cin.ignore(255, '\n');
				int min_num{}, max_num{};
				
				if (selection_choice == 0)
				{
					vvod_min_and_max(std::cin, min_num, max_num);
					auto condition = [min_num, max_num](T demon) { return demon.get_time() >= min_num && demon.get_time() <= max_num; };
					selection.set(list_of_demons.get_demons_by_condition(condition));
				}
				else if (selection_choice == 1)
				{
					vvod_min_and_max(std::cin, min_num, max_num);
					auto condition = [min_num, max_num](T demon) { return demon.get_height() >= min_num && demon.get_height() <= max_num; };
					selection.set(list_of_demons.get_demons_by_condition(condition));
				}
				else if (selection_choice == 2)
				{
					vvod_min_and_max(std::cin, min_num, max_num);
					auto condition = [min_num, max_num](T demon) { return demon.get_horn_count() >= min_num && demon.get_horn_count() <= max_num; };
					selection.set(list_of_demons.get_demons_by_condition(condition));
				}
				else if (selection_choice == 3)
				{
					std::cout << "\nВведите цвет: \n";
					std::string str;
					std::getline(std::cin, str);
					int num = 3;
					if (str == "Красный")
						num = 0;
					else if (str == "Синий")
						num = 1;
					else if (str == "Зелёный")
						num = 2;
					else if (str == "Чёрный")
						num = 3;
					else if (str == "Белый")
						num = 4;
					Color color(static_cast<Color>(num));
					auto condition = [color](T demon) { return demon.get_color() == color; };
					selection.set(list_of_demons.get_demons_by_condition(condition));
				}
				else if (selection_choice == 4)
				{
					std::cout << "\nВведите оружие: \n";
					std::string str;
					std::getline(std::cin, str);

					auto condition = [str](T demon) { return demon.get_weapon() == str; };
					selection.set(list_of_demons.get_demons_by_condition(condition));
				}
				std::cout << "\nВыборка:\n";
				std::ostream_iterator<T> consoleOutput(std::cout, "");
				selection.print_list(consoleOutput);
				break;
			}
			case 5: // Удаление
			{
				DemonContainer<T> selection_after_removing;
				std::cout << "\n0. Удаление по цвету. \n";
				std::cout << "1. Удаление по происхождению. \n";
				int remove_choice = vvod_int(std::cin, 0, 1);

				if (remove_choice == 0)
				{
					std::cout << "\nВведите цвет: \n";
					std::string str;
					int num{};
					std::cin.ignore(255, '\n');
					std::getline(std::cin, str);
					if (str == "Красный")
						num = 0;
					else if (str == "Синий")
						num = 1;
					else if (str == "Зелёный")
						num = 2;
					else if (str == "Чёрный")
						num = 3;
					else if (str == "Белый")
						num = 4;
					Color color = static_cast<Color>(num);
					auto condition = [color](T& demon) { return demon.get_color() == color; };

					selection_after_removing.set(list_of_demons.get_list());
					selection_after_removing.remove_demons_by_condition(condition);
				}
				else
				{
					std::cout << "\nВведите происхождение: \n";
					std::string str;
					std::cin.ignore(255, '\n');
					std::getline(std::cin, str);

					auto condition = [str](Demon& demon) { return demon.get_origin() == str; };

					selection_after_removing.set(list_of_demons.get_list());
					selection_after_removing.remove_demons_by_condition(condition);
				}
				std::ostream_iterator<T> consoleOutput(std::cout, "");
				selection_after_removing.print_list(consoleOutput);
				break;
			}
			case 6: // Выход
				flag2 = false;
				std::cout << "\nЗакончить?\n0. Да\n1. Нет\n--> ";
				choice1 = vvod_int(std::cin, 0, 1);
				flag1 = choice1;
				list_of_demons.clear();
				break;
			}
		}
	}
}