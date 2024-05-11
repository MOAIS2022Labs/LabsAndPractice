#pragma once
#include <stack>
#include <mutex>

class threadsave_stack
{
private:

	std::stack<std::pair<int, int>> st;
	std::mutex mt;

public:

	void push(int first, int second);

	bool try_pop(std::pair<int, int>& pr);

	bool empty();

};
