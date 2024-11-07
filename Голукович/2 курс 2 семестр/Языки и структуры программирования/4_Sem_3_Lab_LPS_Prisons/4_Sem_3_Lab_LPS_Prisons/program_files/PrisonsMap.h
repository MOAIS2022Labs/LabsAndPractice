#pragma once
#include "Prison.h"
#include <map>

class PrisonsMap
{
private:
	std::string prisons_file_name;
	std::fstream* prisons_file;
	std::map<std::string, Prison*> prisons;
public:
	PrisonsMap(std::string file_name);
	~PrisonsMap();

	void save();

	std::map<std::string, Prison*>::iterator begin();

	std::map<std::string, Prison*>::iterator end();

	std::map<std::string, Prison*>::iterator find(std::string key);

	Prison* at(std::string key);

	size_t erase(std::string key);

	void insert(std::string prison_name, Prison* prison);
};