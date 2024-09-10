#include "PrisonsMap.h"

PrisonsMap::PrisonsMap(std::string file_name)
{
	prisons_file_name = file_name;
	prisons_file = new std::fstream(prisons_file_name);
	std::string prison_name;
	while (*prisons_file && !prisons_file->eof())
	{
		std::getline(*prisons_file, prison_name);
		if (prison_name.size() > 0)
			insert(prison_name, new Prison(prison_name, new std::fstream(prison_name)));
	}
	if (find("Wanted") == end())
		insert("Wanted", new Prison("Wanted", new std::fstream("Wanted", std::ios::in | std::ios::out | std::ios::app)));
	prisons_file->clear();
	prisons_file->seekg(0);
	prisons_file->seekp(0);

	std::string message = "";
	for (std::pair<std::string, Prison*> pair : prisons)
	{
		if (pair.first != "Wanted")
		{
			std::vector<Villain> wanted = pair.second->selection([](Villain& value) { return !value.get_is_catched(); });
			if (!wanted.empty())
			{
				message.append(pair.first + ", ");
				prisons.at("Wanted")->add(wanted.begin(), wanted.end());
				std::vector<Villain> catched = pair.second->selection([](Villain& value) { return value.get_is_catched(); });
				pair.second->set(catched);
			}
		}
		else
		{
			std::vector<Villain> catched = pair.second->selection([](Villain& value) { return value.get_is_catched(); });
			if (!catched.empty())
			{
				std::for_each(catched.begin(), catched.end(), [](Villain& value) { value.set_is_catched(false); });
				std::vector<Villain> wanted = pair.second->selection([](Villain& value) { return !value.get_is_catched(); });
				pair.second->clear();
				pair.second->set(catched);
				pair.second->add(wanted.begin(), wanted.end());
			}
		}

	}
	if (!message.empty())
		std::cout << "Некоторым злодеям из тюрем " << message << " удалось сбежать!\n";
}

PrisonsMap::~PrisonsMap()
{
	std::fstream* prison_file = prisons_file;
	using path = std::experimental::filesystem::path;
	resize_file(path(prisons_file_name), 0);
	std::for_each(prisons.begin(), prisons.end(),
		[prison_file](std::pair<std::string, Prison*> pair)
		{
			*prison_file << pair.first << '\n';
			pair.second->~Prison();
			pair.second = nullptr;
		}
	);
	prisons_file->close();
	delete prisons_file;
	prison_file = nullptr;
	prisons_file = nullptr;
}

void PrisonsMap::save()
{
	std::fstream* prison_file = prisons_file;
	using path = std::experimental::filesystem::path;
	resize_file(path(prisons_file_name), 0);
	for (std::pair<const std::string, Prison*>& pair : prisons)
	{
		*prison_file << pair.first << '\n';
		pair.second->save();
	}
	prisons_file->clear();
	prisons_file->seekg(0);
	prisons_file->seekp(0);
	prison_file = nullptr;
}

std::map<std::string, Prison*>::iterator PrisonsMap::begin()
{
	return prisons.begin();
}

std::map<std::string, Prison*>::iterator PrisonsMap::end()
{
	return prisons.end();
}
std::map<std::string, Prison*>::iterator PrisonsMap::find(std::string key)
{
	return prisons.find(key);
}
Prison* PrisonsMap::at(std::string key)
{
	return prisons.at(key);
}
size_t PrisonsMap::erase(std::string key)
{
	return prisons.erase(key);
}

void PrisonsMap::insert(std::string prison_name, Prison* prison)
{
	prisons.insert(std::pair<std::string, Prison*>(prison_name, prison));
}