#include <iostream>
#include <fstream>
#include <chrono>
#include "Windows.h"
#include "IOlib.h"

import Manuscript;
import Library;
import Temple;
import TempleList;


constexpr const char* SOURCE_MENU_TEXT = "\n1. Загрузить данные из файла\n"
										"2. Загрузить данные из консоли\n"
										"3. Продолжить с текущими данными\n"
										"4. Выход\n";

constexpr const char* MAIN_MENU_TEXT = "\n1. Распечатать на экран\n"
										"2. Сохранить в файл\n"
										"3. Добавить храм\n"
										"4. Удалить храм по названию\n"
										"5. Найти храм по названию (просмотреть)\n"
										"6. Редактировать храм\n"
										"7. Переместить рукопись\n"
										"8. Отчет для великого императора\n"
										"9. Выход\n";

constexpr const char* TEMPLE_MENU_TEXT = "\n1. Изменить название храма\n"
											"2. Сменить монаха\n"
											"3. Добавить рукопись\n"
											"4. Удалить рукопись\n"
											"5. Изменить рукопись\n"
											"6. Выборка рукописей\n"
											"7. Выход\n";


void read_from_file(TempleList& temples);
void read_from_console(TempleList& temples);

void show_manuscript_sample();
void show_temple_sample();

void lib_selection_symbols(Library<Manuscript>& lib);
void lib_selection_date(Library<Manuscript>& lib);
void lib_selection_author(Library<Manuscript>& lib);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	TempleList temples;
	ushort source_choice{};
	do
	{
		source_choice = menu(SOURCE_MENU_TEXT, 4);
		switch (source_choice)
		{
		case 1:
			read_from_file(temples);
			break;
		case 2:
			read_from_console(temples);
			break;
		default:
			break;
		}

		if (source_choice != 4)
		{
			ushort main_menu_choice{};
			do
			{
				main_menu_choice = menu(MAIN_MENU_TEXT, 9);
				try
				{
					switch (main_menu_choice)
					{
					case 1:
						std::cout << temples << '\n';
						break;
					case 2:
					{
						std::string out_file_name = input("Введите имя файла для вывода\n");
						std::ofstream file(out_file_name);
						file << temples;
						std::cout << "Данные успешно выведены в " << out_file_name << '\n';
						break;
					}
					case 3:
					{
						std::cout << "Введите данные по шаблону\n\n";
						show_temple_sample();
						std::cin.ignore(std::cin.rdbuf()->in_avail());
						Temple newTemple;
						std::cin >> newTemple;
						temples.add(newTemple);
						break;
					}
					case 4:
						temples.remove(input("Введите название храма"));
						break;
					case 5:
					{
						const Temple& temple = temples.get_temple_ref(input("Введите название храма"));
						std::cout << temple << '\n';
						break;
					}
					case 6:
					{
						ushort temple_menu_choice{};
						do
						{
							temple_menu_choice = menu(TEMPLE_MENU_TEXT, 7);
							if (temple_menu_choice != 7)
							{
								std::string temple_name = input("Введите название храма для редактирования");
								Library<Manuscript>& library = temples.get_temple_ref(temple_name).get_library();

								switch (temple_menu_choice)
								{
								case 1:
									temples.change(temple_name, input("Введите новое название храма"));
									break;
								case 2:
								{
									std::string new_monk_name = input("Введите имя нового монаха");
									uint new_diligence{};
									validation(new_diligence, [](uint x) {return x > 0 && x <= 100; }, "Введите усердность, %");
									temples.change(temple_name, new_monk_name, new_diligence);
									break;
								}
								case 3:
								{
									std::cout << "Введите данные по шаблону\n\n";
									show_manuscript_sample();
									std::cin.ignore(std::cin.rdbuf()->in_avail());
									Manuscript new_manuscript;
									std::cin >> new_manuscript;
									ushort c = menu("Куда добавить рукопись?\n1. Слева от монаха\n2.Справа от монаха\n", 2);
									c == 1 ? library.add_left(new_manuscript) : library.add_right(new_manuscript);
									break;
								}
								case 4:
								{
									ushort c = menu("Где удалить рукопись?\n1. Слева от монаха\n2. Справа от монаха\n", 2);
									c == 1 ? library.remove_left() : library.remove_right();
									break;
								}
								case 5:
								{
									ushort c = menu("Где изменить рукопись?\n1. Слева от монаха\n2. Справа от монаха\n", 2);
									std::cout << "Введите данные по шаблону\n\n";
									show_manuscript_sample();
									std::cin.ignore(std::cin.rdbuf()->in_avail());
									Manuscript new_manuscript;
									std::cin >> new_manuscript;
									c == 1 ? library.change_left(new_manuscript) : library.change_right(new_manuscript);
									break;
								}
								case 6:
								{
									ushort c = menu("Выберите критерий для выборки\n1. По количеству символов\n2. По дате\n 3. По автору\n");
									switch (c)
									{
									case 1:
									{
										lib_selection_symbols(library);
										break;
									}
									case 2:
									{
										lib_selection_date(library);
										break;
									}
									case 3:
									{
										lib_selection_author(library);
										break;
									}
									}
									break;
								}
								default:
									break;
								}
							}
						} while (temple_menu_choice != 7);
						break;
					}
					case 7:
					{
						std::string from_temple_name = input("Введите название храма из которого переместить");
						std::string to_temple_name = input("Введите название храма в который переместить");
						bool from_side{}, to_side{};
						from_side = menu("Откуда взять рукопись:\n1.Слева\n2.Справа\n", 2) - 1;
						to_side = menu("Как добавить рукопись:\n1.Слева\n2.Справа\n", 2) - 1;
						temples.move(from_temple_name, from_side, to_temple_name, to_side);
						std::cout << "1:\n" << temples.get_temple_ref(from_temple_name) << "2:\n" <<
							temples.get_temple_ref(to_temple_name) << '\n';
						break;
					}
					case 8:
						temples.about(std::cout);
						break;
					case 9:
						break;
					}
				}
				catch (std::exception exception)
				{
					std::cout << "Ошибка: " << exception.what() << '\n';
				}
				
			} while (main_menu_choice != 9);
		}
	} while (source_choice != 4);

}


