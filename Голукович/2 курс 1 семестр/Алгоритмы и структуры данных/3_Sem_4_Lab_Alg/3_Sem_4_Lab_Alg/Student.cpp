#include "Student.h"

//Student::Student(const Student& student)
//{
//	this->name = student.name;
//	this->course = student.course;
//	this->group = student.group;
//	this->form = student.form;
//	for (int i = 0; i < COUNT_OF_EXAMS; ++i)
//		this->marks[i] = student.marks[i];
//}

Student::Student(std::string name, int course, int group, std::string form, Mark* marks)
{
	this->name = name;
	this->course = course;
	this->group = group;
	this->form = form;
	for (int i = 0; i < COUNT_OF_EXAMS; ++i)
		this->marks[i] = marks[i];
}

void Student::print()
{
	std::cout << name << '\n';
	std::cout << course << " курс\n";
	std::cout << group << " группа\n";
	std::cout << form << '\n';
	for (int i = 0; i < COUNT_OF_EXAMS; ++i)
		std::cout << marks[i].subject << " : " << marks->mark << '\n';
}

std::string Student::get_name()
{
	return name;
}

int Student::get_course()
{
	return course;
}

int Student::get_group()
{
	return group;
}

std::string Student::get_form()
{
	return form;
}

Mark* Student::get_marks()
{
	return marks;
}

bool Student::is_good_or_excelent()
{
	bool result = true;
	for (int i = 0; i < COUNT_OF_EXAMS && result; ++i)
		if (marks->mark != 4 && marks->mark != 5)
			result = false;
	return result;
}

bool Student::is_correct_data(std::string name, int course, int group, std::string form, Mark* marks)
{
	bool result = true;
	std::string bad_chars = std::string("`1234567890-=[];',./~!@#$%^&*()_+{}:\"<>?|");
	if (name.find_first_of(bad_chars) != std::string::npos)
		result = false;
	if (result && course <= 0 || course > 4)
		result = false;
	if (result && group <= 0 || group > 99)
		result = false;
	if (result && form != "Ѕюджет" && form != "¬небюджет")
		result = false;
	for (int i = 0; i < COUNT_OF_EXAMS && result; ++i)
		if (marks->subject.find_first_of(bad_chars) != std::string::npos || marks->mark < 2 && marks->mark > 5)
			result = false;
	return result;
}

int Student::compare(Student& left, Student& right)
{
	int result = left.get_form().compare(right.get_form());
	if (result == 0)
	{
		result = left.is_good_or_excelent() - right.is_good_or_excelent();
		//result = right.is_good_or_excelent() - left.is_good_or_excelent();
		if (result == 0)
		{
			result = left.get_course() - right.get_course();
			if (result == 0)
			{
				result = left.get_group() - right.get_group();
				if (result == 0)
					result = left.get_name().compare(right.get_name());
			}
		}
	}
	return result;
}
