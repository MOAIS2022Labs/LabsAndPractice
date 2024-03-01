// класс Person абстрактный
// Student и Lecture полиморфные
// в конструкторе чтение данных из текстового файла
// продемонстрировать вызов методов класса предка у классов наследников
// у Student метод kind(), возвращающий как учится студент

// в отдельной библиотеке описать класс контейнер, в нём вектор из умных указателей unique_ptr<Person>
// у класса Faculty 
// у класса Faculty описать сортировку
// в корпараторе если оба студенты, то для обоих вызвать kind
// если первый Student, второй Lecture, или если оба Lecture то вернуть false
// если первый Lecture, второй Student, тогда вернуть true

// TODO: удалить всех студентов двоечников


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