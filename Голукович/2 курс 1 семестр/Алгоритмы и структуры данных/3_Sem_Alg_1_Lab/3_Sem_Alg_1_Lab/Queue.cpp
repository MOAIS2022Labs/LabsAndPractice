#include "Queue.h"

Stack::Stack()
{
	max = 4;
	elements = new Tinfo[max];
	head = -1;
	count = 0;
}

bool Stack::empty()
{
	return head == -1;
}

bool Stack::full()
{
	return head == max - 1;
}

void Stack::Array_expansion()
{
	Array new_elements = new Tinfo[max * 2];
	for (int i = 0; i < max; ++i)
		new_elements[i] = elements[i];
	delete[] elements;
	elements = new_elements;
	new_elements = nullptr;
	max = max * 2;
}

size_t Stack::size()
{
	return head + 1;
}

void Stack::push(Tinfo elem)
{
	elements[++head] = elem;
	count += 1;
}

//void Stack::pop()
//{
//	
//}

Tinfo Stack::top_and_pop()
{
	head--;
	count--;
	return elements[head + 1];
}

Stack::~Stack()
{
	delete[] elements;
	elements = nullptr;
}