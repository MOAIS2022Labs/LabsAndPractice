#include "Faculty.h"

// удалить всех студентов двоечников
bool task1_1(Faculty& F)
{
	Vector f = F.get_vector();
	size_t prev_size = f.size();
	bool flag = true, result;
	Vector::iterator it = f.begin();
	while (it != f.end() && flag)
	{
		Student* st = dynamic_cast<Student*>((*it).get());
		if (st && st->kind() == 2)
			it = f.erase(it);
		else
			flag = false;
	}
	result = prev_size != f.size();
	F.set_vector(f);
	return result;
}

// удалить всех студентов двоечников
bool task1_2(Faculty& F)
{
	Vector f = F.get_vector();
	size_t prev_size = f.size();

	auto condition = [](const std::unique_ptr<Person>& p)
	{
		Student* st = dynamic_cast<Student*>(p.get());
		return st && st->kind() == 2;
	};
	f.erase(std::remove_if(f.begin(), f.end(), condition), f.end());
	F.set_vector(f);
	return prev_size != f.size();
}

// вернуть курсы, на которых больше всего отличников
std::string task2(Faculty& F)
{
	std::string result{};
	Vector f = F.get_vector();
	Vector::iterator it = f.begin();	
	int max = 0;
	Student* st = dynamic_cast<Student*>((*it).get());
	if (st)
	{
		int currect_course = st->get_course(), cnt = 0;;
		bool flag = true;
		while (it != f.end() && flag)
		{
			Student* st = dynamic_cast<Student*>((*it).get());
			if (st && st->kind() == 5)
			{
				if (currect_course == st->get_course())
				{
					++cnt;					
				}
				else
				{
					if (max < cnt)
					{
						max = cnt;
						result = std::to_string(currect_course);
					}
					else if (max == cnt)
					{
						result += " " + std::to_string(currect_course);
					}
					cnt = 1;
					currect_course = st->get_course();
				}
				
			}
			else
				flag = false;
			++it;
		}
		if (max < cnt)
		{
			max = cnt;
			result = std::to_string(currect_course);
		}
		else if (max == cnt)
		{
			result += " " + std::to_string(currect_course);
		}
	}
	return result;
}

int main()
{
	std::string fname = "Persons.txt";
	Faculty faculty(fname);
	std::cout << "Before sort\n";
	faculty.print();

	std::cout << "After sort\n";
	faculty.sort();	
	faculty.print();

	/*std::cout << "After delete\n";
	if (task1_2(faculty))
		faculty.print();
	else
		std::cout << "AMM is the best";*/

	std::string result = task2(faculty);
	if (result != "")
		std::cout << result;
	return 0;
}