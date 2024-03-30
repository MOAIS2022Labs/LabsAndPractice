#include "Faculty.h"
#include "Dictionary.h"
#include "sstream"
#include <set>

std::map<int, int> course_and_counter_of_best_students(Faculty& F)
{
	std::map<int, int> result;
	Vector f = F.get_vector();

	for (auto& item : f)
	{
		Student* st = dynamic_cast<Student*>(item.get());
		if (st && st->kind() == 5)
		{
			if (result.count(st->get_course()))
				result[st->get_course()] += 1;
			else
				result[st->get_course()] = 1;
		}
	}

	return result;
}

/*��� ��������� ����, ���������� ��������� ��������� �����. ����� ������������ �� ����� ��������, 
������� �������� �� ����� 10 ���� "C", "N", "U" � ��� ���� �� �������� �� ����� ����� "X", "Y"*/
int longest_sequence(std::ifstream& file)
{
	int result = 0, max = 0, beg = -1;
	std::map<char, int> mapa
	{
		{ 'U', 0 },
		{ 'N', 0 },
		{ 'S', 0 }
	};	
	std::string str;
	file >> str;
	int len = str.length();
	for (int i = 0; i < len; ++i)
	{
		if (str[i] == 'U' || str[i] == 'S' || str[i] == 'N')
		{
			mapa[str[i]] += 1;
			if (mapa[str[i]] > 10)
			{
				max = i - beg - 1 > max ? i - beg - 1 : max;
				bool stop = false;
				for (int j = beg + 1; !stop; ++j)
				{
					if (str[j] == str[i])
					{
						beg = j;
						stop = true;
					}
					if (str[i] == 'U' || str[i] == 'S' || str[i] == 'N')
						--mapa[str[i]];
				}
			}
		}
		if (str[i] == 'X' || str[i] == 'Y' || str[i] == 'Z')
		{
			max = i - beg - 1 > max ? i - beg - 1 : max;
			beg = i;
			mapa['U'] = 0;
			mapa['N'] = 0;
			mapa['S'] = 0;

		}
	}
	max = len - beg - 1 > max ? len - beg - 1 : max;
	return result;
}

// ��� ����, ���������� ������, � ������ �������� ��������� ���� � ��� ����� ��������� ���������
// ����������� ������ �����, ����� ������� ����� ����������� ������ �����, � ������� ��� �����������
void print_words(std::ifstream& file)
{
	std::map<std::string, std::set<int>> mp;
	std::string line;
	std::stringstream ss;
	int num = 0;
	while (std::getline(file, line))
	{
		++num;
		ss << line;
		std::string word;
		while (ss >> word)
		{
			mp[word].insert(num);
		}
		ss.clear();
	}
	for (auto pr : mp)
	{
		std::cout << pr.first << ": ";
		for (auto x : pr.second)
			std::cout << x << ", ";
		std::cout << '\n';
	}
}

// ���������� ����� ������ ������, ���������� ���������� ���������� ���� � �������������� �������
int num_line_with_repeat(std::ifstream& file)
{
	std::string line;
	std::stringstream ss;
	int max_line = -1, num = 0, max_count = 0;
	auto check = [](std::string word)
	{
		std::set<char> set;
		for (char c : word)
			set.insert(c);
		return set.size() != word.length();
	};
	while (std::getline(file, line))
	{
		ss << line;
		++num;
		std::string word;
		int count;
		while (ss >> word)
		{
			count += check(word);
		}
		ss.clear();
		// ��� �������� std::cout << num << ' ' << count << '\n';
		if (count > max_count)
		{
			max_count = count;
			max_line = num;
		}
	}
	return max_line;
}

int main()
{
	// ������ 1 � 3
	//std::string fname = "Persons.txt";
	//Faculty faculty(fname);
	//std::cout << "Before sort\n";
	//faculty.print();

	//std::cout << "\n\nMap:\n\n";
	//std::map<int, int> result = course_and_counter_of_best_students(faculty);
	//for (auto x : result)
	//	std::cout << x.first << ": " << x.second << "\n";
	//Dictionary<int, int> mp(result);
	//for (auto& key : mp.keys())
	//	std::cout << key << ' ';

	// ����� 2

	/*std::ifstream file("letters.txt");
	std::cout << longest_sequence(file);*/

	// ����� ������
	/*std::ifstream file("words.txt");
	print_words(file);*/

	// ����� � �������������� �������
	std::ifstream file("words.txt");
	num_line_with_repeat(file);
	file.close();
}