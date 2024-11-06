#include "Stats.h"
#include <Windows.h>


void demonstration(int choice);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice{};
	do
	{
		choice = main_menu();
		demonstration(choice);
	} while (choice != 0);

	return 0;
}

void demonstration(int choice)
{
	switch (choice)
	{
	case 0:
		break;
	case 1:
	{
		std::fstream file = choose_empty_file();
		std::cout << "Введите количество элементов в файле(от 1 до 1000000): ";
		int count = read_and_check(1, 1000000);
		fill_file(file, count);
		std::cout << "Файл успешно сгенерирован!\n";
		file.close();		
		break;
	}		
	case 2:
	{
		std::fstream file = choose_file();
		print_file(file);
		file.close();
		break;
	}
	case 3:
	{
		std::string filename = choose_file_name();
		sorting(filename);
		std::cout << "Файл успешно отсортирован!\n";
		break;
	}
	case 4:
	{
		std::fstream file = choose_file();
		if (check_file_orderliness(file))
			std::cout << "Файл упорядочен\n";
		else
			std::cout << "Файл не упорядочен\n";
		file.close();
		break;
	}
	case 5:
		calculate_stats();
		break;
	case 6:
		build_graphic();
		break;
	}
}
