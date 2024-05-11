#include "threadsafe_stack.h"

void threadsave_stack::push(int first, int second)
{
	std::lock_guard<std::mutex> guard(mt);
	st.push({ first, second });
}

bool threadsave_stack::empty()
{
	return st.empty();
}

bool threadsave_stack::try_pop(std::pair<int, int>& pr)
{
	bool result = false;
	std::lock_guard<std::mutex> guard(mt);
	if (!st.empty())
	{
		result = true;
		pr = st.top();
		st.pop();
	}
	return result;
}
