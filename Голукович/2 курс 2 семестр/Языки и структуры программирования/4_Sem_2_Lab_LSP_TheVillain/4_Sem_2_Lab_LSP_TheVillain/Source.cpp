//	��������� ������� ���������, 2 ���� 9 ������, ������ 6

//	������� ������������ ����� ��������� � ������:
//  ��������, �������� ���, ��� ���� �����������
//	(������������: �������, ������, �������), ���� � �����
//	���������� ������������(������������ ���� �� ������������ ������ ��������),
//	������ ��. ������� ������� ������������ ����� �������� �������������
//	����������� ��������� �� ������ �� ���������: ��������, ���� � �����
//	������������. ����� ������� ���� ������� �� ���� ��������, ��� ��������
//	��� �����������. ��������� ����� ������ ����� �������������� ����� �������� ���������.
//	���� ������ ��� �� ������, �������� ��� �������� ������� � �������� ����� �� ��������� ��� ������ �� �������.

#include "Container.h"
#include "Villain.h"
#include <windows.h>

//	����� ����� �� ��������� ���������, ���������� a - 1, ���� ��������� ���������� ������� �����
int pick_and_check(const int a, const int b, const std::string message, int max = -1);
//	����� ��������� �����
std::fstream pick_file();
//	�����(��������) ������� �����
std::fstream pick_empty_file();

//	���� ���������� ����������
void fill_container_menu(int choice);
//	���������� ���������� � ������� �������
void fill_from_console(Container<Villain>& container);
//	���������� ���������� � ������� �����
void fill_from_file(Container<Villain>& container, bool sorted = true);

//	���� ������ � �����������
void container_menu(Container<Villain>& container);

void print_villain_template()
{
	std::cout << "Nickname\n";
	std::cout << "Real_Name\n";
	std::cout << "Monster_Type (Vampire/Zombie/Ghost/Werwolf/Skeleton/EvilClown/NotSpecified)\n";
	std::cout << "dd mm yyyy (���� ����� ���)\n";
	std::cout << "hh mm ss (��� ������ �������)\n";
	std::cout << "Is_Catched (Catched/Wanted)\n";
	std::cout << "\n������� \"---\" ����� ��������� ����\n";
}
//	������ ������� �� ����������
void print_container(Container<Villain>& container);
//	���������� ������� � ���������
void add_to_container(Container<Villain>& container);
//	�������� ������� �� ����������
void remove_from_container(Container<Villain>& container);
//	��������� ������ ������ � ����������
void edit_container(Container<Villain>& container);
//	������� ������� �� ����������
void select_from_container(Container<Villain>& container);
//	������� ����������
void clear_container(Container<Villain>& container);

/*��������� ��� ������� �������*/

std::function<bool(Villain&)> get_nickname_selector();
std::function<bool(Villain&)> get_data_selector();
std::function<bool(Villain&)> get_creature_selector();

//	������/���������� ������� 
void print_save_selected(Container<Villain>& container, std::vector<Villain>& selected);

//	������ ���������� ������ �� ����������
void print_last_from_container(Container<Villain>& container);

