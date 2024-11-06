#include "Arthropod.h"




Arthropod::Arthropod(const Arthropod& other)
{
	this->type = other.get_type();
	this->date = other.get_date();
	this->class_animal = other.get_class_animal();
	this->num_limbs = other.get_num_limbs();
	this->num_wings = other.get_num_wings();
	this->max_length = other.get_max_length();
	this->max_weight = other.get_max_weight();
}


std::string Arthropod::get_type() const
{
	return type;
}

void Arthropod::set_type(const std::string& new_type)
{
	type = new_type;
}

time_t Arthropod::get_date() const
{
	return date;
}

void Arthropod::set_date(const time_t& new_date)
{
	date = new_date;
}

Class_type Arthropod::get_class_animal() const
{
	return class_animal;
}

std::string Arthropod::get_class_animal_string() const
{
	std::string animal_class = "";
	switch (class_animal)
	{
	case Насекомое:
		animal_class = "Насекомое";
		break;
	case Ракообразное:
		animal_class = "Ракообразное";
		break;
	case Паукообразное:
		animal_class = "Паукообразное";
		break;
	case Многоножка:
		animal_class = "Многоножка";
		break;
	}
	return animal_class;
}

bool Arthropod::set_class_animal(std::string new_class_animal)
{
	return (new_class_animal == "Насекомое" && (class_animal = Насекомое))
		||(new_class_animal == "Ракообразное" && (class_animal = Ракообразное))
		||(new_class_animal == "Паукообразное" && (class_animal = Паукообразное))
		||(new_class_animal == "Многоножка" && (class_animal = Многоножка));
}

void Arthropod::set_class_animal()
{
	std::string new_class_animal;
	bool correct;
	do {
		correct = true;
		std::cin >> new_class_animal;
		if (!set_class_animal(new_class_animal)) {
			correct = false;
			std::cout << "Ошибка. Попробуйте снова.\n --> ";
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}

	} while (!correct);
}

int Arthropod::get_num_limbs() const
{
	return num_limbs;
}

void Arthropod::set_num_limbs(int new_num_limbs)
{
	if (new_num_limbs < 0) { throw std::invalid_argument("Должен быть не отрицательным"); }
	num_limbs = new_num_limbs;
}

int Arthropod::get_num_wings() const
{
	return num_wings;
}

void Arthropod::set_num_wings(int new_num_wings)
{
	if (new_num_wings < 0) { throw std::invalid_argument("Должен быть не отрицательным"); }
	num_wings = new_num_wings;
}

double Arthropod::get_max_length() const
{
	return max_length;
}

void Arthropod::set_max_length(double new_max_length)
{
	if (new_max_length < 0) { throw std::invalid_argument("Должен быть не отрицательным"); }
	max_length = new_max_length;
}

double Arthropod::get_max_weight() const
{
	return max_weight;
}

void Arthropod::set_max_weight(double new_max_weight)
{
	if (new_max_weight < 0) { throw std::invalid_argument("Должен быть не отрицательным"); }
	max_weight = new_max_weight;
}

void Arthropod::print_console()
{
	std::cout << "\n   Название вида:" << type;
	std::cout << "\n   Дата открытия вида:" << date;
	std::cout << "\n   Класс:" << get_class_animal_string();
	std::cout << "\n   Число конечностей:" << num_limbs;
	std::cout << "\n   Число крыльев:" << num_wings;
	std::cout << "\n   Максимальная длина:" << max_length;
	std::cout << "\n   Максимальная масса:" << max_weight;
}


bool operator==(const Arthropod& first, const Arthropod& second)
{
	return first.get_type() == second.get_type();
		
}

std::ostream& operator<<(std::ostream& os, const Arthropod& elem)
{
	os << elem.get_type() << '\n';
	os <<elem.get_date() << '\n';
	os << elem.get_class_animal_string() << '\n';
	os << elem.get_num_limbs() << '\n';
	os << elem.get_num_wings() << '\n';
	os << elem.get_max_length() << '\n';
	os << elem.get_max_weight() << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Arthropod& elem)
{
	std::string str = "";
	time_t time;
	int int_param;
	double double_param;
	while (is.peek() == '\n')
	{
		is.ignore(255, '\n');
	}
	std::getline(is, str);
	if (str != "") {
		elem.set_type(str);
		is >> time;
		elem.set_date(time);
		is >> str;
		if (!elem.set_class_animal(str)) {
			throw std::invalid_argument("Такого класса не существует!");
		}
		is >> int_param;
		elem.set_num_limbs(int_param);
		is >> int_param;
		elem.set_num_wings(int_param);
		is >> double_param;
		elem.set_max_length(double_param);
		is >> double_param;
		elem.set_max_weight(double_param);
		
	}
	return is;
}
