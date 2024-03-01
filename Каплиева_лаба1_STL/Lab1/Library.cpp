#include "Library.h"

Library::Library(std::string name, std::string fname) : name(name)
{
	std::string type{};
	std::ifstream file(fname);
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
			list.push_back(std::make_unique<Book>(name, pages, ph, author, genre, bt));
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
				list.push_back(std::make_unique<Magazine>(name, pages, ph, number, year, ws));
			}
	}
	file.close();
}

void Library::sort()
{
	auto compare = [](const std::unique_ptr<PrintEdition>& a, const std::unique_ptr<PrintEdition>& b)->bool
	{
		Magazine* ptr_a = dynamic_cast<Magazine*>(a.get());
		Magazine* ptr_b = dynamic_cast<Magazine*>(b.get());
		bool result = false;
		if (ptr_a && ptr_b)
			result = ptr_b->get_web_site() != "-" && ptr_a->get_web_site() == "-";
		else
			result = ptr_a && !ptr_b;
		return result;
	};
	list.sort(compare);
}

void Library::print(std::ostream& out)
{
	out << name << "\n---------------------------------\n";
	for (auto& elem : list)
	{
		elem->print(out);
		out << "---------------------------------\n";
	}
}
