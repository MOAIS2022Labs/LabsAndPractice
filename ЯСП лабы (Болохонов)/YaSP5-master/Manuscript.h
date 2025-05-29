#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

class Manuscript
{
private:
	enum manuscript_type { Tablet, Parchment, Scroll, Book };
	manuscript_type type;
	std::string author;
	std::string text;
	std::chrono::year_month_day date;
	std::string type_to_string() const;
	bool read_type(std::istream& in);
public:
	Manuscript() {}
	Manuscript(const Manuscript& other);
	Manuscript(manuscript_type type, std::string author, std::chrono::year_month_day date, std::string text) :
		type(type), author(author), date(date), text(text) {}
	manuscript_type get_type() const { return type; }
	std::string get_author() const { return author; }
	std::string get_text() const { return text; }
	std::chrono::year_month_day get_date() const { return date; }
	friend std::ostream& operator<<(std::ostream& out, const Manuscript& manuscript);
	friend std::istream& operator>>(std::istream& in, Manuscript& manuscript); // type, author, date, text
	friend bool operator==(const Manuscript& lvalue, const Manuscript& rvalue);
	friend bool operator!=(const Manuscript& lvalue, const Manuscript& rvalue);
};