#include "PrisonsActions.h"



//работа с тюрьмой
void print_villain_template()
{
	std::cout << "Nickname\n";
	std::cout << "Real_Name\n";
	std::cout << "Monster_Type (Vampire/Zombie/Ghost/Werwolf/Skeleton/EvilClown/NotSpecified)\n";
	std::cout << "dd mm yyyy (день месяц год)\n";
	std::cout << "hh mm ss (час минута секунда)\n";
	std::cout << "Is_Catched (Catched/Wanted)\n";
	std::cout << "\nВведите \"---\" чтобы закончить ввод\n";
	std::cout << "Введите данные новых злодеев по заданному шаблону:\n";
}



bool int_input(int& val)
{
	return bool(std::cout << ">> " && std::cin >> val);
};

bool file_name_input(std::fstream& prison_file)
{
	std::string file_name;
	std::cout << "Введите имя файла >> ";
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
	std::cout << "Ошибка ввода!";
};

void input_not_empty_file_if_fail(std::fstream& prison_file)
{
	std::cout << "Файл с таким именем не существует или не содержит данные!";
	prison_file.close();
};

void input_empty_file_if_fail(std::fstream& prison_file)
{
	std::cout << "Файл с таким именем уже существует и содержит данные!";
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
		std::cout << "Ошибка считывания! " << exception.what() << '\n';
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
		std::cout << "Ошибка чтения файла! " << exception.what() << '\n';
	}
	prison_file.close();
}



void add_to_prison(Prison* prison, Prison* wanted)
{
	size_t size = prison->size();
	std::string message = "Добавить нового злодея с помощью консоли >> 1\nДобавить нового злодея с помощью файла >> 2\nНе добавлять нового злодея в контейнер >> 0\n";
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
			std::cout << "При добавлении некоторым злодеям удалось сбежать!\n";
		}
	}
}



bool remove_from_prison(Prison* prison, Prison* wanted)
{
	size_t size = prison->size();
	if (size > 0)
	{
		std::string message = "Удалить [1-" + std::to_string(size) + "]-го злодея из контейнера >> [1-"
			+ std::to_string(size) + "]\nНе удалять злодеев из контейнера >> 0\n";
		int index = pick_and_check<int>(message.c_str(), int_input, [size](int& val) {return val >= 0 && val <= size; }, int_input_if_fail);
		std::cin.ignore(255, '\n');
		if (index > 0)
		{
			try
			{
				std::vector<Villain> removed{ prison->remove(index - 1) };
				std::cout << removed[0];
				std::cout << "\nДанный злодей сбежал из тюрьмы.\n";
				removed[0].set_is_catched(false);
				wanted->add(removed.begin(), removed.end());
				return true;
			}
			catch (std::out_of_range)
			{
				std::cout << "Выход за пределы контейнера! Удаление невозможно!\n";
			}
		}
	}
	else
		std::cout << "Тюрьма не содержит злодеев!\n";
	return false;
}



void edit_prison(Prison* prison, Prison* wanted)
{
	size_t size = prison->size();
	if (size > 0)
	{
		std::string message = "Изменить [1-" + std::to_string(size) + "]-го злодея в контейнере с помощью консоли >> 1\n"
			+ "Изменить [1-" + std::to_string(size) + "]-го злодея в контейнере с помощью файла >> 2\n"
			+ "Не изменять данные злодеев >> 0\n";
		int choice = pick_and_check<int>(message.c_str(), int_input, [](int& val) {return val >= 0 && val <= 2; }, int_input_if_fail);
		std::cin.ignore(255, '\n');
		if (choice == 0)
			return;
		message = "Введите номер злодея, данные которого хотите изменить [1-"
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
				std::cout << "Введите новые данные злодея по заданному шаблону:\n";
				reader = std::istream_iterator<Villain>(std::cin);
				break;
			case 2:
			{
				message = "Введите название файла, в котором находятся новые данные злодея\n";
				std::fstream prison_file = pick_and_check<std::fstream>(message.c_str(), file_name_input, not_empty_file_predicate, input_not_empty_file_if_fail);
				reader = std::istream_iterator<Villain>(prison_file);
				break;
			}
			default:
				return;
			}
			prison->edit(index - 1, *reader);
			std::cout << "Данные " << index << "-го злодея были изменены.\n";
			if (!prison->at(index - 1).get_is_catched())
			{
				std::vector<Villain> removed{ prison->remove(index - 1) };
				removed[0].set_is_catched(false);
				wanted->add(removed.begin(), removed.end());
				std::cout << "\nЗлодей сбежал из тюрьмы.\n";
			}
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
		std::cout << "Тюрьма не содержит злодеев!\n";
}



