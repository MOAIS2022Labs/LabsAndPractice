#pragma once

#include <iostream>

using Tinfo = char;
using Array = char*;

struct Stack
{
private:
	int max;
	Array elements;
	size_t count;
	int head;
public:
	Stack();
	bool empty();
	bool full();
	void Array_expansion();
	size_t size();
	void push(Tinfo elem);
	//void pop();
	Tinfo top_and_pop();
	~Stack();
};