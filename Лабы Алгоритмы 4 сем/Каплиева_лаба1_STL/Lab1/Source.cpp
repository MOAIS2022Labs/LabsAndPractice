//Разработать контейнерный класс «Библиотека», в котором список изданий
//упорядочен по возрастанию значений поля Наименование.
//Удалить журналы, не имеющие веб - сайтов.

#include "Library.h"
#include <Windows.h>

bool task(Library& lib);

int main()
{
	SetConsoleOutputCP(1251);
	std::string fname = "Editions.txt";
	Library lib("Библиотека", fname);
	std::cout << "До сортировки\n";
	lib.print();
	std::cout << "\nПосле сортировки\n";
	lib.sort();
	lib.print();
	std::cout << "\nПосле удаления\n";
	if (task(lib))
		lib.print();
	else
		std::cout << "Таких элементов нет\n";
	return 0;
}

bool task(Library& lib)
{
	auto list = lib.get_list();
	int prev_size = list.size();
	auto predicate = [](const std::unique_ptr<PrintEdition>& elem)->bool
	{
		Magazine* magazine = dynamic_cast<Magazine*>(elem.get());
		return (magazine && magazine->get_web_site() == "-");
	};
	list.remove_if(predicate);
	bool result = prev_size != list.size();
	if (result)
		lib.set_list(list);
	return result;
}
