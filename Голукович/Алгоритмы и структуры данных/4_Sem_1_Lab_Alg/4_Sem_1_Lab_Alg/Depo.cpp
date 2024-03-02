#include "Depo.h"

Depo::Depo(std::string file_name)
{
	std::ifstream file(file_name);
	std::getline(file, name);
	char type;
	while (file >> type)
	{
		if (type == 'П')
			wagon_vector.push_back(std::make_shared<Passenger_Wagon>(file));
		else
			wagon_vector.push_back(std::make_shared<Freight_Wagon>(file));
	}
	file.close();
}

void Depo::print(std::ostream& out) const
{
	out << name << '\n';
	for (auto& wagon : wagon_vector)
		(*wagon).print(out);
}

auto compare = [](const std::shared_ptr<Wagon>& left, const std::shared_ptr<Wagon>& right)
{
	bool result = left.get()->compare(*right.get());
	Freight_Wagon* left_wagon = dynamic_cast<Freight_Wagon*>(left.get());
	Freight_Wagon* right_wagon = dynamic_cast<Freight_Wagon*>(right.get());
	if (!left_wagon && right_wagon && right_wagon->get_type() == "Полувагон")
		result = false;
	if (left_wagon && right_wagon && left_wagon->get_type() != right_wagon->get_type())
	{
		if (left_wagon->get_type() == "Полувагон")
			result = true;
		else
			result = false;
	}
	if (left_wagon && !right_wagon && left_wagon->get_type() == "Полувагон")
		result = true;
	return result;
};

void Depo::sort()
{
	std::sort(wagon_vector.begin(), wagon_vector.end(), compare);
}

std::vector<std::shared_ptr<Wagon>>& Depo::get_wagon_vector()
{
	return wagon_vector;
}

void Depo::set_wagon_vector(std::vector<std::shared_ptr<Wagon>>& vector)
{
	wagon_vector = vector;
}