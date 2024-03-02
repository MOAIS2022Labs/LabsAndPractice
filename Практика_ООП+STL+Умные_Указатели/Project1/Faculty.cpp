#include "Faculty.h"

Faculty::Faculty(std::string file_name)
{
	std::ifstream file(file_name);
	std::getline(file, name);
	char type;
	while (file >> type)
	{
		file.ignore();
		std::string person_name;
		std::getline(file, person_name);
		switch (type)
		{
		case 'S':
		{
			int course;
			int arr[5];
			file >> course;
			for (int i = 0; i < 5; ++i)
				file >> arr[i];
			file.ignore();
			faculty.push_back(std::make_unique<Student>(person_name, course, arr));			
			break;
		}

		case 'L':
			std::string post;
			std::getline(file, post);
			faculty.push_back(std::make_unique<Lecture>(person_name, post));
			break;
		}
	}
	file.close();
}

void Faculty::print()
{
	std::cout << name << '\n';
	for (auto& person : faculty)
		person->print();

}

void Faculty::sort()
{
	// вид сортировки: сначала студенты, среди студентов сначала двоечники
	//auto compare = [](const std::unique_ptr<Person>& p1, const std::unique_ptr<Person>& p2)->bool
	//{
	//	bool result = false;
	//	Student* s1 = dynamic_cast<Student*>(p1.get());
	//	Student* s2 = dynamic_cast<Student*>(p2.get());
	//	if (s1 && s2)
	//	{
	//		if (s1->kind() < s2->kind())
	//			result = true;
	//	}
	//	else
	//	{
	//		// это не два студента 
	//		result = s1 && !s2;
	//	}
	//	return result;
	//};
	//std::sort(faculty.begin(), faculty.end(), compare);

	// сначала студенты, среди них отличники
	auto compare = [](const std::unique_ptr<Person>& p1, const std::unique_ptr<Person>& p2)->bool
	{
		bool result = false;
		Student* s1 = dynamic_cast<Student*>(p1.get());
		Student* s2 = dynamic_cast<Student*>(p2.get());
		if (s1 && s2)
		{
			if (s1->kind() > s2->kind() || (s1->kind() == s2->kind() && s1->get_course() < s2->get_course()))
				result = true;
		}
		else
		{
			// это не два студента 
			result = s1 && !s2;
		}
		return result;
	};
	std::sort(faculty.begin(), faculty.end(), compare);

}
