#pragma once
#include "Help.h"

enum Class
{
	 Crustacean = 1, Arachnid, Insect
};

struct Arthropod
{
private:

	std::string name{};
	tm discovery_date{};
	Class arthropod_type{};
	int limbs_count{};
	int wings_count{};
	double max_length{};
	double max_weight{};

public:

	Arthropod() {}
	Arthropod(std::string name, tm date, Class type, int limbs, int wings, double len, double weight) :
		name(name), discovery_date(date), arthropod_type(type), limbs_count(limbs), wings_count(wings),
		max_length(len), max_weight(weight) {}
	Arthropod(const Arthropod& other);

	std::string get_name() const { return name; }
	Class get_class() const { return arthropod_type; }
	tm get_discovery_date() const { return discovery_date; }
	double get_max_length() const { return max_length; }
	double get_max_weight() const { return max_weight; }
	
	friend std::ostream& operator<<(std::ostream& out, const Arthropod& arthropod);

	friend std::istream& operator>>(std::istream& in, Arthropod& arthropod);
	
};

bool operator==(const Arthropod& x1, const Arthropod& x2);
bool read_class(std::istream& in, Class& clss);
std::string class_to_string(Class clss);
bool operator<=(const tm& date1, const tm& date2);
bool operator>(const tm& date1, const tm& date2);


namespace std
{
	template <>
	struct hash<Arthropod> 
	{
		size_t operator()(const Arthropod& obj) const 
		{
			return hash<std::string>{}(obj.get_name());
		}
	};	
}