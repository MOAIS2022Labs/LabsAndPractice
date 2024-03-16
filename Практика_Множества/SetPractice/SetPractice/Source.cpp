#include "MathSet.h"
#include "sstream"
#include <map>

// удалить повторяющиеся числа
MathSet task(std::ifstream& file)
{
	MathSet all, tw;
	TInfo x;
	while (file >> x)
	{
		if (all.mset.count(x))
		{
			tw.mset.insert(x);
		}
		else
		{
			all.mset.insert(x);
		}
	}
	return all.difference(tw);
}

// текст разбит на строки, слова разделены произвольным количеством пробелов
// найти числа, которые есть во всех строчках
MathSet task2(std::ifstream& file)
{
	MathSet result;
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	int x;
	while (ss >> x)
		result.mset.insert(x);
	while (std::getline(file, line))
	{
		std::stringstream ss1(line);
		MathSet tmp;
		while (ss1 >> x)
			tmp.mset.insert(x);
		result = result.intersection(tmp);
	}
	return result;
}

// Построить частотный словарь с числами из task2
std::map<int, int> dict(std::ifstream& file)
{
	int x;
	std::map<int, int> result;
	while (file >> x)
	{
		if (result.count(x))
			result[x] += 1;
		else
			result[x] = 1;
	}
	return result;
}

int main()
{
	/*std::set<TInfo> st1{ 1, 3, 5, 7, 9 };
	std::set<TInfo> st2{ 2, 5, 4, 7, 6, 3, 8 };
	MathSet set1(st1);
	MathSet set2(st2);
	set1.print();
	set2.print();
	MathSet set3 = set1.union_set(set2);
	std::cout << "Union\n";
	set3.print();
	std::cout << "Intersection\n";
	set3 = set1.intersection(set2);
	set3.print();
	std::cout << "Difference\n";
	set3 = set2.difference(set1);
	set3.print();*/

	/*std::ifstream file("test.txt");
	MathSet res = task(file);
	res.print();
	file.close();*/

	/*std::ifstream file("test2.txt");
	MathSet res = task2(file);
	res.print();
	file.close();*/

	std::ifstream file("test2.txt");
	std::map<int, int> result = dict(file);
	for (auto x : result)
	{
		std::cout << x.first << ": " << x.second << '\n';
	}

	return 0;
}