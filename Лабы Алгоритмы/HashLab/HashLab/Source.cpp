#include "HashTableList.h"
#include <Windows.h>

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::ifstream file("data.txt");
	if (file)
	{
		HashTableList HT(3);
		HT.fill(file);
		HT.print();
		/*std::cout << (HT.add({ "window", "окно" }) ? "" : "No") << "Add\n";
		std::cout << (HT.add({ "blue", "синий" }) ? "" : "No") << "Add\n";
		Pair elem;
		std::cout << (HT.find("blue", elem) ? elem.second : "No Find") << '\n';*/
		std::cout << "-----------------------------\n";
		PrintEdition* pt = nullptr;
		if (HT.find("Мурзилка", pt))
			pt->print();
		else
			std::cout << "Not found\n";
		std::cout << "-----------------------------\n";
		if (!HT.add(new Magazine({ "Мурзилак", 10, "Автомир2", 2,2024, "Car.ru" })))
			std::cout << "No add\n";
		HT.print();
		if (!HT.add(new Magazine({ "Мурзилка", 10, "Мурзилка", 2,2024, "Mur.ru" })))
			std::cout << "No add\n";
		HT.erase("Мурзилка");
		HT.print();
		if (HT.find("Мурзилка", pt))
			pt->print();
		else
			std::cout << "No\n";
		if (!HT.add(new Magazine({ "Мурзилка", 10, "Мурзилка", 2,2024, "Car.ru" })))
			std::cout << "No add\n";
		HT.print();
	}
	else
		std::cout << "File is not opened!\n";
	file.close();
	return 0;
}