#include "PrisonsActions.h"



//������ � �������
void print_villain_template()
{
	std::cout << "Nickname\n";
	std::cout << "Real_Name\n";
	std::cout << "Monster_Type (Vampire/Zombie/Ghost/Werwolf/Skeleton/EvilClown/NotSpecified)\n";
	std::cout << "dd mm yyyy (���� ����� ���)\n";
	std::cout << "hh mm ss (��� ������ �������)\n";
	std::cout << "Is_Catched (Catched/Wanted)\n";
	std::cout << "\n������� \"---\" ����� ��������� ����\n";
	std::cout << "������� ������ ����� ������� �� ��������� �������:\n";
}



bool int_input(int& val)
{
	return bool(std::cout << ">> " && std::cin >> val);
};

bool file_name_input(std::fstream& prison_file)
{
	std::string file_name;
	std::cout << "������� ��� ����� >> ";
	std::getline(std::cin, file_name);
	prison_file = std::fstream(file_name);
	return true;
};

bool not_empty_file_predicate(std::fstream& prison_file)
{
	if (prison_file.peek() != EOF)
		return true;
	return false;
};

bool empty_file_predicate(std::fstream& prison_file)
{
	if (prison_file.peek() == EOF)
		return true;
	return false;
};

void int_input_if_fail(int& val)
{
	std::cin.clear();
	std::cin.ignore(255, '\n');
	std::cout << "������ �����!";
};

void input_not_empty_file_if_fail(std::fstream& prison_file)
{
	std::cout << "���� � ����� ������ �� ���������� ��� �� �������� ������!";
	prison_file.close();
};

void input_empty_file_if_fail(std::fstream& prison_file)
{
	std::cout << "���� � ����� ������ ��� ���������� � �������� ������!";
	prison_file.close();
};



void fill_from_console(Prison* prison)
{
	print_villain_template();
	try
	{
		prison->add(std::cin);
		std::cin.clear();
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "������ ����������! " << exception.what() << '\n';
	}
}

void fill_from_file(Prison* prison)
{
	std::fstream prison_file = pick_and_check<std::fstream>("", file_name_input, not_empty_file_predicate, input_not_empty_file_if_fail);
	try
	{
		prison->add(prison_file);
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "������ ������ �����! " << exception.what() << '\n';
	}
	prison_file.close();
}



void add_to_prison(Prison* prison, Prison* wanted)
{
	size_t size = prison->size();
	std::string message = "�������� ������ ������ � ������� ������� >> 1\n�������� ������ ������ � ������� ����� >> 2\n�� ��������� ������ ������ � ��������� >> 0\n";
	int choice = pick_and_check<int>(message.c_str(), int_input, [](int& val) {return val >= 0 && val <= 2; }, int_input_if_fail);
	std::cin.ignore(255, '\n');
	switch (choice)
	{
	case 1:
		fill_from_console(prison);
		break;
	case 2:
		fill_from_file(prison);
		break;
	default:
		break;
	}
	if (prison->size() > size)
	{
		std::vector<Villain> removed = prison->selection([](Villain& villain) { return !villain.get_is_catched(); });
		if (!removed.empty())
		{
			std::for_each(removed.begin(), removed.end(), [](Villain& value) { value.set_is_catched(false); });
			wanted->add(removed.begin(), removed.end());
			std::vector<Villain> catched = prison->selection([](Villain& villain) { return villain.get_is_catched(); });
			prison->set(catched);
			std::cout << "��� ���������� ��������� ������� ������� �������!\n";
		}
	}
}



bool remove_from_prison(Prison* prison, Prison* wanted)
{
	size_t size = prison->size();
	if (size > 0)
	{
		std::string message = "������� [1-" + std::to_string(size) + "]-�� ������ �� ���������� >> [1-"
			+ std::to_string(size) + "]\n�� ������� ������� �� ���������� >> 0\n";
		int index = pick_and_check<int>(message.c_str(), int_input, [size](int& val) {return val >= 0 && val <= size; }, int_input_if_fail);
		std::cin.ignore(255, '\n');
		if (index > 0)
		{
			try
			{
				std::vector<Villain> removed{ prison->remove(index - 1) };
				std::cout << removed[0];
				std::cout << "\n������ ������ ������ �� ������.\n";
				removed[0].set_is_catched(false);
				wanted->add(removed.begin(), removed.end());
				return true;
			}
			catch (std::out_of_range)
			{
				std::cout << "����� �� ������� ����������! �������� ����������!\n";
			}
		}
	}
	else
		std::cout << "������ �� �������� �������!\n";
	return false;
}



