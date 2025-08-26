//	Голукович Тимофей Сергеевич, 2 курс 9 группа, задача 6

//	«Злодей» представляет собой структуру с полями:
//  прозвище, реальное имя, под кого маскируется
//	(перечисление: призрак, вампир, монстр…), дата и время
//	последнего преступления(использовать одну из предлагаемых языком структур),
//	пойман ли. Выборка злодеев производится путем указания пользователем
//	подходящего интервала по одному из критериев: прозвище, дата и время
//	преступления. Также выборка всех злодеев по типу создания, под которого
//	они маскируются. Шаблонный класс должен иметь дополнительный метод «извлечь последний».
//	Если злодей еще не пойман, заменять все значимые символы в реальном имени на звездочки при печати на консоль.

#include "Container.h"
#include "Villain.h"
#include <windows.h>

//	выбор числа из заданного диапазона, возвращает a - 1, если превышено количество попыток ввода
int pick_and_check(const int a, const int b, const std::string message, int max = -1);
//	выбор непустого файла
std::fstream pick_file();
//	выбор(создание) пустого файла
std::fstream pick_empty_file();

//	меню заполнения контейнера
void fill_container_menu(int choice);
//	заполнение контейнера с помощью консоли
void fill_from_console(Container<Villain>& container);
//	заполнение контейнера с помощью файла
void fill_from_file(Container<Villain>& container, bool sorted = true);

//	меню работы с контейнером
void container_menu(Container<Villain>& container);

void print_villain_template()
{
	std::cout << "Nickname\n";
	std::cout << "Real_Name\n";
	std::cout << "Monster_Type (Vampire/Zombie/Ghost/Werwolf/Skeleton/EvilClown/NotSpecified)\n";
	std::cout << "dd mm yyyy (день месяц год)\n";
	std::cout << "hh mm ss (час минута секунда)\n";
	std::cout << "Is_Catched (Catched/Wanted)\n";
	std::cout << "\nВведите \"---\" чтобы закончить ввод\n";
}
//	печать злодеев из контейнера
void print_container(Container<Villain>& container);
//	добавление злодеев в контейнер
void add_to_container(Container<Villain>& container);
//	удаление злодеев из контейнера
void remove_from_container(Container<Villain>& container);
//	изменение данных злодея в контейнере
void edit_container(Container<Villain>& container);
//	выборка злодеев из контейнера
void select_from_container(Container<Villain>& container);
//	очистка контейнера
void clear_container(Container<Villain>& container);

/*селекторы для выборок злодеев*/

std::function<bool(Villain&)> get_nickname_selector();
std::function<bool(Villain&)> get_data_selector();
std::function<bool(Villain&)> get_creature_selector();

//	печать/сохранение выборки 
void print_save_selected(Container<Villain>& container, std::vector<Villain>& selected);

//	печать последнего злодея из контейнера
void print_last_from_container(Container<Villain>& container);

int main()
{
	SetConsoleOutputCP(1251);

	int choice = 1;
	while (choice != 0)
	{
		choice = pick_and_check(0, 2, "Заполнить контейнера из консоли >> 1\nЗаполнить контейнера из файла >> 2\nВыход из программы >> 0\n");
		fill_container_menu(choice);
	}
	return 0;
}

int pick_and_check(const int a, const int b, const std::string message, int max)
{
	int choice = 0;
	std::cout << message;
	bool flag_of_out = false;
	while (!flag_of_out && max != 0)
	{
		if (std::cout << ">> " && std::cin >> choice && a <= choice && choice <= b)
			flag_of_out = true;
		else
		{
			max--;
			std::cout << "Ошибка ввода! "; 
			std::cin.clear();
			if (max == 0)
			{
				std::cout << "Превышено количество попыток ввода!\n";
				std::cin.ignore(255, '\n');
				return a - 1;
			}
			else
				std::cout << "Повторите ввод\n";
		}
		std::cin.ignore(255, '\n');
	}
	std::cout << '\n';
	return choice;
}

