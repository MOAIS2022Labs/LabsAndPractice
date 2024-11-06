#pragma once
#include <iostream>
#include <fstream>
#include <string>


class PrintEdition
{
protected:

	std::string name{};
	size_t pages{};
	std::string publishing_house{};

public:

	PrintEdition(std::string name, size_t pages, std::string ph) :
		name(name), pages(pages), publishing_house(ph) {}

	virtual void print(std::ostream& out = std::cout) = 0;

	std::string get_name() const
	{
		return name;
	}
};

class Book : public PrintEdition
{
private:

	std::string author{};
	std::string genre{};
	std::string binding_type{};

public:

	Book(std::string name, size_t pages, std::string ph,
		std::string author, std::string genre, std::string bt) :
		PrintEdition(name, pages, ph), author(author),
		genre(genre), binding_type(bt) {}

	void print(std::ostream& out = std::cout);

};

class Magazine : public PrintEdition
{
private:

	size_t number{};
	size_t year{};
	std::string web_site{};

public:

	Magazine(std::string name, size_t pages, std::string ph,
		size_t number, size_t year, std::string web_site) :
		PrintEdition(name, pages, ph), number(number),
		year(year), web_site(web_site) {}

	void print(std::ostream& out = std::cout);

	std::string get_web_site()
	{
		return web_site;
	}
};