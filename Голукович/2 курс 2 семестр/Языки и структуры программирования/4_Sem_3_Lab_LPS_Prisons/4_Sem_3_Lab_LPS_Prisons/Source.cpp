//	��������� ������� ���������, 2 ���� 9 ������, ������ 6

//	������ ������ ������ ������ � ������. ��� ���������� ������������� ������� �� ������� ����� ������� ���������� -
//	����� �������� �������, ������� ��������� ��������� ������� ������������ � ���� �����.
// 
//	������ ������ ��������������� ��������� � ������� �����������.
// 
//	������ ����� ���������, ������� � ��������.����� ��������� �������� ������ ������� : ���������, ������� (������ ����������� �� �������)
//	� ������������� ����������� � ��� �������, � ����� ������������� ������ ������� �� ���� ��� ����� ��������(��.������ 2)
//	� ����� ����������� ����������� ����������� � ������ �����.
// 
//	������, ����� ������� �� - �������� ��������� �� �������. ����� �� ���������� (������ ��������).
// 
//	��������� ����� ���������� ������� ������.
// 
//	��� ����� ������ ���������� �� ������ ���� ��������� � �������� �������� ��� �������������� ���.
// 
//	���� ������� �����, ������ �������� � ������ (������������ ������������ ����������� ������ ��������� �� ������).
// 
//	������ �������, �������� �������� ������� ��������� ������������� ���������� : ����� ����������� � ������ ������,
//	����� ����� �����, ����� ����� �����������, ������� ����� �����������.


#include "program_files\PrisonsActions.h"
#include "program_files\Entered.h"

auto console_int_input = [](int& val) {	return bool(std::cout << ">> " && std::cin >> val && std::cin.ignore(255, '\n')); };
auto console_int_input_if_fail = [](int&)
{
	std::cout << "������ �����!";
	std::cin.clear();
	std::cin.ignore(255, '\n');
};

void main_menu(PrisonsMap& prisons, Entered& last_entered);

void print_prisons(PrisonsMap& prisons, Entered& last_entered);

void add_prison(PrisonsMap& prisons, Entered& last_entered);

void edit_prison_name(PrisonsMap& prisons, Entered& last_entered);

void remove_prison(PrisonsMap& prisons, Entered& last_entered);

void work_with_prison(PrisonsMap& prisons, Entered& last_entered);

void check_stats(PrisonsMap& prisons, Entered& last_entered);
void prisoners_count(PrisonsMap& prisons);
size_t all_prisoners_count(PrisonsMap& prisons);
size_t prisons_count(PrisonsMap& prisons);
size_t avg_prisoners_count(PrisonsMap& prisons);
size_t wanted_count(PrisonsMap& prisons);

void try_catch_villain(PrisonsMap& prisons, Entered& last_entered);



int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	PrisonsMap prisons("_prisons.txt");
	std::cout << '\n';
	Entered last_entered("_entered_int", "_entered_string"); //��������� �� ������ ����������
	main_menu(prisons, last_entered);

	return 0;
}



void main_menu(PrisonsMap& prisons, Entered& last_entered)
{
	std::string message = "������ ����������� � ������� >> 1\n�������� ������ >> 2\n���������� �������� ������ >> 3\n"
		"������� ������ >> 4\n���������� ���������� ������� >> 5\n�������� ���������� �� ������� >> 6\n����������� ������� ������ >> 7\n"
		"��������� ������ � �������� >> 0\n";
	auto predicate = [](int& val) {	return val >= 0 && val <= 7; };

	int choice = 1;
	while (choice != 0)
	{
		if (last_entered.front(choice))
			std::cout << message << ">> " << choice << '\n';
		else
		{
			choice = pick_and_check<int>(message.c_str(), console_int_input, predicate, console_int_input_if_fail);
			last_entered.push_back(choice);
		}
		std::cout << '\n';

		switch (choice)
		{
		case 1:
			print_prisons(prisons, last_entered);
			break;
		case 2:
			add_prison(prisons, last_entered);
			break;
		case 3:
			edit_prison_name(prisons, last_entered);
			break;
		case 4:
			remove_prison(prisons, last_entered);
			break;
		case 5:
			work_with_prison(prisons, last_entered);
			break;
		case 6:
			check_stats(prisons, last_entered);
			break;
		case 7:
			try_catch_villain(prisons, last_entered);
			break;
		default:
			break;
		}
		std::cout << "\n\n";
		if (!last_entered.empty())
			last_entered.clear();
	}
}



