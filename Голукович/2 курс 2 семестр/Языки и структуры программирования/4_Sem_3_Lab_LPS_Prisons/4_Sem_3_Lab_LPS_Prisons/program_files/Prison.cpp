#include "Prison.h"

//методы класса

Prison::Prison(std::string name, std::fstream* prison_file) : prison_name(name), prison_file(prison_file)
{
	try
	{
		auto reader = std::istream_iterator<Villain>(*prison_file);
		prison.read(reader);
		if (prison.size() > 0)
			std::cout << "Файл " << prison_name << " успешно считан.\n";
		prison_file->clear();
		prison_file->seekg(0);
		prison_file->seekp(0);
	}
	catch (std::invalid_argument exception)
	{
		std::cout << "Файл " << prison_name << " считан с ошибкой! " << exception.what() << '\n';
	}
}

Prison::~Prison()
{
	save();
	prison_file->close();
	delete prison_file;
	prison_file = nullptr;
}

void Prison::save()
{
	using path = std::experimental::filesystem::path;
	resize_file(path(prison_name), 0);
	std::ostream_iterator<Villain> writer(*prison_file);
	prison.write(writer);
	prison_file->clear();
	prison_file->seekg(0);
	prison_file->seekp(0);
}

void Prison::rename(std::string new_prison_name)
{
	prison_file->close();
	delete prison_file;
	prison_file = nullptr;
	std::experimental::filesystem::path path = prison_name;
	std::experimental::filesystem::remove(path);
	prison_name = new_prison_name;
	prison_file = new std::fstream(prison_name, std::ios::in | std::ios::out | std::ios::trunc);
}

void Prison::print(std::ostream& out, std::string parser, bool flag)
{
	if (flag)
		out << "### " << prison_name << " ###\n\n";
	std::ostream_iterator<Villain> writer(out, parser.c_str());
	prison.write(writer);
}

std::string Prison::get_name() const
{
	return prison_name;
}

size_t Prison::size()
{ 
	return prison.size();
}

const Villain& Prison::at(size_t index)
{
	return prison.at(index);
}

void Prison::add(std::istream& in)
{
	std::istream_iterator<Villain> reader(in);
	prison.read(reader);
	in.clear();
}

void Prison::add(std::vector<Villain>::iterator begin, std::vector<Villain>::iterator end)
{
	for (auto iterator = begin; iterator != end; ++iterator)
		prison.add(*iterator);
}

Villain Prison::remove(size_t index)
{
	return prison.remove(index);
}

void Prison::edit(size_t index, const Villain& villain)
{
	prison.edit(index, villain);
}

std::vector<Villain> Prison::selection(std::function<bool(Villain&)> selector)
{
	return prison.selection(selector);
}

void Prison::set(std::vector<Villain>& selected)
{
	prison.set(selected);
}

Villain Prison::get_last()
{
	return prison.get_last();
}

std::vector<Villain> Prison::clear()
{
	return prison.clear();
}