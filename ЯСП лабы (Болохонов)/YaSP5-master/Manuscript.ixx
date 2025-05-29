module;

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

export module Manuscript;

export enum manuscript_type { Tablet, Parchment, Scroll, Book };

export class Manuscript
{
private:
	manuscript_type type;
	std::string author;
	std::string text;
	std::chrono::year_month_day date;
    std::string type_to_string() const
    {
        switch (type)
        {
        case Tablet: return "Табличка";
        case Parchment: return "Пергамент";
        case Scroll: return "Свиток";
        case Book: return "Книга";
        }
    }
    bool read_type(std::istream& in)
    {
        std::string str{};
        in >> str;
        if (str == "Табличка")
        {
            type = Tablet;
            return true;
        }
        if (str == "Пергамент")
        {
            type = Parchment;
            return true;
        }
        if (str == "Свиток")
        {
            type = Scroll;
            return true;
        }
        if (str == "Книга")
        {
            type = Book;
            return true;
        }
        return false;
    }
public:
	Manuscript() {}
    Manuscript(const Manuscript& other)
    {
        this->text = other.text;
        this->author = other.author;
        this->type = other.type;
        this->date = other.date;
    }
	Manuscript(manuscript_type type, std::string author, std::chrono::year_month_day date, std::string text) :
		type(type), author(author), date(date), text(text) {}
	manuscript_type get_type() const { return type; }
	std::string get_author() const { return author; }
	std::string get_text() const { return text; }
	std::chrono::year_month_day get_date() const { return date; }
    
    friend std::ostream& operator<<(std::ostream& out, const Manuscript& manuscript)
    {
        out << manuscript.type_to_string() << '\n';
        out << manuscript.author << '\n';
        unsigned month = static_cast<unsigned>(manuscript.date.month());
        out << manuscript.date.year() << '-' << (month < 10 ? "0" : "") << month
            << '-' << manuscript.date.day() << '\n';
        out << manuscript.text << '\n';
        return out;
    }

    // type, author, date, text
    friend std::istream& operator>>(std::istream& in, Manuscript& manuscript) 
    {
        Manuscript tmp;
        std::string str{};

        if (!tmp.read_type(in)) {
            if (in.eof()) return in;
            throw std::invalid_argument("Недопустимое значение типа манускрипта\n");
        }

        // Проверка состояния потока перед ignore
        if (!in.ignore()) {
            throw std::ios_base::failure("Ошибка при пропуске символа после типа");
        }

        if (!std::getline(in, tmp.author)) {
            throw std::invalid_argument("Ошибка чтения автора");
        }

        std::chrono::from_stream(in, "%F", tmp.date);
        if (in.fail()) {
            throw std::invalid_argument("Недопустимое значение даты\n");
        }

        if (!in.ignore()) {
            throw std::ios_base::failure("Ошибка при пропуске символа после даты");
        }

        if (!std::getline(in, tmp.text)) {
            throw std::invalid_argument("Ошибка чтения текста");
        }

        manuscript = tmp;
        return in;
    }

    friend bool operator==(const Manuscript& lvalue, const Manuscript& rvalue)
    {
        return
            lvalue.text == rvalue.text &&
            lvalue.author == rvalue.author &&
            lvalue.type == rvalue.type &&
            lvalue.date == rvalue.date;
    }
	
    friend bool operator!=(const Manuscript& lvalue, const Manuscript& rvalue)
    {
        return (lvalue.text != rvalue.text ||
            lvalue.author != rvalue.author ||
            lvalue.type != rvalue.type ||
            lvalue.date != rvalue.date);
    }
};