void print_prisons(PrisonsMap& prisons, Entered& last_entered)
{
	std::string message = "����������� ����������� �� ���� ������� >> 1\n����������� ����������� ���������� ������ >> 2\n��������� ������ � ������� >> 0\n";
	int choice;
	if (last_entered.front(choice))
		std::cout << message << ">> " << choice << '\n';
	else
	{
		auto predicate = [](int& val) { return val >= 0 && val <= 2; };
		choice = pick_and_check<int>(message.c_str(), console_int_input, predicate, console_int_input_if_fail);
		last_entered.push_back(choice);
	}
	switch (choice)
	{
	case 1:
	{
		auto func = [](std::pair<const std::string, Prison*>& pair) { std::cout << "\n"; pair.second->print(std::cout, "\n", true); std::cout << "\n"; };
		std::for_each(prisons.begin(), prisons.end(), func);
	}
		break;
	case 2:
	{
		message = "������� �������� ������, ����������� ������� ������ �����������\n";
		std::string prison_name;
		if (last_entered.front(prison_name))
			std::cout << message << ">> " << prison_name << '\n';
		else
		{
			auto input = [](std::string& val)
			{
				std::cout << ">> ";
				std::getline(std::cin, val);
				return true;
			};
			auto predicate = [&prisons](std::string& val) { return prisons.find(val) != prisons.end(); };
			auto if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ �� ����������!"; };

			prison_name = pick_and_check<std::string>(message.c_str(), input, predicate, if_fail, 3, "");
			last_entered.push_back(prison_name);
		}
		
		if (prison_name == "")
			return;

		if (prisons.find(prison_name) != prisons.end())
			prisons.at(prison_name)->print(std::cout, "\n", true);
	}
		break;
	default:
		break;
	}
}



void add_prison(PrisonsMap& prisons, Entered& last_entered)
{
	std::string message = "������� �������� ������, �������� ������� ������ ��������\n";
	std::string prison_name;
	if (last_entered.front(prison_name))
		std::cout << message << ">> " << prison_name << '\n';
	else
	{
		auto input = [](std::string& val)
		{
			std::cout << ">> ";
			std::getline(std::cin, val);
			return true;
		};
		auto predicate = [&prisons](std::string& val) { return prisons.find(val) == prisons.end(); };
		auto if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ ��� ����������! ��������� ����.\n"; };

		prison_name = pick_and_check<std::string>(message.c_str(), input, predicate, if_fail, 3, "");
		last_entered.push_back(prison_name);
	}
	if (prison_name == "")
		return;

	prisons.insert(prison_name, new Prison(prison_name, new std::fstream(prison_name, std::ios::in | std::ios::out | std::ios::trunc)));

	prisons.save();
	std::cout << "����� ������ " << prison_name << " ������� ���������!\n";
}



void edit_prison_name(PrisonsMap& prisons, Entered& last_entered)
{
	auto input = [](std::string& val)
	{
		std::cout << ">> ";
		std::getline(std::cin, val);
		return true;
	};

	std::string message = "������� �������� ������, �������� ������� ������ ��������\n";
	std::string prison_name;
	if (last_entered.front(prison_name))
		std::cout << message << ">> " << prison_name << '\n';
	else
	{
		auto first_predicate = [&prisons](std::string& val) { return prisons.find(val) != prisons.end(); };
		auto first_if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ �� ����������! ��������� ����.\n"; };

		prison_name = pick_and_check<std::string>(message.c_str(), input, first_predicate, first_if_fail, 3, "");
		last_entered.push_back(prison_name);
	}
	if (prison_name == "")
		return;

	message = "������� ����� �������� ������\n";
	std::string new_prison_name;
	if (last_entered.front(prison_name))
		std::cout << message << ">> " << prison_name << '\n';
	else
	{
		auto second_predicate = [&prisons](std::string& val) { return prisons.find(val) == prisons.end(); };
		auto second_if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ ��� ����������! ��������� ����.\n"; };

		new_prison_name = pick_and_check<std::string>(message.c_str(), input, second_predicate, second_if_fail, 3, "");
		last_entered.push_back(new_prison_name);
	}
	if (new_prison_name == "")
		return;

	prisons.insert(new_prison_name, prisons.at(prison_name));
	prisons.erase(prison_name);

	prisons.at(new_prison_name)->rename(new_prison_name);

	prisons.save();
	std::cout << "�������� ������ " << prison_name << " ������� �������� �� " << new_prison_name << ".\n";
}



