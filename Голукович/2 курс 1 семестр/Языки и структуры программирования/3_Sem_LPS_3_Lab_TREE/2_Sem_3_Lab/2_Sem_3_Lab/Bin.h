#pragma once
#include "Error.h"
#include <fstream>
#include <iostream>

const int MAX = 100; //максимальное количество бит в числе
const char MAXBIN[] = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";

class Binary
{
private:
	int size; //размер числа в битах
	unsigned char bin[MAX]; //число, представленное в виде символов

	Binary plus(const Binary& num_r); //running ++
	Binary minus(const Binary& num_r); //running ++
	Binary multiplication(const Binary & num_r); //running ++
	Binary division(const Binary& num_r); //running ++
	Binary another_division(const Binary& num_r); //running ++
public:
	Binary(); //конструктор по умолчанию

	Binary(const Binary& num); //running ++   //коструктор
	Binary(const int SIZE); //running ++   //
	Binary(const char* num); //running ++   //
	Binary(std::istream& in);

	char* to_cstring();

	Binary& operator=(const Binary& num); //running ++   //
	Binary& operator+=(const Binary& num); //running ++   //
	Binary& operator-=(const Binary& num); //running ++   //
	Binary& operator*=(const Binary& num); //running ++   //
	Binary& operator/=(const Binary& num); //running ++   //
	Binary& operator%=(const Binary& num_r); //running ++   //

	Binary& operator++(); //running ++   //
	Binary& operator--(); //running ++   //
	//Binary& operator++(int rud); //running ++   //
	//Binary& operator--(int rud); //running ++   //
	
	friend std::ostream& operator<<(std::ostream& out, const Binary& num); //running ++   //
	friend std::istream& operator>>(std::istream& in, Binary& num); //not running //

	friend const Binary operator+(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const Binary operator-(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const Binary operator*(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const Binary operator/(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const Binary operator%(const Binary& num_l, const Binary& num_r); //running ++   //
	
	operator bool(); //running ++   //
	friend const bool operator!(const Binary& num); //running ++   //
	friend const bool operator==(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const bool operator!=(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const bool operator<=(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const bool operator>=(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const bool operator<(const Binary& num_l, const Binary& num_r); //running ++   //
	friend const bool operator>(const Binary& num_l, const Binary& num_r); //running ++   //
	//int get_size(); //running ++
};