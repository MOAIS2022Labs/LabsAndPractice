//#include "Container.h"
//#include "Villain.h"
//#include <windows.h>
//#include <map>
//#include <set>
//
//using Pair = std::pair<Container<Villain>, std::fstream>;
//
//bool is_edited = false;
//
//template <typename T>
//T pick_and_check_updated(const char* message, std::function<bool(T&)> task, std::function<bool(T&)> predicate, std::function<void(T&)> if_fail = []() {}, int max = -1, T bad_val = T())
//{
//	std::cout << message;
//	T result;
//	bool flag_of_out = false;
//	while (!flag_of_out && max != 0)
//	{
//		if (task(result) && predicate(result))
//			flag_of_out = true;
//		else
//		{
//			max--;
//			if_fail(result);
//			if (max == 0)
//			{
//				std::cout << "Превышено количество попыток ввода!\n";
//				return bad_val;
//			}
//		}
//	}
//	return result;
//}
//
//auto console_int_input = [](int& val) {	return bool(std::cout << ">> " && std::cin >> val); };
//
//auto console_int_input_if_fail = [](int&)
//{
//	std::cout << "Ошибка ввода! Повторите ввод!\n";
//	std::cin.clear();
//	std::cin.ignore(255, '\n');
//};
//
//void start(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//void save(Pair& prison);
//void save(std::string prison_name, std::map<std::string, Pair>& prisons);
//
//void save_all(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons);
//
//void main_menu(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//void print_prisons(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//void add_prison(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//void edit_prison_name(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//void remove_prison(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//void work_with_prison(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//void check_stats(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered);
//
//int main_2()
//{
//	SetConsoleOutputCP(1251);
//	std::set<std::string> prisons_names;
//	std::map<std::string, Pair> prisons;
//	std::vector<int> last_entered; //заготовка на полное сохранение
//	start(prisons_names, prisons, last_entered);
//	main_menu(prisons_names, prisons, last_entered);
//	return 0;
//}
//
//void start(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
//{
//	std::ifstream prisons_file("_prisons.txt");
//	std::string prison_name;
//	while (prisons_file && !prisons_file.eof())
//	{
//		std::getline(prisons_file, prison_name);
//		prisons_names.insert(prison_name);
//		prisons[prison_name] = Pair(Container<Villain>(), std::fstream(prison_name, std::ios::in | std::ios::out));
//		std::istream_iterator<Villain> reader(prisons[prison_name].second);
//		prisons[prison_name].first.read(reader);
//		prisons[prison_name].second.seekg(0);
//	}
//	prisons_file.close();
//}
//
//void save(Pair& prison)
//{
//	Container<Villain> container = prison.first;
//	std::ostream_iterator<Villain> writer(prison.second);
//	prison.first.write(writer);
//	prison.second.seekg(0);
//}
//void save(std::string prison_name, std::map<std::string, Pair>& prisons)
//{
//	Container<Villain> container = prisons[prison_name].first;
//	std::ostream_iterator<Villain> writer(prisons[prison_name].second);
//	prisons[prison_name].first.write(writer);
//	prisons[prison_name].second.seekg(0);
//}
//
//void save_all(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons)
//{
//	std::ofstream prisons_file("_prisons.txt");
//	for (auto prison_name : prisons_names)
//	{
//		prisons_file << prison_name << std::endl;
//		save(prison_name, prisons);
//	}
//	prisons_file.close();
//}
//
//void main_menu(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
//{
//	std::string message = "";
//	auto predicate = [](int& val) {	return val >= 0 && val <= 6; };
//
//
//	int choice = 1;
//	while (choice != 0)
//	{
//		choice = pick_and_check_updated<int>(message.c_str(), console_int_input, predicate, console_int_input_if_fail);
//		switch (choice)
//		{
//		case 1:
//			print_prisons(prisons_names, prisons, last_entered);
//			break;
//		case 2:
//			add_prison(prisons_names, prisons, last_entered);
//			break;
//		case 3:
//			edit_prison_name(prisons_names, prisons, last_entered);
//			break;
//		case 4:
//			remove_prison(prisons_names, prisons, last_entered);
//			break;
//		case 5:
//			work_with_prison(prisons_names, prisons, last_entered);
//			break;
//		case 6:
//			check_stats(prisons_names, prisons, last_entered);
//			break;
//		default:
//			save_all(prisons_names, prisons);
//			break;
//		}
//	}
//}
//
//void print_prisons(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
//{
//	std::string message = "";
//	auto predicate = [](int& val) { return val >= 0 && val <= 2; };
//	int choice = pick_and_check_updated<int>(message.c_str(), console_int_input, predicate, console_int_input_if_fail);
//	switch (choice)
//	{
//	case 1:
//	{
//		for (auto prison_name : prisons_names)
//		{
//			std::cout << "Название тюрьмы: " << prison_name << "\n\n";
//			auto writer = std::ostream_iterator<Villain>(std::cout, "\n");
//			prisons[prison_name].first.write(writer);
//		}
//	}
//		break;
//	case 2:
//	{
//		auto input = [](std::string& val)
//		{
//			std::cout << ">> ";
//			std::getline(std::cin, val);
//			return true;
//		};
//		auto predicate = [&prisons](std::string& val) { return prisons.find(val) != prisons.end(); };
//		auto if_fail = [](std::string& val) { std::cout << "Ошибка ввода! Такой тюрьмы не существует! Повторите ввод.\n"; };
//
//		std::string prison_name = pick_and_check_updated<std::string>(message.c_str(), input, predicate, if_fail, 3, "!error!");
//		if (prison_name == "!error!" && prisons.find(prison_name) != prisons.end())
//			return;
//		std::cout << "Название тюрьмы: " << prison_name << "\n\n";
//		auto writer = std::ostream_iterator<Villain>(std::cout, "\n");
//		prisons[prison_name].first.write(writer);
//	}
//		break;
//	default:
//		break;
//	}
//}
//
////void add_prison(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
////{
////
////}
//
//void edit_prison_name(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
//{
//	std::string message = "Введите название тюрьмы, название которой хотите изменить:";
//	auto input = [](std::string& val)
//	{
//		std::cout << ">> ";
//		std::getline(std::cin, val);
//		return true;
//	};
//	auto first_predicate = [&prisons](std::string& val) { return prisons.find(val) != prisons.end(); };
//	auto first_if_fail = [](std::string& val) { std::cout << "Ошибка ввода! Такой тюрьмы не существует! Повторите ввод.\n"; };
//
//	std::string prison_name = pick_and_check_updated<std::string>(message.c_str(), input, first_predicate, first_if_fail, 3, "!error!");
//	if (prison_name == "!error!" && prisons.find(prison_name) == prisons.end())
//		return;
//
//	message = "Введите название новой тюрьмы";
//	auto second_predicate = [&prisons](std::string& val) { return prisons.find(val) == prisons.end(); };
//	auto second_if_fail = [](std::string& val) { std::cout << "Ошибка ввода! Такая тюрьма уже существует! Повторите ввод.\n"; };
//	std::string new_prison_name = pick_and_check_updated<std::string>(message.c_str(), input, second_predicate, first_if_fail, 3, "!error!");
//	if (new_prison_name == "!error!" && prisons.find(new_prison_name) != prisons.end())
//		return;
//
//	prisons[new_prison_name].first = prisons[prison_name].first;
//	//prisons[new_prison_name].second = std::fstream(prisons[prison_name].second, std::ios::in | std::ios::out);
//
//	std::cout << "Название тюрьмы успешно изменено!\n";
//}
//
////void remove_prison(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
////{
////
////}
//
////void work_with_prison(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
////{
////
////}
//
////void check_stats(std::set<std::string>& prisons_names, std::map<std::string, Pair>& prisons, std::vector<int>& last_entered)
////{
////
////}