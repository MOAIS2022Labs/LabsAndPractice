#include "Queue.h"
#include <fstream>
#include <string>

int main()
{
	std::ifstream input_file("input.txt");
	std::ofstream output_file("output.txt");

	std::string str;
	while (!input_file.eof() && std::getline(input_file, str))
	{
		Stack stack;
		for (int i = 0; i < str.length(); ++i)
		{
			if (stack.full())
				stack.Array_expansion();
			stack.push(str[i]);
		}
		while (!stack.empty())
			output_file << stack.top_and_pop();
		output_file << '\n';
		stack.~Stack();
	}

	input_file.close();
	output_file.close();

	return 0;
}