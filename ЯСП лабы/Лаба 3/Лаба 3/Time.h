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

	// перевод из секунд
	void from_seconds(short seconds);

public:
	// инициализация полей класса из строкового представления
	void from_string(std::string str);

	Time();
	// инициализация числами
	Time(short hour, short minute, short second);
	// инициализация строкой
	Time(std::string str_time);
	// инициализация секундами
	Time(short seconds);
	// инициализация временем
	Time(tm& time);

	// вычисление разности между двумя моментами времени в секундах
	short difference(Time time2);
	// вычитание из момента времени некоторого количества секунд
	void subtract_seconds(short seconds);
	// добавление к моменту времени некоторого количества секунд
	void add_seconds(short seconds);

	// вычитание двух моментов времени
	Time operator- (const Time& time2);
	// вычитание секунд из времени
	Time operator- (const short sec);
	//сложение двух моментов времени
	Time operator+ (const Time& time2);
	// сложение времени и секунд
	Time operator+	(const short sec);

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
	short to_seconds();
	//перевод времени в минуты (с округлением до целой минуты, в сторону большего)
	short to_minutes();

	friend std::ostream& operator << (std::ostream& out, const Time& time);

	friend std::istream& operator >> (std::istream& in, Time& time);
};
