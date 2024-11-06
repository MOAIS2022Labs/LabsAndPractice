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

	// перевод из секунд
	void from_seconds(uShort seconds);

public:
	// инициализация полей класса из строкового представления
	void from_string(std::string str);

	Time();
	// инициализация числами
	Time(uShort hour, uShort minute, uShort second) :
		second(second), minute(minute), hour(hour) {}
	// инициализация строкой
	Time(std::string str_time);
	// инициализация секундами
	Time(uShort seconds);
	// инициализация временем
	Time(tm& time);

	// вычисление разности между двумя моментами времени в секундах
	uShort difference(Time time2);
	// вычитание из момента времени некоторого количества секунд
	void subtract_seconds(uShort seconds);
	// добавление к моменту времени некоторого количества секунд
	void add_seconds(uShort seconds);

	// вычитание двух моментов времени
	Time operator- (const Time& time2);
	// вычитание секунд из времени
	Time operator- (const uShort sec);
	//сложение двух моментов времени
	Time operator+ (const Time& time2);
	// сложение времени и секунд
	Time operator+	(const uShort sec);

	// сравнение двух моментов времени

	bool operator== (const Time& time2);
	bool operator!= (const Time& time2);
	bool operator> (const Time& time2);
	bool operator< (const Time& time2);
	bool operator>= (const Time& time2);
	bool operator<= (const Time& time2);

	// конвертация объекта в строку
	std::string to_string();
	// перевод времени в секунды
	uShort to_seconds();
	//перевод времени в минуты (с округлением до целой минуты, в сторону большего)
	uShort to_minutes();
};
