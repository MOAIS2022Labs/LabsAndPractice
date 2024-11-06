#include "Arthropod.h"

std::ostream& operator<<(std::ostream& out, const Arthropod& arthropod)
{
	out <<  arthropod.name << '\n';
	tm date = arthropod.discovery_date;
	out << date_to_string(date.tm_mday, date.tm_mon + 1, date.tm_year + 1900) << '\n';
	out << class_to_string(arthropod.arthropod_type) << '\n';
	out << arthropod.limbs_count << '\n';
	out << arthropod.wings_count << '\n';
	out << arthropod.max_length << '\n';
	out << arthropod.max_weight << '\n';
	return out;
}

std::string class_to_string(Class clss)
{
	switch (clss)
	{
	case Insect:
		return "Насекомое";
	case Crustacean:
		return "Ракообразное";
	case Arachnid:
		return "Паукообразное";
	}
}

bool read_class(std::istream& in, Class& clss)
{
	std::string str{};
	in >> str;
	if (str == "Насекомое")
	{
		clss = Insect;
		return true;
	}
	if (str == "Ракообразное")
	{
		clss = Crustacean;
		return true;
	}
	if (str == "Паукообразное")
	{
		clss = Arachnid;
		return true;
	}	
	return false;
}

bool operator<=(const tm& date1, const tm& date2)
{
	if (date1.tm_year < date2.tm_year)
		return true;
	if (date1.tm_year > date2.tm_year)
		return false;
	if (date1.tm_mon < date2.tm_mon)
		return true;
	if (date1.tm_mon > date2.tm_mon)
		return false;
	return date1.tm_mday <= date2.tm_mday;
}

bool operator>(const tm& date1, const tm& date2)
{
	return !(date1 <= date2);
}

std::istream& operator>>(std::istream& in, Arthropod& arthropod)
{	
	Arthropod tmp;
	std::string str;	
	std::getline(in, str);	
	if (in.eof())
	{
		in.ignore(255, '\n');
		return in;
	}
	tmp.name = str;
	tmp.discovery_date = read_date(in);
	if (!read_class(in, tmp.arthropod_type))
		throw std::invalid_argument("Неверный класс!\n");
	int x;
	in >> x;
	if (x < 0)
		throw std::invalid_argument("Неверное число конечностей!\n");
	tmp.limbs_count = x;
	in >> x;
	if (x < 0)
		throw std::invalid_argument("Неверное число крыльев!\n");
	tmp.wings_count = x;
	double x2;
	in >> x2;
	if (x2 <= 0.00001)
		throw std::invalid_argument("Неверная длина!\n");
	tmp.max_length = x2;
	in >> x2;
	in.ignore(255, '\n');
	if (x2 <= 0.00001)
		throw std::invalid_argument("Неверная масса!\n");
	tmp.max_weight = x2;
	arthropod = tmp;
	return in;
}

bool operator==(const Arthropod& x1, const Arthropod& x2)
{
	return x1.get_name() == x2.get_name();
}

Arthropod::Arthropod(const Arthropod& other)
{
	this->name = other.name;
	this->discovery_date = other.discovery_date;
	this->arthropod_type = other.arthropod_type;
	this->limbs_count = other.limbs_count;
	this->wings_count = other.wings_count;
	this->max_length = other.max_length;
	this->max_weight = other.max_weight;
}
