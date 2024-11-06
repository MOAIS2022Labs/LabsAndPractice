#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <Windows.h>



using Pair = std::pair<std::string, std::string>;
using List = std::list<Pair>;
using Vector = std::vector<List>;


std::string to_string(const Pair& elem)
{
	return elem.first + ' ' + elem.second;
}

class HashTableList
{
private:
	Vector table;
	size_t max_size;
	size_t size;
public:
	HashTableList(size_t max_size) : max_size(max_size)
	{
		table.resize(max_size);
	}

	int hash(std::string key)
	{
		int result = 0;
		for (char c : key)
			result += c;
		return result % max_size;
	}

	bool find(std::string key, Pair& elem) // ключ —  английский вариант
	{
		bool result = false;
		int index = hash(key);

		List::iterator it = std::find_if(table[index].begin(), table[index].end(), 
			[key](Pair& tmp) { return tmp.first == key; }
		);
		if (it == table[index].end())
		{
			result = true;
			elem = *it;			
		}

		return result;
	}

	bool add(const Pair& elem)
	{
		bool result = false;
		int index = hash(elem.first);

		List::iterator it = std::find_if(table[index].begin(), table[index].end(),
			[elem](Pair& tmp) { return tmp.first == elem.first; }
		);
		if (it != table[index].end())
		{
			result = true;
			table[index].push_back(elem);
		}

		return result;
	}

	bool erase(std::string key)
	{
		bool result = false;
		int index = hash(key);
		Pair temp{ key, "" };

		List::iterator it = std::find_if(table[index].begin(), table[index].end(),
			[key](Pair& tmp) { return tmp.first == key; }
		);
		if (it != table[index].end())
		{
			result = true;
			table[index].erase(it);
		}

		return result;
	}

	void fill(std::ifstream& file)
	{
		Pair elem;		
		while (file >> elem.first >> elem.second)
			add(elem);
	}

	void print()
	{
		int index = -1;
		for (auto lst : table)
		{
			++index;
			if (!lst.empty())
				for (auto elem : lst)
					std::cout << index << to_string(elem) << '\n';
		}
	}


};
struct Cell
{
	Pair info;
	int used = 0;
};

using Vector = std::vector<Cell>;

class HashTableInt
{
private:
	Vector table;
	size_t max_size;
	size_t size;
public:
	HashTableInt(size_t max_size) : max_size(max_size)
	{
		table.resize(max_size);
	}

	int hash(std::string key)
	{
		int result = 0;
		for (char c : key)
			result += c;
		return result % max_size;
	}

	int find(std::string key, Pair& elem)
	{
		int result = -1;
		int index = hash(key);
		while (!(table[index].used == 0 || table[index].used == 1 && table[index].info.first == key))
			index = (index + 1) % max_size;
		if (table[index].used == 1)
		{
			result = index;
			elem = table[index].info;
		}
		return result;
	}

	bool add(const Pair& elem)
	{
		bool result = false;
		int index = hash(elem.first);

		while (table[index].used == 1 && table[index].info.first != elem.first)
			index = (index + 1) % max_size;
		if (table[index].used != 1)
		{
			table[index].used = 1;
			table[index].info = elem;
			result = true;
		}
		return result;
	}

	bool erase(std::string key)
	{
		bool result = false;
		int index = hash(key);
		while (!(table[index].used == 0 || table[index].used == 1 && table[index].info.first == key))
			index = (index + 1) % max_size;
		if (table[index].used == 1)
		{
			result = true;
			table[index].used = -1;
		}
		return result;
	}

	void fill(std::ifstream& file)
	{
		Pair elem;
		while (file >> elem.first >> elem.second)
			add(elem);
	}

	void print()
	{
		int index = -1;
		for (auto elem : table)
		{
			++index;
			if (table[index].used == 1)
			{
				std::cout << index << ": (" << hash(elem.info.first) << ") " << to_string(elem.info) << '\n';
			}
		}
	}


};

struct Cell
{
	Pair info;
	bool used = false;
};

using Vector = std::vector<Cell>;

class HashTableBool
{
private:
	Vector table;
	size_t max_size;
	size_t size;
public:
	HashTableBool(size_t max_size) : max_size(max_size)
	{
		table.resize(max_size);
	}

	int hash(std::string key)
	{
		int result = 0;
		for (char c : key)
			result += c;
		return result % max_size;
	}

	int find(std::string key)
	{
		int result = -1;
		int index = hash(key);
		while (table[index].used && table[index].info.first != key)
			index = (index + 1) % max_size;
		if (table[index].used)
			result = index;
		return result;
	}

	bool add(const Pair& elem)
	{
		bool result = false;
		int index = hash(elem.first);
		while (table[index].used && table[index].info.first != elem.first)
			index = (index + 1) % max_size;
		if (!table[index].used)
		{
			result = true;
			table[index].info = elem;
			table[index].used = true;
		}
		return result;
	}

	bool erase(std::string key)
	{
		bool result = false;
		int index = find(key);
		if (index != -1)
		{
			auto dist = [this](int a, int b)
				{
					return (b - a + max_size) % max_size;
				};
			table[index].used = false;
			int window = index;
			++index;
			result = true;
			while (table[index].used)
			{
				if (dist(hash(table[index].info.first), index) >= dist(window, index))
				{
					table[window] = table[index];
					table[index].used = false;
					window = index;
				}
				index = (index + 1) % max_size;
			}
		}
		return result;
	}
	
	void fill(std::ifstream& file)
	{
		Pair elem;
		while (file >> elem.first >> elem.second)
			add(elem);
	}

	void print()
	{
		int index = -1;
		for (auto elem : table)
		{
			++index;
			if (table[index].used == 1)
			{
				std::cout << index << ": (" << hash(elem.info.first) << ") " << to_string(elem.info) << '\n';
			}
		}
	}


};

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::ifstream file("eng_rus.txt");
	if (file)
	{
		HashTableList HT(15);
		HT.fill(file);
		HT.print();
		std::cout << (HT.add({ "window", "окно" }) ? "" : "No") << "Add\n";
		std::cout << (HT.add({ "blue", "синий" }) ? "" : "No") << "Add\n";
		Pair elem;
		std::cout << (HT.find("blue", elem) ? elem.second : "No Find") << '\n';
	}
	else
		std::cout << "File is not opened!\n";
	file.close();
	return 0;
}