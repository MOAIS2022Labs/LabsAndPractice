#pragma once
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>
#include "Deque.h"



class Time
{

private:

	short hour;
	short minute;
	short second;

	// ������� �� ������
	void from_seconds(short seconds);

public:
	// ������������� ����� ������ �� ���������� �������������
	void from_string(std::string str);

	Time();
	// ������������� �������
	Time(short hour, short minute, short second);
	// ������������� �������
	Time(std::string str_time);
	// ������������� ���������
	Time(short seconds);
	// ������������� ��������
	Time(tm& time);

	// ���������� �������� ����� ����� ��������� ������� � ��������
	short difference(Time time2);
	// ��������� �� ������� ������� ���������� ���������� ������
	void subtract_seconds(short seconds);
	// ���������� � ������� ������� ���������� ���������� ������
	void add_seconds(short seconds);

	// ��������� ���� �������� �������
	Time operator- (const Time& time2);
	// ��������� ������ �� �������
	Time operator- (const short sec);
	//�������� ���� �������� �������
	Time operator+ (const Time& time2);
	// �������� ������� � ������
	Time operator+	(const short sec);

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
	short to_seconds();
	//������� ������� � ������ (� ����������� �� ����� ������, � ������� ��������)
	short to_minutes();

	friend std::ostream& operator << (std::ostream& out, const Time& time);

	friend std::istream& operator >> (std::istream& in, Time& time);
};