int main()
{
	SetConsoleOutputCP(1251);

	int choice = 1;
	while (choice != 0)
	{
		choice = pick_and_check(0, 2, "��������� ���������� �� ������� >> 1\n��������� ���������� �� ����� >> 2\n����� �� ��������� >> 0\n");
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
			std::cout << "������ �����! "; 
			std::cin.clear();
			if (max == 0)
			{
				std::cout << "��������� ���������� ������� �����!\n";
				std::cin.ignore(255, '\n');
				return a - 1;
			}
			else
				std::cout << "��������� ����\n";
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
		std::cout << "������� ��� ����� >> ";
		std::getline(std::cin, file_name);
		file = std::fstream(file_name);
		if (file.peek() != EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "���� � ����� ������ �� ���������� ��� �� �������� ������! ��������� ����.\n";
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
		std::cout << "������� ��� ����� >> ";
		std::getline(std::cin, file_name);
		file = std::fstream(file_name, std::ios::trunc | std::ios::out);
		if (file.peek() == EOF)
			flag_of_out = true;
		else
			file.close();
		if (!flag_of_out)
			std::cout << "���� � ����� ������ ��� ���������� � �������� ������! ��������� ����.\n";
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
		std::cout << "������� ������ ������ ������ �� ��������� �������:\n";
		std::istream_iterator<Villain> reader(std::cin);
		while (std::cin.good())
		{
			container.add(*reader);
			std::cout << "������� ������ ������ ������ �� ��������� �������:\n";
			reader++;
		}
		std::cin.clear();
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "������ ����������! " << exception.what() << '\n';
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
		std::cout << "������ ������ �����! " << exception.what() << '\n';
	}
	file.close();
}

void container_menu(Container<Villain>& container)
{
	int choice = 1;
	while (choice != 0)
	{
		choice = pick_and_check(0, 7, "������ ��������� ���������� >> 1\n���������� ��������� � ��������� >> 2\n"
			"�������� ��������� �� ���������� >> 3\n��������� ��������� ���������� >> 4\n"
			"������� ��������� ���������� �� ��������� �������� >> 5\n������ ���������� �������� ���������� >> 6\n"
			"������� ���������� >> 7\n��������� ������ � ������� ����������� >> 0\n");
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
		choice = pick_and_check(0, 2, "������ ���������� � ������� >> 1\n������ ���������� � ���� >> 2\n�� �������� ��������� >> 0\n");
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
		std::cout << "������� ��������� ����!\n";
}

void add_to_container(Container<Villain>& container)
{
	int choice = pick_and_check(0, 2, "�������� ������ ������ � ������� ������� >> 1\n�������� ������ ������ � ������� ����� >> 2\n"
		"�� ��������� ������ ������ � ��������� >> 0\n");
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
		int index = pick_and_check(0, size, "������� [1-" + std::to_string(size) + "]-�� ������ �� ���������� >> [1-"
			+ std::to_string(size) + "]\n�� ������� ������� �� ���������� >> 0\n");
		if (index == 0)
			return;
		try
		{
			std::cout << container.remove(index - 1);
			std::cout << "\n������ ������ ��� ������ �� ����������.\n";
		}
		catch (std::out_of_range)
		{
			std::cout << "����� �� ������� ����������! �������� ����������!\n";
		}
	}
	else
		std::cout << "������� ��������� ����!\n";
}

void edit_container(Container<Villain>& container)
{
	int size = container.size();
	if (size > 0)
	{
		int choice = pick_and_check(0, 2, "�������� [1-" + std::to_string(size) + "]-�� ������ � ���������� � ������� ������� >> 1\n"
			+ "�������� [1-" + std::to_string(size) + "]-�� ������ � ���������� � ������� ����� >> 2\n"
			+ "�� �������� ������ ������� >> 0\n");
		if (choice == 0)
			return;
		int index = pick_and_check(1, size, "������� ������ ������, ������ �������� ������ �������� [1-"
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
				std::cout << "������� ������ ������ ������ �� ��������� �������:\n";
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
			std::cout << index << "-� ������ �� ���������� ��� �������.\n";
		}
		catch (std::out_of_range)
		{
			std::cout << "����� �� ������� ����������! ��������� ����������!\n";
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "������ ����������! " << exception.what() << '\n';
		}
	}
	else
		std::cout << "������� ��������� ����!\n";
}

void select_from_container(Container<Villain>& container)
{
	if (container.size() > 0)
	{
		int choice = pick_and_check(0, 3, "������� ������� �� ���������� :\n�� �������� >> 1\n"
			"�� ���� ���������� ������������ >> 2\n�� ���� �������, ��� �������� ����������� >> 3\n��������� ������ � �������� >> 0\n");
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
		std::cout << "������� ��������� ����!\n";
}

std::function<bool(Villain&)> get_nickname_selector()
{
	std::cout << "������� ��������, �� �������� ������ ������� �������\n>> ";
	std::string nickname;
	std::getline(std::cin, nickname);
	return [nickname](Villain& villain) { return villain.get_nickname() == nickname; };
}

std::function<bool(Villain&)> get_data_selector()
{
	tm date;
	std::cout << "dd mm yyyy (���� ����� ���)\n";
	std::cout << "hh mm ss (��� ������ �������)\n\n";
	std::cout << "������� ���� � ����� ���������� ������������, ������������ �������, �� ��������� �������:\n";
	int flag_of_out = 0;
	while (flag_of_out != -1)
	{
		try
		{
			int date_time = 0;
			if (std::cin >> date_time && date_time >= 1 && date_time <= 31)
				date.tm_mday = date_time - 1;
			else
				throw std::invalid_argument("����!");
			if (std::cin >> date_time && date_time >= 1 && date_time <= 12 && (date_time != 2 || date_time == 2 && date.tm_mday < 30))
				date.tm_mon = date_time - 1;
			else
				throw std::invalid_argument("�����!");
			if (std::cin >> date_time && date_time >= 1900)
				date.tm_year = date_time - 1900;
			else
				throw std::invalid_argument("���!");
			if (std::cin >> date_time && date_time >= 0 && date_time <= 23)
				date.tm_hour = date_time;
			else
				throw std::invalid_argument("���!");
			if (std::cin >> date_time && date_time >= 0 && date_time <= 59)
				date.tm_min = date_time;
			else
				throw std::invalid_argument("������!");
			if (std::cin >> date_time && date_time >= 0 && date_time <= 59)
				date.tm_sec = date_time;
			else
				throw std::invalid_argument("�������!");
			flag_of_out = -1;
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "\n������! " << exception.what() << '\n';
			flag_of_out++;
			if (flag_of_out == 3)
			{
				std::cout << "��������� ���������� ������� �����!\n";
				return NULL;
			}
			std::cout << "��������� ���� �� ��������� �������:\n";
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
	std::cout << "������� ���� �� ����� ��������, �� �������� ������ ������� �������\n>> ";
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
				throw std::invalid_argument("�������� ��� �������!");
			}
			flag_of_out = -1;
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "\n������ �����! " << exception.what() << '\n';
			flag_of_out++;
			if (flag_of_out == 3)
			{
				std::cout << "��������� ���������� ������� �����!\n";
				return NULL;
			}
			std::cout << "��������� ����\n>> ";
		}
	}

	return [creature](Villain& value) { return value.get_creature() == creature; };
}

void print_save_selected(Container<Villain>& container, std::vector<Villain>& selected)
{
	int choice = pick_and_check(0, 2, "������ ������� ������� � ������� >> 1\n������ ������� ������� � ���� >> 2\n"
		"�� �������� ������� ������� >> 0\n");
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
		std::cout << "���� � ������� �������� ������� ��������.\n";
		break;
	}
	default:
		return;
	}

	choice = pick_and_check(0, 1, "��������� ������� � ������� ���������?\n�� >> 1\n��� >> 0\n");
	if (choice == 1)
	{
		container.set(selected);
		std::cout << "������� ��������� � ������� ���������.\n";
	}
}

void print_last_from_container(Container<Villain>& container)
{
	if (container.size() > 0)
	{
		int choice = pick_and_check(0, 2, "������ ���������� ������ � ������� >> 1\n������ ���������� ������ � ���� >> 2\n"
			"�� �������� ��������� ������� ���������� >> 0\n");
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
		std::cout << "������� ��������� ����!\n";
}

void clear_container(Container<Villain>& container)
{
	if (container.size() > 0)
	{
		container.clear();
		std::cout << "������� ��������� ��� ������.\n";
	}
	else
		std::cout << "������! ������� ��� ��������� ����!\n";
}