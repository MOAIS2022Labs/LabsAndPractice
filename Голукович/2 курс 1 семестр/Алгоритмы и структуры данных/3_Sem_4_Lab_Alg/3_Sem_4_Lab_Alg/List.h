#pragma once
#include "Student.h"

struct List_Elem 
{
	List_Elem* next;
	Student* student;
	List_Elem(List_Elem* next, Student*& student) : next(next), student(student) {};
	~List_Elem();
};

using Elem = List_Elem*;

class List 
{
private:
	Elem first;
	int count;
public:
	List();
	List(std::ifstream& file);
	~List();

	Elem get_first();
	bool add_elem(Student* student);
	bool empty();
	void print();
};