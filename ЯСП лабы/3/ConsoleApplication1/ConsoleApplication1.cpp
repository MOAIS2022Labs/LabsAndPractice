//Гаршин Максим Сергеевич
/*
10. Реализовать шаблон класса вектор Vector<X>, последовательно хранящий элементы
	произвольного типа.Класс должен содержать методы, перечисленные в варианте 1.

Инициализация списка из файла;
Добавление элемента в начало списка;
Добавление элемента в конец списка;
Показ всех элементов списка;
Сохранение в файл.

A:
Определение количества элементов списка;
Удаление элемента списка по номеру(индексу);
Удаление первого элемента;
Удаление последнего элемента;
Удаление всех элементов списка с заданным значением;
Сортировка элементов списка.
*/

#include "Vector.h"

template<class X>
void check_value(Vector<X> &vector, X &elem);
int selection_type(); //функция выбора одного из предложенных типов данных, которые будут хранится в векторе
int main_menu(); //меню выбора действий, которые могут быть осуществимы над вектором
template<class X>
void check_name_file(std::string& file); //проверка имени файла на корректность
std::string name_file(); //ввести имя файла, который требуется открыть
void type(int choice); //создания вектора заданного типа и вызова task
template<class X>
void task(Vector<X>& vector, int type_of_vector); //основная часть программы, где осуществляется выполнение всех доступных действий
bool check_file(std::string file_name, int choice);
bool to_number(std::string str);

int main()
{
	SetConsoleOutputCP(1251);
	
	type(selection_type());
}

template<class X>
bool is_positive(X elem)
{
	return elem >= 0;
}

bool to_number(std::string str)
{
	int num;
	std::stringstream ss(str);

	ss >> num;
	return !ss.fail();
}

bool check_file(std::string file_name, int choice)
{
	bool flag = true;
	std::ifstream file(file_name);

	switch (choice)
	{
	case 1:
	{
		std::string line;

		while (std::getline(file, line) && flag)
		{
			std::stringstream ss(line); // создаем поток для преобразования строки в число
			std::string word;
			while (ss >> word && flag)
			{
				if (!to_number(word) || (word.find(".") != std::string::npos))
					flag = false;
			}
		}
		break;
	}
	case 2:
	{
		flag = true;
		break;
	}
	case 3:
	{
		std::string line;

		while (getline(file, line) && flag)
		{
			std::stringstream ss(line);
			std::string word;

			while (ss >> word && flag)
			{
				if (!to_number(word) || (to_number(word) && std::atoi(word.c_str()) <= 0))
					flag = false;
			}
		}
		break;
	}
	}
	file.close();
	return flag;
}

