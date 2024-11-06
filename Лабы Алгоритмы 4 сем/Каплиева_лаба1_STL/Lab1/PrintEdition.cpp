#include "PrintEdition.h"

void Book::print(std::ostream& out)
{
	out << "Информация о книге: \n"
		<< "Наименование: " << name << '\n'
		<< "Количество страниц: " << pages << '\n'
		<< "Издательство: " << publishing_house << '\n'
		<< "Автор: " << author << '\n'
		<< "Жанр: " << genre << '\n'
		<< "Вид переплёта: " << binding_type << '\n';

}

void Magazine::print(std::ostream& out)
{
	out << "Информация о журнале: \n"
		<< "Наименование: " << name << '\n'
		<< "Количество страниц: " << pages << '\n'
		<< "Издательство: " << publishing_house << '\n'
		<< "Номер: " << number << '\n'
		<< "Год: " << year << '\n'
		<< "Веб сайт: " << web_site << '\n';
}
