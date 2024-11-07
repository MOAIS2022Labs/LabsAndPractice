#include "List.h"
#include <Windows.h>
#include <fstream>

List task(List& list);

int main()
{
	SetConsoleOutputCP(1251);

	std::ifstream file("students.txt");
	List list_of_students(file);
	file.close();
	list_of_students.print();
	std::cout << "-----\n";
	List list = task(list_of_students);
	list.print();

	std::cin.get();
	return 0;
}

List task(List& list_of_students)
{
	List list;
	Elem t = list_of_students.get_first();
	while (t && t->student->get_form() == "ֱ‏הזוע")
	{
		list.add_elem(new Student(t->student->get_name(), t->student->get_course(), t->student->get_group(), t->student->get_form(), t->student->get_marks()));
		t = t->next;
	}
	return list;
}