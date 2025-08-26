#include "TrieTree.h"
#include <Windows.h>

bool task(TrieTree& tree, Tree root, std::string set)
{
	bool result = false;
	if (set.empty())
		result = true;
	if (root && !result)
	{
		for (size_t i = 0; i < 26; ++i)
		{
			if (root->ptrs[i])
			{
				size_t char_index = set.find(i + 'a');
				std::string new_set = set;
				if (char_index != std::string::npos)
					new_set.erase(char_index, 1);
				if (task(tree, root->ptrs[i], new_set))
				{
					tree.clear(root->ptrs[i]);
					root->count -= 1;
				}
			}
		}
		if (root->count == 0 && !root->eow)
			result = true;
	}
	return result;
}

int main()
{
	SetConsoleOutputCP(1251);
	TrieTree tree("words.txt");
	if (!tree.empty())
	{
		tree.print(tree.get_root());
		std::cout << "---\n";
		tree.print_los(tree.get_root());
		std::string set = "bckj";
		task(tree, tree.get_root(), set);
		std::cout << "---\n";
		if (!tree.empty())
		{
			tree.print(tree.get_root());
			std::cout << "---\n";
			tree.print_los(tree.get_root());
		}
		else
			std::cout << "Дерево пусто!";
	}
	else
		std::cout << "Дерево пусто!";

	std::cin.get();
	return 0;
}