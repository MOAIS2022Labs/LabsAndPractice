#pragma once
#include <string>
#include <time.h>


using uShort = unsigned short;


class Time
{

private:

	uShort hour;
	uShort minute;
	uShort second;

	// ������� �� ������
	void from_seconds(uShort seconds);

public:
	// ������������� ����� ������ �� ���������� �������������
	void from_string(std::string str);

	Time();
	// ������������� �������
	Time(uShort hour, uShort minute, uShort second) :
		second(second), minute(minute), hour(hour) {}
	// ������������� �������
	Time(std::string str_time);
	// ������������� ���������
	Time(uShort seconds);
	// ������������� ��������
	Time(tm& time);

	// ���������� �������� ����� ����� ��������� ������� � ��������
	uShort difference(Time time2);
	// ��������� �� ������� ������� ���������� ���������� ������
	void subtract_seconds(uShort seconds);
	// ���������� � ������� ������� ���������� ���������� ������
	void add_seconds(uShort seconds);

	// ��������� ���� �������� �������
	Time operator- (const Time& time2);
	// ��������� ������ �� �������
	Time operator- (const uShort sec);
	//�������� ���� �������� �������
	Time operator+ (const Time& time2);
	// �������� ������� � ������
	Time operator+	(const uShort sec);

	// ��������� ���� �������� �������

	bool operator== (const Time& time2);
	bool operator!= (const Time& time2);
	bool operator> (const Time& time2);
	bool operator< (const Time& time2);
	bool operator>= (const Time& time2);
	bool operator<= (const Time& time2);

	// ����������� ������� � ������
	std::string to_string();
	// ������� ������� � �������
	uShort to_seconds();
	//������� ������� � ������ (� ����������� �� ����� ������, � ������� ��������)
	uShort to_minutes();
};