std::fstream pick_file()
{
	bool flag_of_out = false;
	std::string file_name;
	std::fstream file;
	while (!flag_of_out)
	{
		std::cout << "Введите имя файла >> ";
		std::getline(std::cin, file_name);
		file = std::fstream(file_name);
		if (file.peek() != EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "Файл с таким именем не существует или не содержит данные! Повторите ввод.\n";
	}
	std::cout << '\n';
	return file;
}

std::fstream pick_empty_file()
{
	bool flag_of_out = false;
	std::fstream file;
	std::string file_name;
	while (!flag_of_out)
	{
		std::cout << "Введите имя файла >> ";
		std::getline(std::cin, file_name);
		file = std::fstream(file_name, std::ios::trunc | std::ios::out);
		if (file.peek() == EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "Файл с таким именем уже существует и содержит данные! Повторите ввод.\n";
	}
	std::cout << '\n';
	file.seekg(0);
	return file;
}

void fill_container_menu(int choice)
{
	Container<Villain> container;
	switch (choice)
	{
	case 1:
		fill_from_console(container);
		break;
	case 2:
		fill_from_file(container);
		break;
	default:
		return;
	}
	container_menu(container);
}

void fill_from_console(Container<Villain>& container)
{
	print_villain_template();
	try
	{
		std::cout << "Введите данные нового злодея по заданному шаблону:\n";
		std::istream_iterator<Villain> reader(std::cin);
		while (std::cin.good())
		{
			container.add(*reader);
			std::cout << "Введите данные нового злодея по заданному шаблону:\n";
			reader++;
		}
		std::cin.clear();
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "Ошибка считывания! " << exception.what() << '\n';
	}
}

void fill_from_file(Container<Villain>& container, bool sorted)
{
	std::fstream file = pick_file();
	try
	{
		std::istream_iterator<Villain> reader(file);
		container.read(reader);
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "Ошибка чтения файла! " << exception.what() << '\n';
	}
	file.close();
}

void container_menu(Container<Villain>& container)
{
	int choice = 1;
	while (choice != 0)
	{
		choice = pick_and_check(0, 7, "Печать элементов контейнера >> 1\nДобавление элементов в контейнер >> 2\n"
			"Удаление элементов из контейнера >> 3\nИзменение элементов контейнера >> 4\n"
			"Выборка элементов контейнера по заданному критерию >> 5\nПечать последнего элемента контейнера >> 6\n"
			"Очистка контейнера >> 7\nЗакончить работу с текущим контейнером >> 0\n");
		switch (choice)
		{
		case 1:
			print_container(container);
			break;
		case 2:
			add_to_container(container);
			break;
		case 3:
			remove_from_container(container);
			break;
		case 4:
			edit_container(container);
			break;
		case 5:
			select_from_container(container);
			break;
		case 6:
			print_last_from_container(container);
			break;
		case 7:
			clear_container(container);
			break;
		default:
			break;
		}
		std::cout << '\n';
	}
}

void print_container(Container<Villain>& container)
{
	int choice = 0;
	if (container.size() > 0)
	{
		choice = pick_and_check(0, 2, "Печать контейнера в консоль >> 1\nПечать контейнера в файл >> 2\nНе печатать контейнер >> 0\n");
		switch (choice)
		{
		case 1:
		{
			auto writer = std::ostream_iterator<Villain>(std::cout, "\n");
			container.write(writer);
			break;
		}
		case 2:
		{
			std::fstream file = pick_empty_file();
			auto writer = std::ostream_iterator<Villain>(file);
			container.write(writer);
			file.close();
			break;
		}
		default:
			break;
		}
	}
	else
		std::cout << "Текущий контейнер пуст!\n";
}

void add_to_container(Container<Villain>& container)
{
	int choice = pick_and_check(0, 2, "Добавить нового злодея с помощью консоли >> 1\nДобавить нового злодея с помощью файла >> 2\n"
		"Не добавлять нового злодея в контейнер >> 0\n");
	switch (choice)
	{
	case 1:
		fill_from_console(container);
		break;
	case 2:
		fill_from_file(container);
		break;
	default:
		break;
	}
}

void remove_from_container(Container<Villain>& container)
{
	int size = container.size();
	if (size > 0)
	{
		int index = pick_and_check(0, size, "Удалить [1-" + std::to_string(size) + "]-го злодея из контейнера >> [1-"
			+ std::to_string(size) + "]\nНе удалять злодеев из контейнера >> 0\n");
		if (index == 0)
			return;
		try
		{
			std::cout << container.remove(index - 1);
			std::cout << "\nДанный злодей был удален из контейнера.\n";
		}
		catch (std::out_of_range)
		{
			std::cout << "Выход за пределы контейнера! Удаление невозможно!\n";
		}
	}
	else
		std::cout << "Текущий контейнер пуст!\n";
}

void edit_container(Container<Villain>& container)
{
	int size = container.size();
	if (size > 0)
	{
		int choice = pick_and_check(0, 2, "Изменить [1-" + std::to_string(size) + "]-го злодея в контейнере с помощью консоли >> 1\n"
			+ "Изменить [1-" + std::to_string(size) + "]-го злодея в контейнере с помощью файла >> 2\n"
			+ "Не изменять данные злодеев >> 0\n");
		if (choice == 0)
			return;
		int index = pick_and_check(1, size, "Введите индекс злодея, данные которого хотите изменить [1-"
			+ std::to_string(size) + "]", 3);
		if (index == 0)
			return;
		try
		{
			std::istream_iterator<Villain> reader;
			switch (choice)
			{
			case 1:
				print_villain_template();
				std::cout << "Введите данные нового злодея по заданному шаблону:\n";
				reader = std::istream_iterator<Villain>(std::cin);
				break;
			case 2:
			{
				std::fstream file = pick_file();
				reader = std::istream_iterator<Villain>(file);
				break;
			}
			default:
				return;
			}
			container.edit(index - 1, *reader);
			std::cout << index << "-й злодей из контейнера был изменен.\n";
		}
		catch (std::out_of_range)
		{
			std::cout << "Выход за пределы контейнера! Изменение невозможно!\n";
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "Ошибка считывания! " << exception.what() << '\n';
		}
	}
	else
		std::cout << "Текущий контейнер пуст!\n";
}

void select_from_container(Container<Villain>& container)
{
	if (container.size() > 0)
	{
		int choice = pick_and_check(0, 3, "Выборка злодеев из контейнера :\nПо прозвищу >> 1\n"
			"По дате последнего преступления >> 2\nПо типу монстра, под которого маскируется >> 3\nЗакончить работу с выборкой >> 0\n");
		if (choice != 0)
		{
			std::vector<Villain> selected(container.size());
			std::function<bool(Villain&)> selector;
			switch (choice)
			{
			case 1:
				selector = get_nickname_selector();
				break;
			case 2:
				selector = get_data_selector();
				break;
			case 3:
				selector = get_creature_selector();
				break;
			default:
				selector = [](Villain& vill) { return true; };
				break;
			}
			if (selector == NULL)
				return;
			selected = container.selection(selector);
			print_save_selected(container, selected);
		}
	}
	else
		std::cout << "Текущий контейнер пуст!\n";
}

std::function<bool(Villain&)> get_nickname_selector()
{
	std::cout << "Введите прозвище, по которому хотите сделать выборку\n>> ";
	std::string nickname;
	std::getline(std::cin, nickname);
	return [nickname](Villain& villain) { return villain.get_nickname() == nickname; };
}

std::function<bool(Villain&)> get_data_selector()
{
	tm date;
	std::cout << "dd mm yyyy (день месяц год)\n";
	std::cout << "hh mm ss (час минута секунда)\n\n";
	std::cout << "Введите дату и время последнего преступления, совершенного злодеем, по заданному шаблону:\n";
	int flag_of_out = 0;
	while (flag_of_out != -1)
	{
		try
		{
			int date_time = 0;
			if (std::cin >> date_time && date_time >= 1 && date_time <= 31)
				date.tm_mday = date_time - 1;
			else
				throw std::invalid_argument("День!");
			if (std::cin >> date_time && date_time >= 1 && date_time <= 12 && (date_time != 2 || date_time == 2 && date.tm_mday < 30))
				date.tm_mon = date_time - 1;
			else
				throw std::invalid_argument("Месяц!");
			if (std::cin >> date_time && date_time >= 1900)
				date.tm_year = date_time - 1900;
			else
				throw std::invalid_argument("Год!");
			if (std::cin >> date_time && date_time >= 0 && date_time <= 23)
				date.tm_hour = date_time;
			else
				throw std::invalid_argument("Час!");
			if (std::cin >> date_time && date_time >= 0 && date_time <= 59)
				date.tm_min = date_time;
			else
				throw std::invalid_argument("Минута!");
			if (std::cin >> date_time && date_time >= 0 && date_time <= 59)
				date.tm_sec = date_time;
			else
				throw std::invalid_argument("Секунда!");
			flag_of_out = -1;
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "\nОшибка! " << exception.what() << '\n';
			flag_of_out++;
			if (flag_of_out == 3)
			{
				std::cout << "Превышено количество попыток ввода!\n";
				return NULL;
			}
			std::cout << "Повторите ввод по заданному шаблону:\n";
		}
	}

	return [date](Villain& value) { tm comparere_date = value.get_date(); return comparere_date.tm_mday == date.tm_mday
		&& comparere_date.tm_mon == date.tm_mon && comparere_date.tm_year == date.tm_year
		&& comparere_date.tm_hour == date.tm_hour && comparere_date.tm_min == date.tm_min
		&& comparere_date.tm_sec == date.tm_sec; };
}

std::function<bool(Villain&)> get_creature_selector()
{
	Monster creature;
	std::cout << "Vampire/Zombie/Ghost/Werwolf/Skeleton/EvilClown/NotSpecified\n";
	std::cout << "Введите один из типов монстров, ко которому хотите сделать выборку\n>> ";
	std::string str;
	int flag_of_out = 0;
	while (flag_of_out != -1)
	{
		std::getline(std::cin, str);
		try
		{
			if (!(str == "Vampire" && (creature = Vampire)) && !(str == "Zombie" && (creature = Zombie)) && !(str == "Ghost" && (creature = Ghost))
				&& !(str == "Werwolf" && (creature = Werwolf)) && !(str == "Skeleton" && (creature = Skeleton))
				&& !(str == "EvilClown" && (creature = EvilClown)) && !(str == "NotSpecified" && (creature = NotSpecified)))
			{
				throw std::invalid_argument("Неверный тип монстра!");
			}
			flag_of_out = -1;
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "\nОшибка ввода! " << exception.what() << '\n';
			flag_of_out++;
			if (flag_of_out == 3)
			{
				std::cout << "Превышено количество попыток ввода!\n";
				return NULL;
			}
			std::cout << "Повторите ввод\n>> ";
		}
	}

	return [creature](Villain& value) { return value.get_creature() == creature; };
}

void print_save_selected(Container<Villain>& container, std::vector<Villain>& selected)
{
	int choice = pick_and_check(0, 2, "Печать текущей выборки в консоль >> 1\nПечать текущей выборки в файл >> 2\n"
		"Не печатать текущую выборку >> 0\n");
	switch (choice)
	{
	case 1:
	{
		auto writer = std::ostream_iterator<Villain>(std::cout, "\n");
		copy(selected.begin(), selected.end(), writer);
		std::cout << '\n';
		break;
	}
	case 2:
	{
		std::fstream file = pick_empty_file();
		auto writer = std::ostream_iterator<Villain>(file);
		copy(selected.begin(), selected.end(), writer);
		file.close();
		std::cout << "Файл с текущей выборкой успешно сохранен.\n";
		break;
	}
	default:
		return;
	}

	choice = pick_and_check(0, 1, "Сохранить выборку в текущий контейнер?\nДа >> 1\nНет >> 0\n");
	if (choice == 1)
	{
		container.set(selected);
		std::cout << "Выборка сохранена в текущий контейнер.\n";
	}
}

void print_last_from_container(Container<Villain>& container)
{
	if (container.size() > 0)
	{
		int choice = pick_and_check(0, 2, "Печать последнего злодея в консоль >> 1\nПечать последнего злодея в файл >> 2\n"
			"Не печатать последний элемент контейнера >> 0\n");
		switch (choice)
		{
		case 1:
		{
			std::cout << container.get_last();
			break;
		}
		case 2:
		{
			std::fstream file = pick_empty_file();
			file << container.get_last();
			file.close();
			break;
		}
		default:
			break;
		}
	}
	else
		std::cout << "Текущий контейнер пуст!\n";
}

void clear_container(Container<Villain>& container)
{
	if (container.size() > 0)
	{
		container.clear();
		std::cout << "Текущий контейнер был очищен.\n";
	}
	else
		std::cout << "Ошибка! Текущий уже контейнер пуст!\n";
}