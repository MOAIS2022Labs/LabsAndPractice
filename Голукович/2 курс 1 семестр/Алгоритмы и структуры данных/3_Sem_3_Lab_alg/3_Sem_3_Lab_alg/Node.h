#pragma once

struct NODE
{
	bool eow = false;
	NODE* ptrs[26];
	size_t count;
	NODE()
	{
		for (size_t i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
		count = 0;
	}
	~NODE()
	{

	}
};