void edit_prison(Prison* prison, Prison* wanted)
{
	size_t size = prison->size();
	if (size > 0)
	{
		std::string message = "�������� [1-" + std::to_string(size) + "]-�� ������ � ���������� � ������� ������� >> 1\n"
			+ "�������� [1-" + std::to_string(size) + "]-�� ������ � ���������� � ������� ����� >> 2\n"
			+ "�� �������� ������ ������� >> 0\n";
		int choice = pick_and_check<int>(message.c_str(), int_input, [](int& val) {return val >= 0 && val <= 2; }, int_input_if_fail);
		std::cin.ignore(255, '\n');
		if (choice == 0)
			return;
		message = "������� ����� ������, ������ �������� ������ �������� [1-"
			+ std::to_string(size) + "]";
		int index = pick_and_check<int>(message.c_str(), int_input, [size](int& val) {return val >= 1 && val <= size; }, int_input_if_fail, 3, 0);
		std::cin.ignore(255, '\n');
		if (index == 0)
			return;
		try
		{
			std::istream_iterator<Villain> reader;
			switch (choice)
			{
			case 1:
				print_villain_template();
				std::cout << "������� ����� ������ ������ �� ��������� �������:\n";
				reader = std::istream_iterator<Villain>(std::cin);
				break;
			case 2:
			{
				message = "������� �������� �����, � ������� ��������� ����� ������ ������\n";
				std::fstream prison_file = pick_and_check<std::fstream>(message.c_str(), file_name_input, not_empty_file_predicate, input_not_empty_file_if_fail);
				reader = std::istream_iterator<Villain>(prison_file);
				break;
			}
			default:
				return;
			}
			prison->edit(index - 1, *reader);
			std::cout << "������ " << index << "-�� ������ ���� ��������.\n";
			if (!prison->at(index - 1).get_is_catched())
			{
				std::vector<Villain> removed{ prison->remove(index - 1) };
				removed[0].set_is_catched(false);
				wanted->add(removed.begin(), removed.end());
				std::cout << "\n������ ������ �� ������.\n";
			}
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
		std::cout << "������ �� �������� �������!\n";
}



std::function<bool(Villain&)> get_nickname_selector()
{
	std::cout << "������� �� ��������.\n������� ����� ������� ���������, �� �������� ������ ������� �������\n>> ";
	std::string left;
	std::getline(std::cin, left);
	std::cout << "������� ������ ������� ���������, �� �������� ������ ������� �������\n>> ";
	std::string right;
	std::getline(std::cin, right);
	if (left > right)
	{
		std::cout << "������! ������ ������� �� ����� ���� ������ �����!";
		return NULL;
	}
	return [left, right](Villain& villain) { std::string nickname = villain.get_nickname(); return nickname.compare(left) > -1 && nickname.compare(right) < 1; };
}

std::function<bool(Villain&)> get_data_selector()
{
	tm left, right;
	std::cout << "dd mm yyyy (���� ����� ���)\n";
	std::cout << "hh mm ss (��� ������ �������)\n\n";
	int flag_of_out = 0;
	while (flag_of_out != -1)
	{
		try
		{
			std::cout << "������� ����� ������� ���������(���� � �����) ���������� ������������, ������������ �������, �� ��������� �������:\n";
			left = input_date(std::cin);
			std::cout << "������� ������ ������� ���������(���� � �����) ���������� ������������, ������������ �������, �� ��������� �������:\n";
			right = input_date(std::cin);
			flag_of_out = -1;
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "\n������! " << exception.what();
			flag_of_out++;
			if (flag_of_out == 3)
			{
				std::cout << "\n��������� ���������� ������� �����!\n";
				return NULL;
			}
			std::cout << " ��������� ����.\n";
		}
	}

	return [left, right](Villain& value) { return compare_date(value.get_date(), left) > -1 && compare_date(value.get_date(), right) < 1; };
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

void select_from_prison(Prison* prison)
{
	if (prison->size() > 0)
	{
		std::string message = "������� ������� �� ������ :\n�� �������� >> 1\n"
			"�� ���� ���������� ������������ >> 2\n�� ���� �������, ��� �������� ����������� >> 3\n��������� ������ � �������� >> 0\n";
		int choice = pick_and_check<int>(message.c_str(), int_input, [](int& val) {return val >= 0 && val <= 3; }, int_input_if_fail);
		std::cin.ignore(255, '\n');
		if (choice != 0)
		{
			std::vector<Villain> selected(prison->size());
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
			selected = prison->selection(selector);
			auto writer = std::ostream_iterator<Villain>(std::cout, "\n");
			copy(selected.begin(), selected.end(), writer);
			std::cout << '\n';
		}
	}
	else
		std::cout << "������ �� �������� �������!\n";
}



void release_last_from_prison(Prison* prison)
{
	if (prison->size() > 0)
	{
		std::cout << "��������� ������, ������� ��� ������� � ������ " << prison->get_name() << ":\n\n";
		std::cout << prison->get_last();
	}
	else
		std::cout << "������ �� �������� �������!\n";
}



void move_villain(Prison* prison_from, Prison* prison_to)
{
	size_t size = prison_from->size();
	if (size > 0)
	{
		std::string message = "������� ����� ������, �������� ������ ��������� � ������ ������ [1-"
			+ std::to_string(size) + "]";
		int index = pick_and_check<int>(message.c_str(), int_input, [size](int& val) {return val >= 1 && val <= size; }, int_input_if_fail, 3, 0);
		if (index == 0)
			return;
		std::vector<Villain> removed{ prison_from->remove(index - 1) };
		prison_to->add(removed.begin(), removed.end());
		std::cout << index << "-� ������ ��� ������� ��������� �� ������ " << prison_from->get_name() << " � ������ " << prison_to->get_name() << ".\n";
	}
	else
		std::cout << "������ �� �������� �������!\n";
}



void prison_menu(PrisonsMap& prisons, Prison* prison)
{
	int choice = 1;
	while (choice != 0)
	{
		std::string message = "���������� ����� ������� � ������ >> 1\n"
			"�������� ������� �� ������ >> 2\n��������� ������ ������ � ������ >> 3\n"
			"������� ������� �� ��������� �������� >> 4\n������ ���������� ������������ � ������ ������ >> 5\n"
			"������� ������� �� ����� ������ � ������ >> 6\n��������� ������ � ������� ������� >> 0\n";
		choice = pick_and_check<int>(message.c_str(), int_input, [](int& val) {return val >= 0 && val <= 6; }, int_input_if_fail);
		std::cin.ignore(255, '\n');
		std::cout << '\n';
		switch (choice)
		{
		case 1:
			add_to_prison(prison, prisons.at("Wanted"));
			break;
		case 2:
			remove_from_prison(prison, prisons.at("Wanted"));
			break;
		case 3:
			edit_prison(prison, prisons.at("Wanted"));
			break;
		case 4:
			select_from_prison(prison);
			break;
		case 5:
			release_last_from_prison(prison);
			break;
		case 6:
		{
			message = "������� �������� ������, ���� �� ������ ��������� ������������\n";
			auto input = [](std::string& val)
			{
				std::cout << ">> ";
				std::getline(std::cin, val);
				return true;
			};
			auto predicate = [&prisons, &prison](std::string& val) { return val != "Wanted" && val != prison->get_name() && prisons.find(val) != prisons.end(); };
			auto if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ �� ����������!"; };

			std::string prison_name = pick_and_check<std::string>(message.c_str(), input, predicate, if_fail, 3, "");
			std::cout << '\n';
			if (prison_name == "")
				break;
			move_villain(prison, prisons.at(prison_name));
		}
			break;
		default:
			break;
		}
		prisons.save();
		std::cout << '\n';
	}
}