template<class X>
void check_value(Vector<X> &vector, X &elem)
{
	// если int
	if (!std::strcmp(typeid(vector.get_type()).name(), "int"))
	{
		std::cout << "Введите целое число: ";
		bool flag = false;
		while (!flag)
		{
			std::cin >> elem;
			if (std::cin.fail() || std::cin.peek() != '\n') //проверяем что пользователь вводит числа типа int
			{
				std::cout << "Ошибка! Введите число типа int.\n";
				std::cin.clear();
				std::cin.ignore(255, '\n');
			}
			else
				flag = true;
		}
	}
	// если string
	else if (!std::strcmp(typeid(vector.get_type()).name(), "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >"))
	{
		std::string str;
		bool flag = true;
		
		while (flag)
		{
			std::cout << "Введите строку: ";
			std::cin.ignore();
			std::getline(std::cin, str);
			int count = 0;
			for (int i = 0; i < str.length() && flag; ++i)
			{
				if (str[i] == ' ') //если в введённой строке есть пробелы, то запрашиваем повторный ввод
					++count;
			}
			if (count)
			{
				std::cin.clear();
				std::cout << "Ошибка ввода!\n";
			}
			else
				flag = false;
		}
		std::stringstream ss(str);
		ss >> elem;
	}
	// если struct
	else if (!std::strcmp(typeid(vector.get_type()).name(), "struct Point"))
	{
		std::cout << "Введите координаты x, y, z: ";
		while ( !(std::cin >> elem) ) // проверяем что пользователь вводит числа типа double
		{
			std::cout << "Ошибка ввода!\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	}
}

// выбора типа вектора
int selection_type()
{
	int choice;

	std::cout << "Выберите тип данных:\n";
	std::cout << "1. Целочисленный\n";
	std::cout << "2. Строковый\n";
	std::cout << "3. Структура\n";

	bool flag = false;
	while (!flag)
	{
		std::cin >> choice;
		if (std::cin.fail() || std::cin.peek() != '\n' || choice<1 || choice>3) // проверяем что пользователь вводит числа типа int от 1 до 3
		{
			std::cout << "Ошибка! Введите число типа int от 1 до 3:\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
		else
			flag = true;
	}
	return choice;
}

int main_menu()
{
	int choice;
	std::cout << "\nВозможные операции:\n";
	std::cout << "0. Завершение программы\n";
	std::cout << "1. Инициализация массива из файла\n";
	std::cout << "2. Определение количества элементов массива\n";
	std::cout << "3. Добавление элемента в начало массива\n";
	std::cout << "4. Добавление элемента в конец массива\n";
	std::cout << "5. Удаление первого элемента\n";
	std::cout << "6. Удаление последнего элемента\n";
	std::cout << "7. Удаление элемента массива по номеру (индексу)\n";
	std::cout << "8. Удаление всех элементов массива с заданным значением\n";
	std::cout << "9. Показ всех элементов массива\n";
	std::cout << "10. Сохранение в файл\n";
	std::cout << "11. Сортировка элементов массива\n->";
	bool flag = false;
	while (!flag)
	{
		std::cin >> choice;
		if (std::cin.fail() || std::cin.peek() != '\n' || choice < 0 || choice > 11) // проверяем что пользователь вводит числа типа int от 1 до 11
		{
			std::cout << "Ошибка! Введите число типа int от 0 до 11:\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
		else
			flag = true;
	}
	return choice;
}

void type(int choice)
{
	switch (choice)
	{
	case 1: //int
	{
		Vector<int> vector;
		task(vector, choice);
		break;
	}
	case 2: //string
	{
		Vector<std::string> vector;
		task(vector, choice);
		break;
	}
	case 3: //HumanParameters
	{
		Vector<Point> vector;
		task(vector, choice);
		break;
	}
	}
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
	std::cout << "Введите путь к файлу:\n";
	std::string file_name;
	std::cin.ignore();
	std::getline(std::cin, file_name);
	check_name_file(file_name);
	return file_name;
}

template<class X>
void task(Vector<X>& vector, int type_of_vector)
{
	int choice{};
	do
	{
		choice = main_menu();
		switch (choice)
		{
		case 1:
		{
			std::string file_name = name_file();
			std::ifstream file(file_name);
		
			if (check_file(file_name, type_of_vector))
			{
				if (vector.get_size())
					vector.clear();
				vector.init_from_file(file);
				std::cout << "Вектор успешно заполнен!\n";
			}
			else
				std::cout << "В файле не тот тип данных!\n";
			break;
		}
		case 2:
		{
			std::cout << "Количество элементов в массиве: " << vector.get_size() << '\n';
			break;
		}
		case 3:
		{
			X elem{};
			check_value(vector, elem);
			
			vector.push_front(elem);
			break;
		}
		case 4:
		{
			X elem{};
			check_value(vector, elem);
			
			vector.push_back(elem);
			break;
		}
		case 5:
		{
			vector.remove_first();
			break;
		}
		case 6:
		{
			vector.remove_last();
			break;
		}
		case 7:
		{
			int index;
			std::cout << "Введите позицию:\n";
			std::cin >> index;
			vector.remove_at(index);
			break;
		}
		case 8:
		{
			X value{};
			check_value(vector, value);
			vector.remove_all_with_value(value);
			break;
		}
		case 9:
		{
			std::cout << "\nПечать всех элементов:\n";
			if (type_of_vector == 3)
				vector.print(std::cout, '\n');
			else
				vector.print(std::cout, ' ');
			break;
		}
		case 10:
		{
			std::string file_name = name_file();
			std::ofstream file(file_name);
			if (type_of_vector == 3)
				vector.print(std::cout, '\n');
			else
				vector.print(std::cout, ' ');
			break;
		}
		case 11:
		{
			vector.sort();
			break;
		}
		}
	} while (choice);
};