std::function<bool(Villain&)> get_nickname_selector()
{
	std::cout << "Выборка по прозвищу.\nВведите левую границу интервала, по которому хотите сделать выборку\n>> ";
	std::string left;
	std::getline(std::cin, left);
	std::cout << "Введите правую границу интервала, по которому хотите сделать выборку\n>> ";
	std::string right;
	std::getline(std::cin, right);
	if (left > right)
	{
		std::cout << "Ошибка! Правая граница не может быть меньше левой!";
		return NULL;
	}
	return [left, right](Villain& villain) { std::string nickname = villain.get_nickname(); return nickname.compare(left) > -1 && nickname.compare(right) < 1; };
}

std::function<bool(Villain&)> get_data_selector()
{
	tm left, right;
	std::cout << "dd mm yyyy (день месяц год)\n";
	std::cout << "hh mm ss (час минута секунда)\n\n";
	int flag_of_out = 0;
	while (flag_of_out != -1)
	{
		try
		{
			std::cout << "Введите левую границу интервала(дату и время) последнего преступления, совершенного злодеем, по заданному шаблону:\n";
			left = input_date(std::cin);
			std::cout << "Введите правую границу интервала(дату и время) последнего преступления, совершенного злодеем, по заданному шаблону:\n";
			right = input_date(std::cin);
			flag_of_out = -1;
		}
		catch (std::invalid_argument exception)
		{
			std::cout << "\nОшибка! " << exception.what();
			flag_of_out++;
			if (flag_of_out == 3)
			{
				std::cout << "\nПревышено количество попыток ввода!\n";
				return NULL;
			}
			std::cout << " Повторите ввод.\n";
		}
	}

	return [left, right](Villain& value) { return compare_date(value.get_date(), left) > -1 && compare_date(value.get_date(), right) < 1; };
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

void select_from_prison(Prison* prison)
{
	if (prison->size() > 0)
	{
		std::string message = "Выборка злодеев из тюрьмы :\nПо прозвищу >> 1\n"
			"По дате последнего преступления >> 2\nПо типу монстра, под которого маскируется >> 3\nЗакончить работу с выборкой >> 0\n";
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
		std::cout << "Тюрьма не содержит злодеев!\n";
}



void release_last_from_prison(Prison* prison)
{
	if (prison->size() > 0)
	{
		std::cout << "Последний злодей, который был посажен в тюрьму " << prison->get_name() << ":\n\n";
		std::cout << prison->get_last();
	}
	else
		std::cout << "Тюрьма не содержит злодеев!\n";
}



void move_villain(Prison* prison_from, Prison* prison_to)
{
	size_t size = prison_from->size();
	if (size > 0)
	{
		std::string message = "Введите номер злодея, которого хотите перевести в другую тюрьму [1-"
			+ std::to_string(size) + "]";
		int index = pick_and_check<int>(message.c_str(), int_input, [size](int& val) {return val >= 1 && val <= size; }, int_input_if_fail, 3, 0);
		if (index == 0)
			return;
		std::vector<Villain> removed{ prison_from->remove(index - 1) };
		prison_to->add(removed.begin(), removed.end());
		std::cout << index << "-й злодей был успешно переведен из тюрьмы " << prison_from->get_name() << " в тюрьму " << prison_to->get_name() << ".\n";
	}
	else
		std::cout << "Тюрьма не содержит злодеев!\n";
}



void prison_menu(PrisonsMap& prisons, Prison* prison)
{
	int choice = 1;
	while (choice != 0)
	{
		std::string message = "Добавление новых злодеев в тюрьму >> 1\n"
			"Удаление злодеев из тюрьмы >> 2\nИзменение данных злодев в тюрьме >> 3\n"
			"Выборка злодеев по заданному критерию >> 4\nПечать последнего добавленного в тюрьму злодея >> 5\n"
			"Перевод злодеев из одной тюрьмы в другую >> 6\nЗакончить работу с текущей тюрьмой >> 0\n";
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
			message = "Введите название тюрьмы, куда вы хотите перевести заключенного\n";
			auto input = [](std::string& val)
			{
				std::cout << ">> ";
				std::getline(std::cin, val);
				return true;
			};
			auto predicate = [&prisons, &prison](std::string& val) { return val != "Wanted" && val != prison->get_name() && prisons.find(val) != prisons.end(); };
			auto if_fail = [](std::string& val) { std::cout << "Ошибка ввода! Такой тюрьмы не существует!"; };

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