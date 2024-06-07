#pragma once
#include <queue>
#include <Windows.h>
#include <process.h>

class ThreadsafeQueue
{

private:

	std::queue<std::pair<int, int>> que;
	HANDLE hSemaphore = CreateSemaphore(
		NULL,
		1,
		1,
		NULL);

public:

	bool empty();

	void push(int first, int second);

	bool try_pop(std::pair<int, int>& value);

	~ThreadsafeQueue()
	{
		CloseHandle(hSemaphore);
	}
};
