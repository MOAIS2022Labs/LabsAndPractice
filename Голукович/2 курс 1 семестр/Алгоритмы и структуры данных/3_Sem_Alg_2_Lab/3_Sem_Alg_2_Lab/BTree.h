#pragma once
#include <iostream>
#include <fstream>

using TInfo = int;

struct NODE
{
	TInfo info;
	NODE* left, * right;
	NODE() {};
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) : info(info), left(left), right(right) {}
	~NODE() { left = right = nullptr; }
};

using Tree = NODE*;

struct BinTree
{
private:
	Tree root;
public:
	BinTree() {};
	BinTree(std::ifstream& file, const bool flag);
	void print(Tree root, int level = 0);
	void clear(Tree& root);
	Tree get_root() { return root; }
	void set_root(Tree new_root) { root = new_root; }
	~BinTree();
};