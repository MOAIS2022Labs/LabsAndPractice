#include "BTree.h"

Tree build_balance(std::ifstream& file, int count)
{
	Tree result = nullptr;
	if (count)
	{
		int count_left = count / 2;
		int count_right = count - count_left - 1;
		result = new NODE;
		file >> result->info;
		result->left = build_balance(file, count_left);
		result->right = build_balance(file, count_right);
	}
	return result;
}

Tree build_binary(std::ifstream& file)
{
	Tree result = nullptr;
	TInfo x;
	if (file >> x)
	{
		if (x != -1)
		{
			result = new NODE;
			result->info = x;
			result->left = build_binary(file);
			result->right = build_binary(file);
		}
	}
	return result;
}

BinTree::BinTree(std::ifstream& file, const bool flag)
{
	if (flag)
	{
		int count;
		file >> count;
		root = build_balance(file, count);
	}
	else
		root = build_binary(file);
}

void BinTree::print(Tree t, int level)
{
	if (t)
	{
		print(t->right, level + 1);
		for (int i = 1; i <= level; ++i)
			std::cout << "  ";
		std::cout << t->info << '\n';
		print(t->left, level + 1);
	}
}

void BinTree::clear(Tree& t)
{
	if (t)
	{
		clear(t->left);
		clear(t->right);
		delete t;
		t = nullptr;
	}
}

BinTree::~BinTree()
{
	clear(root);
}