#include <Windows.h>
#include "Depo.h"

bool task(Depo& depo, int year)
{
	bool result = false;
	std::vector<std::shared_ptr<Wagon>> wagon_vector(depo.get_wagon_vector());
	std::vector<std::shared_ptr<Wagon>>::iterator iterator_end = wagon_vector.begin();
	bool stop = false;
	while (iterator_end != wagon_vector.end() && !stop)
	{
		Freight_Wagon* wagon = dynamic_cast<Freight_Wagon*>((*iterator_end).get());
		if (wagon && wagon->get_year() < year && wagon->get_type() == "Полувагон")
			iterator_end++;	
		else
			stop = true;
	}
	if (iterator_end != wagon_vector.begin())
	{
		wagon_vector.erase(wagon_vector.begin(), iterator_end);
		depo.set_wagon_vector(wagon_vector);
		result = true;
	}
	return result;
}

int main()
{
	SetConsoleOutputCP(1251);

	std::string file_name = "test.txt";
	Depo depo(file_name);
	depo.print(std::cout);
	std::cout << "\n\n------\n\n";
	depo.sort();
	depo.print(std::cout);
	std::cout << "\n\n------\n\n";
	int year = 2001;
	if (task(depo, year))
		depo.print(std::cout);
	else
		std::cout << "Количество вагонов не изменилось.";

	return 0;
}

