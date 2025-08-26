#pragma once
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>

using Tree = NODE*;

struct TrieTree
{
private:

	Tree root;
	void add_word(Tree& root, const std::string& word, size_t i = 0);
	bool all_ptrs_empty(const Tree& root);
	void del_word(Tree& root, const std::string& word, size_t i = 0);
	std::string find_los(const Tree& root);

public:

	TrieTree();
	TrieTree(const std::string& fname);
	~TrieTree();

	bool empty();
	void clear();
	void clear(Tree& root);
	void add(const std::string& word);
	void del(const std::string& word);
	void print(const Tree& root, std::string word = "");
	void print_los(const Tree& root);
	

	Tree get_root();
	void set_root(Tree source);

	void del_words_with_letters(Tree& t, const std::string& set, std::string word = "");
	void del_with_letters(const std::string& set);

};