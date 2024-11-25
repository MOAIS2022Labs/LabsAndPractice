#include "List.h"

List::List()
{
	first = nullptr;
	count = 0;
}

List::List(std::ifstream& file)
{
	first = nullptr;
	count = 0;
	while (!file.eof())
	{
		std::string name, form;
		int course, group;
		Mark marks[COUNT_OF_EXAMS];
		std::getline(file, name);
		file >> course >> group;
		file.ignore();
		std::getline(file, form);
		for (int i = 0; i < COUNT_OF_EXAMS; ++i)
		{
			std::getline(file, marks[i].subject);
			file >> marks[i].mark;
			file.ignore();
		}

		if (Student::is_correct_data(name, course, group, form, marks))
		{
			Student* student = new Student(name, course, group, form, marks);
			if (add_elem(student))
				count += 1;
		}
	}
}

List::~List()
{
	while (first)
	{
		Elem t = first;
		first = first->next;
		delete t;
	}
	first = nullptr;
	count = 0;
}

Elem List::get_first()
{
	return first;
}

bool List::add_elem(Student* student)
{
	bool result = false;
	if (first)
	{
		Elem t = first;
		while (t->next && Student::compare(*t->next->student, *student) < 1)
			t = t->next;
		if (Student::compare(*t->student, *student) == -1)
		{
			t->next = new List_Elem(t->next, student);
			result = true;
		}
	}
	else
	{
		first = new List_Elem(first, student);
		result = true;
	}
	return result;
}

bool List::empty()
{
	return count == 0;
}

void List::print()
{
	Elem t = first;
	while (t)
	{
		t->student->print();
		std::cout << '\n';
		t = t->next;
	}
}

List_Elem::~List_Elem()
{
	next = nullptr;
	delete student;
}
