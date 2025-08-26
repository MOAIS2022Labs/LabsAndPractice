#include <iostream> 
#include <fstream>
#include <string>
#include <Windows.h>

template <typename X>
struct Node {
	X info;
	Node* left;
	Node* right;
	Node() {}
	Node(X info, Node* left = nullptr, Node* right = nullptr) : info(info), left(left), right(right) {};
	~Node() { left = nullptr; right = nullptr; }
};

template <typename X>
using Tree = Node<X>*;

template <typename X>
int compare_X(X left_value, X right_value)
{
	int result;
	if (left_value < right_value)
		result = 1;
	if (left_value == right_value)
		result = 0;
	if (left_value > right_value)
		result = -1;
	return result;
}

template <typename X>
class BinaryTree {
private:
	Tree<X> root;
	//Tree<X> _build(std::ifstream& file);
	bool _add(Tree<X>& r, X element);
	void _clear(Tree<X>& t);
	void _find_delete_element(Tree<X>& r, Tree<X>& q);
	bool _delete(Tree<X>& t, X element);
	int _height(const Tree<X> t);
	int _size(const Tree<X> t);
	void _print(const Tree<X> t, const int level);
	void _print(const Tree<X> t, std::ofstream& file);
public:
	BinaryTree();
	BinaryTree(std::string name_of_file);
	~BinaryTree();
	bool empty();
	bool add(X element);
	bool remove(X element);
	Tree<X> search(X element);
	int height();
	int size();
	void print();
	void print(std::ofstream& file);
	void print(const Tree<X>& t);
};

template<typename X>
BinaryTree<X>::BinaryTree() { root = nullptr; }

template<typename X>
BinaryTree<X>::BinaryTree(const std::string name_of_file)
{
	std::ifstream file(name_of_file);
	X element;
	while (!file.eof())
	{
		file >> element;
		_add(this->root, element);
	}
	file.close();
}

template<typename X>
BinaryTree<X>::~BinaryTree()
{
	_clear(this->root);
}

//template<typename X>
//Tree<X> BinaryTree<X>::_build(std::ifstream& file)
//{
//	Tree<X> result = nullptr;
//	X element;
//	while (!file.eof())
//	{
//		file >> element;
//		_add_Element(result, element);
//	}
//	return result;
//}

template<typename X>
bool BinaryTree<X>::_add(Tree<X>& r, X element)
{
	bool result = false;
	if (!r)
	{
		r = new Node<X>(element);
		result = true;
	}
	else
	{
		switch (compare_X(r->info, element))
		{
		case 1:
			result = _add(r->right, element);
			break;
		case -1:
			result = _add(r->left, element);
			break;
		case 0:
			break;
		}
	}
	return result;
}

template<typename X>
void BinaryTree<X>::_clear(Tree<X>& t)
{
	if (t)
	{
		_clear(t->left);
		_clear(t->right);
		delete t;
		t = nullptr;
	}
}

template<typename X>
void BinaryTree<X>::_find_delete_element(Tree<X>& r, Tree<X>& q)
{
	if (r->right)
		_find_delete_element(r->right, q);
	else
	{
		q->info = r->info;
		q = r;
		r = r->left;
	}
}

template<typename X>
bool BinaryTree<X>::_delete(Tree<X>& t, X element)
{
	bool result = false;
	if (t)
	{
		switch (compare_X(t->info, element))
		{
		case 1:
			result = _delete(t->right, element);
			break;
		case -1:
			result = _delete(t->left, element);
			break;
		case 0:
		{
			result = true;
			Tree<X> q = t;
			if (!t->right)
				t = t->left;
			else
				if (!t->left)
					t = t->right;
				else
				{
					_find_delete_element(q->left, q);
				}
			delete q;
		}
		}
	}
	return result;
}

template<typename X>
int BinaryTree<X>::_height(const Tree<X> t)
{
	int result = 0;
	if (t)
	{
		int result_left, result_right;
		result_left = 1 + _height(t->left);
		result_right = 1 + _height(t->right);
		result = result_left > result_right ? result_left : result_right;
	}
	return result;
}

template<typename X>
int BinaryTree<X>::_size(const Tree<X> t)
{
	int result = 0;
	if (t)
		result = 1 + _size(t->left) + _size(t->right);
	return result;
}

template<typename X>
void BinaryTree<X>::_print(const Tree<X> t, const int level)
{
	if (t)
	{
		_print(t->right, level + 1);
		for (int i = 0; i < level; ++i)
			std::cout << "      ";
		std::cout << t->info << "\n\n";
		_print(t->left, level + 1);
	}
}

template<typename X>
void BinaryTree<X>::_print(const Tree<X> t, std::ofstream& file)
{
	if (t)
	{
		file << t->info << '\n';
		_print(t->left, file);
		_print(t->right, file);
	}
}

template<typename X>
bool BinaryTree<X>::empty()
{
	return !root;
}

template<typename X>
bool BinaryTree<X>::add(X element)
{
	return _add(this->root, element);
}

template<typename X>
bool BinaryTree<X>::remove(X element)
{
	bool result = _delete(this->root, element);
	return result;
}

template<typename X>
Tree<X> BinaryTree<X>::search(X element)
{
	Tree<X> t = this->root, result = nullptr;
	while (t && !result)
	{
		switch (compare_X(t->info, element))
		{
		case 1:
			t = t->right;
			break;
		case -1:
			t = t->left;
			break;
		case 0:
			result = t;
			break;
		}			
	}
	return result;
}

template<typename X>
int BinaryTree<X>::height()
{
	return _height(this->root);
}

template<typename X>
int BinaryTree<X>::size()
{
	return _size(this->root);
}

template<typename X>
void BinaryTree<X>::print()
{
	_print(this->root, 0);
}

template<typename X>
void BinaryTree<X>::print(const Tree<X>& t)
{
	_print(t, 0);
}

template<typename X>
void BinaryTree<X>::print(std::ofstream& file)
{
	_print(root, file);
}