void read_from_file(TempleList& temples)
{
	short file_status{};
	while (file_status != 1)
	{
		std::string filename = input("Введите имя файла");
		std::fstream file(filename, std::fstream::in);
		switch (file_status = check_file(file))
		{
		case -1:
			std::cout << filename << " не найден\n";
			break;
		case 0:
			std::cout << filename << " пуст\n";
			break;
		case 1:
			try
			{
				file >> temples;
				std::cout << filename << " успешно прочитан\n";
			}
			catch (std::exception& exception)
			{
				file_status = -1;
				std::cout << "Ошибка чтения файла: \n" << exception.what() << '\n';
			}
			break;
		}
		file.close();
	}
}

void read_from_console(TempleList& temples)
{
	std::cout << "Введите данные по шаблону\n\n";
	show_temple_sample();
	try
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> temples;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "Ошибка чтения! " << exception.what() << '\n';
	}

}

void show_manuscript_sample()
{
	std::cout << "Табличка\nИмя автора\n1890-05-21\nТекст\n" <<
		"Вместо таблички также может быть: Пергамент, Свиток или Книга\n\n";
}

void show_temple_sample()
{
	std::cout << "Название храма\nИмя монаха\n20(усердность)\n\nКнига (Свиток, Пергамент, Табличка)"
		"\nАвтор книги\n1866-11-16\nТекст\n\n========================================\n";
}

void lib_selection_symbols(Library<Manuscript>& library)
{
	uint left{}, right{};
	validation(left, [](uint x) {return x > 0; }, "Введите минимальное количество символов");
	validation(right, [left](uint x) {return x > 0 && x < left; }, "Введите максимальное количество символов");
	auto res = library.selection([left, right](const Manuscript& elem) {return right > elem.get_text().size() && left <= elem.get_text().size(); });
	std::cout << res << '\n';
}

void lib_selection_date(Library<Manuscript>& library)
{
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "Вводите даты по образцу: 1980-05-01\n";
	std::chrono::year_month_day date1{}, date2{};
	bool fl{ false };
	while (!fl)
	{
		std::cout << "Введите левое значение интервала даты\n";
		std::chrono::from_stream(std::cin, "%F", date1);
		std::cin.ignore();
		if (std::cin.fail())
			throw std::invalid_argument("Недопустимое значение даты\n");
		std::cout << "Введите правое значение интервала даты\n";
		std::chrono::from_stream(std::cin, "%F", date2);
		if (std::cin.fail())
			throw std::invalid_argument("Недопустимое значение даты\n");
		if (date1 < date2)
			fl = true;
		else
			std::cout << "Правая граница не должна быть меньше левой.\n";
	}
	auto res = library.selection([date1, date2](const Manuscript& elem) {return date2 > elem.get_date() && date1 <= elem.get_date(); });
	std::cout << res << '\n';
}

void lib_selection_author(Library<Manuscript>& library)
{
	std::string author = input("Введите имя автора");
	auto res = library.selection([author](const Manuscript& elem) {return author == elem.get_author(); });
	std::cout << res << '\n';
}
