#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include "PrintEdition.h"


using List = std::list<PrintEdition*>;
using Vector = std::vector<List>;



class HashTableList
{
private:

	Vector table;
	size_t max_size;
	size_t size;
	const int MAX_LIST_SIZE = 2;
	void rehash_table()
	{
		std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!\nReHash\n!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		Vector new_table;
		max_size *= 2;
		new_table.resize(max_size);
		for (auto lst : table)
		{
			for (auto elem : lst)
			{
				int index = hash(elem->get_name());
				new_table[index].push_back(elem);
			}
		}
		table = new_table;
	}

public:

	HashTableList(size_t max_size) : max_size(max_size)
	{
		size = 0;
		table.resize(max_size);
	}

	~HashTableList()
	{
		for (auto lst : table)
			for (auto elem : lst)
			{
				delete elem;
				elem = nullptr;
			}
	}

	int hash(std::string key)
	{
		int result = 0;
		for (char c : key)
			result += c;
		return result % max_size;
	}

	bool find(std::string key, PrintEdition*& elem)
	{
		bool result = false;
		int index = hash(key);

		List::iterator it = std::find_if(table[index].begin(), table[index].end(),
			[key](PrintEdition* tmp) { return tmp->get_name() == key; }
		);
		if (it != table[index].end())
		{
			result = true;
			elem = *it;
		}

		return result;
	}

	bool add(PrintEdition* elem)
	{
		bool result = false;
		int index = hash(elem->get_name());
		if (table[index].size() > MAX_LIST_SIZE)
			rehash_table();
		List::iterator it = std::find_if(table[index].begin(), table[index].end(),
			[elem](PrintEdition* tmp) { return tmp->get_name() == elem->get_name(); }
		);
		if (it == table[index].end())
		{			
			result = true;
			table[index].push_back(elem);
			++size;
			
		}
		return result;
	}

	bool erase(std::string key)
	{
		bool result = false;
		int index = hash(key);

		List::iterator it = std::find_if(table[index].begin(), table[index].end(),
			[key](PrintEdition* tmp) { return tmp->get_name() == key; }
		);
		if (it != table[index].end())
		{
			result = true;
			delete* it;
			*it = nullptr;
			table[index].erase(it);
			--size;
		}

		return result;
	}

	void fill(std::ifstream& file)
	{
		std::string type{};
		while (file >> type)
		{
			file.ignore(255, '\n');
			if (type == " нига")
			{
				std::string name{};
				std::getline(file, name);
				size_t pages{};
				file >> pages;
				file.ignore(255, '\n');
				std::string ph{};
				std::getline(file, ph);
				std::string author{};
				std::getline(file, author);
				std::string genre{};
				std::getline(file, genre);
				std::string bt{};
				std::getline(file, bt);
				Book* book = new Book(name, pages, ph, author, genre, bt);
				add(book);
			}
			else
				if (type == "∆урнал")
				{
					std::string name{};
					std::getline(file, name);
					size_t pages{};
					file >> pages;
					file.ignore(255, '\n');
					std::string ph{};
					std::getline(file, ph);
					size_t number{};
					file >> number;
					size_t year{};
					file >> year;
					file.ignore(255, '\n');
					std::string ws{};
					std::getline(file, ws);
					Magazine* magazine = new Magazine(name, pages, ph, number, year, ws);
					add(magazine);
				}
		}
	}

	void print()
	{
		int index = -1;
		for (auto lst : table)
		{
			++index;
			if (!lst.empty())
				for (auto elem : lst)
				{
					std::cout << index << '\n';
					elem->print();
				}
		}
	}
};