void remove_prison(PrisonsMap& prisons, Entered& last_entered)
{
	std::string message = "������� �������� ������, �������� ������� ������ �������\n";
	std::string prison_name;
	if (last_entered.front(prison_name))
		std::cout << message << ">> " << prison_name << '\n';
	else
	{
		auto input = [](std::string& val)
		{
			std::cout << ">> ";
			std::getline(std::cin, val);
			return true;
		};
		auto predicate = [&prisons](std::string& val) { return val != "Wanted" && prisons.find(val) != prisons.end(); };
		auto if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ �� ����������! ��������� ����.\n"; };

		prison_name = pick_and_check<std::string>(message.c_str(), input, predicate, if_fail, 3, "");
		last_entered.push_back(prison_name);
	}
	if (prison_name == "")
		return;

	std::vector<Villain> wanted = prisons.at(prison_name)->clear();
	std::for_each(wanted.begin(), wanted.end(), [](Villain& villain) { villain.set_is_catched(false); });

	prisons.at("Wanted")->add(wanted.begin(), wanted.end());

	delete prisons.at(prison_name);
	prisons.erase(prison_name);

	prisons.save();
	std::cout << "\n������ " << prison_name << " ������� �������!\n��� ������ ������� �� ���!\n";
}



void work_with_prison(PrisonsMap& prisons, Entered& last_entered)
{
	std::string message = "������� �������� ������, � ������� ������ ��������\n";
	std::string prison_name;
	if (last_entered.front(prison_name))
		std::cout << message << ">> " << prison_name << '\n';
	else
	{
		auto input = [](std::string& val)
		{
			std::cout << ">> ";
			std::getline(std::cin, val);
			return true;
	
		};
		auto predicate = [&prisons](std::string& val) { return val != "Wanted" && prisons.find(val) != prisons.end(); };
		auto if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ �� ����������! ��������� ����.\n"; };

		prison_name = pick_and_check<std::string>(message.c_str(), input, predicate, if_fail, 3, "");
		last_entered.push_back(prison_name);
	}
	if (prison_name == "")
		return;
	std::cout << '\n';
	prison_menu(prisons, prisons.at(prison_name));
}



void check_stats(PrisonsMap& prisons, Entered& last_entered)
{
	std::string message = "�������� ����� ����� ����������� ��� ������ ������ >> 1\n�������� ����� ����� ����������� >> 2\n�������� ����� ����� ����� >> 3\n�������� ������� ����� ����������� >> 4\n�������� ���������� ������������� ������� >> 5\n�� �������� ���������� �� ������� >> 0\n";
	int choice = 1;
	while (choice != 0)
	{
		if (last_entered.front(choice))
			std::cout << message << ">> " << choice << '\n';
		else
		{
			auto predicate = [](int& val) {	return val >= 0 && val <= 5; };
			choice = pick_and_check<int>(message.c_str(), console_int_input, predicate, console_int_input_if_fail);
			last_entered.push_back(choice);
		}
		std::cout << '\n';
		switch (choice)
		{
		case 1:
			std::cout << "����� ����� ����������� ��� ������ ������:\n";
			prisoners_count(prisons);
			break;
		case 2:
			std::cout << "����� ����� �����������: " << all_prisoners_count(prisons) << '\n';
			break;
		case 3:
			std::cout << "����� ����� �����: " << prisons_count(prisons) << '\n';
			break;
		case 4:
			std::cout << "������� ����� �����������: " << avg_prisoners_count(prisons) << '\n';
			break;
		case 5:
			std::cout << "���������� ������������� ������� : " << wanted_count(prisons) << '\n';
			break;
		default:
			break;
		}
		std::cout << '\n';
	}
}

