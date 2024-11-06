#pragma once
#include<iostream>

class Elem
{
private:
	char info;
	int key;
public:
	Elem(char info = '\0', int key = -1) : info(info), key(key) {}
	void make_rand(int n) { info = 'A' + rand() % 26; key = rand() % n; }
	bool operator==(const Elem& other) const { return key == other.key; }
	bool operator!=(const Elem& other) const { return key != other.key; }
	bool operator>(const Elem& other) const { return key > other.key; }
	bool operator<(const Elem& other) const { return key < other.key; }
	bool operator>=(const Elem& other) const { return key >= other.key; }
	bool operator<=(const Elem& other) const { return key <= other.key; }
	friend std::ostream& operator << (std::ostream& out, const Elem& elem)
	{
		out << '(' << elem.key << ", " << elem.info << ')';
		return out;
	}
};