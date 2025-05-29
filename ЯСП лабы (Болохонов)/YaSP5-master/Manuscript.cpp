#pragma once
#include "Manuscript.h"

std::string Manuscript::type_to_string() const
{
    switch (type)
    {
    case Tablet: return "Табличка";
    case Parchment: return "Пергамент";
    case Scroll: return "Свиток";
    case Book: return "Книга";
    }
}

bool Manuscript::read_type(std::istream& in)
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

Manuscript::Manuscript(const Manuscript& other)
{
    this->text = other.text;
    this->author = other.author;
    this->type = other.type;
    this->date = other.date;
}

std::ostream& operator<<(std::ostream& out, const Manuscript& manuscript)
{
    out << manuscript.type_to_string() << '\n';
    out << manuscript.author << '\n';
    unsigned month = static_cast<unsigned>(manuscript.date.month());
    out << manuscript.date.year() << '-' << (month < 10 ? "0" : "") << month
        << '-' << manuscript.date.day() << '\n';
    out << manuscript.text << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, Manuscript& manuscript) // type, author, date, text
{
    Manuscript tmp;
    std::string str{};
    if (!tmp.read_type(in))
    {
        if (in.eof())
            return in;
        throw std::invalid_argument("Недопустимое значение типа манускрипта\n");
    }
    in.ignore();
    std::getline(in, tmp.author);
    std::chrono::from_stream(in, "%F", tmp.date);
    if (in.fail())
        throw std::invalid_argument("Недопустимое значение даты\n");
    in.ignore();
    std::getline(in, tmp.text);
    manuscript = tmp;
    return in;
}

bool operator==(const Manuscript& lvalue, const Manuscript& rvalue)
{
    return
        lvalue.text == rvalue.text &&
        lvalue.author == rvalue.author &&
        lvalue.type == rvalue.type &&
        lvalue.date == rvalue.date;
}

bool operator!=(const Manuscript& lvalue, const Manuscript& rvalue) {
    return (lvalue.text != rvalue.text ||
        lvalue.author != rvalue.author ||
        lvalue.type != rvalue.type ||
        lvalue.date != rvalue.date);
}