void prisoners_count(PrisonsMap& prisons)
{
	for (std::pair<const std::string, Prison*>& pair : prisons)
		if (pair.first != "Wanted")
			std::cout << pair.first << ": " << pair.second->size() << '\n';
}

size_t all_prisoners_count(PrisonsMap& prisons)
{
	size_t result = 0;
	for (std::pair<const std::string, Prison*>& pair : prisons)
		if (pair.first != "Wanted")
			result += pair.second->size();
	return result;
}

size_t prisons_count(PrisonsMap& prisons)
{
	size_t result = 0;
	for (std::pair<const std::string, Prison*>& pair : prisons)
		if (pair.first != "Wanted")
			result++;
	return result;
}

size_t avg_prisoners_count(PrisonsMap& prisons)
{
	int count = prisons_count(prisons);
	return count > 0 ?  all_prisoners_count(prisons) / prisons_count(prisons) : count;
}

size_t wanted_count(PrisonsMap& prisons)
{
	return prisons.at("Wanted")->size();
}



void try_catch_villain(PrisonsMap& prisons, Entered& last_entered)
{
	prisons.at("Wanted")->print(std::cout, "\n", true);

	std::string message = "\n������� ����� ������ (�� ������ �������������), �������� ������ ����������� �������\n";

	int index;
	if (last_entered.front(index))
		std::cout << message << ">> " << index << '\n';
	else
	{
		index = pick_and_check<int>(message.c_str(), console_int_input, [&prisons](int& value) { return value > 0 && value <= prisons.at("Wanted")->size(); }, console_int_input_if_fail, 3, 0);
		last_entered.push_back(index);
	}
		
	if (index > 0)
	{
		index -= 1;
		auto input = [](std::string& val)
		{
			std::cout << ">> ";
			std::getline(std::cin, val);
			return true;
		};
		message = "������� �������������� ��� ������, �������� ������ �������\n";
		std::string villain_name;
		if (last_entered.front(villain_name))
			std::cout << message << ">> " << villain_name << '\n';
		else
		{
			villain_name = pick_and_check<std::string>(message.c_str(), input, [](std::string& val) { return true; }, [](std::string& val) {});
			last_entered.push_back(villain_name);
		}
		try
		{
			std::vector<Villain> removed{ prisons.at("Wanted")->remove(index) };
			if (removed[0].get_name() == villain_name)
			{
				std::cout << "��� ������� ������� ������.\n";
				message = "������� �������� ������, ���� ������ ��������� ���������� ������\n";
				std::string prison_name;
				if (last_entered.front(prison_name))
					std::cout << message << ">> " << index << '\n';
				else
				{
					auto predicate = [&prisons](std::string& val) { return val != "Wanted" && prisons.find(val) != prisons.end(); };
					auto if_fail = [](std::string& val) { std::cout << "������ �����! ����� ������ �� ����������! ��������� ����.\n"; };

					prison_name = pick_and_check<std::string>(message.c_str(), input, predicate, if_fail, 3, "");
					last_entered.push_back(prison_name);
				}
				if (prison_name == "")
				{
					prisons.at("Wanted")->add(removed.begin(), removed.end());
					std::cout << "�������! ������ ��� ������, �� �������� ������� ����� � ����� ������!\n";
					return;
				}
				
				removed[0].set_is_catched(true);
				prisons.at(prison_name)->add(removed.begin(), removed.end());
				std::cout << "�����! ������ ��� ������ � ������� � ������ " << prison_name << "!\n";
			}
			else
			{
				prisons.at("Wanted")->add(removed.begin(), removed.end());
				std::cout << "�������! ������� ������ �� �������!\n";
			}

			prisons.save();
		}
		catch (std::out_of_range exception)
		{
			std::cout << exception.what() << "\n";
		}
	}
}