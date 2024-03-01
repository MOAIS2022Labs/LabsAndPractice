#include "PrintEdition.h"

void Book::print(std::ostream& out)
{
	out << "���������� � �����: \n"
		<< "������������: " << name << '\n'
		<< "���������� �������: " << pages << '\n'
		<< "������������: " << publishing_house << '\n'
		<< "�����: " << author << '\n'
		<< "����: " << genre << '\n'
		<< "��� ��������: " << binding_type << '\n';

}

void Magazine::print(std::ostream& out)
{
	out << "���������� � �������: \n"
		<< "������������: " << name << '\n'
		<< "���������� �������: " << pages << '\n'
		<< "������������: " << publishing_house << '\n'
		<< "�����: " << number << '\n'
		<< "���: " << year << '\n'
		<< "��� ����: " << web_site << '\n';
}
