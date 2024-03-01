// ����� Person �����������
// Student � Lecture �����������
// � ������������ ������ ������ �� ���������� �����
// ������������������ ����� ������� ������ ������ � ������� �����������
// � Student ����� kind(), ������������ ��� ������ �������

// � ��������� ���������� ������� ����� ���������, � �� ������ �� ����� ���������� unique_ptr<Person>
// � ������ Faculty 
// � ������ Faculty ������� ����������
// � ����������� ���� ��� ��������, �� ��� ����� ������� kind
// ���� ������ Student, ������ Lecture, ��� ���� ��� Lecture �� ������� false
// ���� ������ Lecture, ������ Student, ����� ������� true

// TODO: ������� ���� ��������� ����������


#include <fstream>
#include "Person.h"

int main()
{
	std::ifstream file("Persons.txt");
	if (file)
	{
		std::string FIO;
		int course;
		int arr[5];
		file >> FIO >> course;
		for (int i = 0; i < 5; ++i)
			file >> arr[i];
		Student st(FIO, course, arr);
		st.print();

		std::cout << '\n';

		std::string post;
		file.ignore();
		file >> FIO >> post;
		Lecture l(FIO, post);
		l.print();
	}

	return 0;
}