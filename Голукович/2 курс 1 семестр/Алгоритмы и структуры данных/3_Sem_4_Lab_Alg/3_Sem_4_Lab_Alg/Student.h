#pragma once

#include <string>
#include <iostream>
#include <fstream>

struct Mark
{
	std::string subject;
	int mark;
	Mark(std::string subject = std::string(), int mark = 0) : subject(subject), mark(mark) {}
};

const unsigned int COUNT_OF_EXAMS = 5;
class Student
{
private:
	std::string name;
	int course;
	int group;
	std::string form;
	Mark marks[COUNT_OF_EXAMS];
public:
	Student(std::string name, int course, int group, std::string form, Mark* Marks);

	void print();
	std::string get_name();
	int get_course();
	int get_group();
	std::string get_form();
	Mark* get_marks();
	bool is_good_or_excelent();

	static bool is_correct_data(std::string name, int course, int group, std::string form, Mark* marks);
	static int compare(Student& left, Student& right);
};