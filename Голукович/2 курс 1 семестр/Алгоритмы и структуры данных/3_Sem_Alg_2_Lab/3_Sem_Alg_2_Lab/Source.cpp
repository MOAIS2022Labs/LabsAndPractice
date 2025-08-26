#include "BTree.h"
#include <Windows.h>
#include <stack>
#include <queue>
#include <sstream>

//bool task(BTree& btree);

bool is_leaf(const Tree& root);

void print_to_level(Tree root, int count, const int level);

Tree copy(const Tree& root);

void copy_without_leaves(BinTree source, BinTree& result);

void print_by_levels(BinTree& tree);

bool print_level(BinTree& drevo, int user_level);

TInfo task_rec(const Tree& root, Tree& t, const bool flag, bool& result)
{
	TInfo value = -1;
	if (t)
	{
		TInfo value_left = task_rec(root, t->left, flag, result);
		if (value_left != -1 && value_left > t->info)
			result = false;
		TInfo value_right;
		if (t == root)
			value_right = task_rec(root, t->right, true, result);
		else
			value_right = task_rec(root, t->right, flag, result);
		if (value_right != -1 && value_right < t->info)
			result = false;
		if (!flag)
		{
			if (value_left != -1 && (value_right == -1 || value_right != -1 && value_left > value_right) && value_left > t->info)
				value = value_left;
			if (value_right != -1 && (value_left == -1 || value_left != -1 && value_right > value_left) && value_right > t->info)
				value = value_right;
			if ((value_left == -1 || value_left != -1 && t->info > value_left) && (value_right == -1 || value_right != -1 && t->info > value_right))
				value = t->info;
		}
		else
		{
			if (value_left != -1 && (value_right == -1 || value_right != -1 && value_left < value_right) && value_left < t->info)
				value = value_left;
			if (value_right != -1 && (value_left == -1 || value_left != -1 && value_right < value_left) && value_right < t->info)
				value = value_right;
			if ((value_left == -1 || value_left != -1 && t->info < value_left) && (value_right == -1 || value_right != -1 && t->info < value_right))
				value = t->info;
		}
	}
	return value;
}

bool task_stack(BinTree& tree)
{
	bool result = true;
	if (tree.get_root())
	{
		std::stack<Tree> st;
		st.push(tree.get_root());
		Tree t;
		TInfo value = -1;
		bool flag = false;
		while (!st.empty())
		{
			t = st.top();
			st.pop();
			if (t == tree.get_root()->right)
				flag = true;
			if (t->left)
			{

			}
			else
			{
				if (t->right)
					st.push(t->right);
			}
		}
	}
	return result;
}

//int is_simple(int num) {
//	int result = num;
//	if (num < 2)
//		throw std::invalid_argument("Введено некорректное значение!");
//	for (int i = 2; i <= sqrt(num) && result == num; ++i) {
//		if (num % i == 0)
//			result = i;
//	}
//	return result;
//}
//
//int check_simple(int num)
//{
//	int result = -1;
//	try
//	{
//		result = is_simple(num);
//	}
//	catch (std::invalid_argument exception)
//	{
//		std::cout << exception.what();
//	}
//	return result;
//}

void task_ijfhn(int& lenght, int level, int* arr, Tree root)
{
	if (root)
	{
		if (root->info > arr[level])
			arr[level] = root->info;
		if (lenght == level + 1)
		{
			int* new_arr = new int[lenght + lenght / 2];
			for (int i = 0; i < lenght; ++i)
				new_arr[i] = arr[i];
			lenght = lenght + lenght / 2;
			delete[] arr;
			arr = new_arr;
			new_arr = nullptr;
		}
		task_ijfhn(lenght, level + 1, arr, root->left);
		task_ijfhn(lenght, level + 1, arr, root->right);
	}
}

Tree copy_without_leafs(Tree root)
{
	Tree new_root;
	if (root && (root->left || root->right))
	{
		new_root = new NODE(root->info);
		new_root->left = copy_without_leafs(root->left);
		new_root->right = copy_without_leafs(root->right);
	}
	else
		new_root = nullptr;
	return new_root;
}

Tree copy_with_leafs(Tree root)
{
	Tree new_root = nullptr;
	if (root)
	{
		new_root = new NODE(root->info);
		if (!root->left)
			new_root->left = new NODE(0);
		else
			new_root->left = copy_with_leafs(root->left);
		if (!root->right)
			new_root->right = new NODE(0);
		else
			new_root->right = copy_with_leafs(root->right);
	}
	return new_root;
}

int tree_height(int level, int& max, Tree root)
{
	int result = level;
	if (root)
	{
		if (root->left || root->right)
		{
			int left_height = tree_height(level + 1, max, root->left);
			int right_height = tree_height(level + 1, max, root->right);
			if (left_height > right_height)
				result = left_height;
			else
				result = right_height;
		}
	}
	return result;
}

// 4.1
void delete_leafs(BinTree& tree, Tree root)
{
	if (root)
	{
		if (root->left && !root->left->left && !root->left->right)
		{
			delete root->left;
			root->left = nullptr;
		}
		if (root->right && !root->right->left && !root->right->right)
		{
			delete root->right;
			root->right = nullptr;
		}
		delete_leafs(tree, root->left);
		delete_leafs(tree, root->right);
	}
}
//4.2
int sum_before_level(int cur_level, BinTree& tree)
{
	int result = 0;
	std::queue<Tree> que;
	que.push(tree.get_root());
	que.push(nullptr);
	int level = 0;
	while (!que.empty() && level < cur_level)
	{
		Tree t = que.front();
		que.pop();
		while (t)
		{
			result += t->info;
			if (t->left)
				que.push(t->left);
			if (t->right)
				que.push(t->right);
			t = que.front();
			que.pop();
		}
		que.push(nullptr);
		level += 1;
	}
	return result;
}
//3.1
void add_leafs(Tree root)
{
	if (root)
	{
		add_leafs(root->left);
		add_leafs(root->right);
		if (!root->left)
			root->left = new NODE(0);
		if (!root->right)
			root->right = new NODE(0);
	}
}
//3.2
int sum_before_odd(BinTree& tree)
{
	int result = 0;
	std::stack<Tree> st;
	st.push(tree.get_root());
	while (!st.empty())
	{
		Tree t = st.top();
		st.pop();
		if (t)
		{
			result += t->info;
			if (t->info % 2 != 0)
			{
				st.push(t->left);
				st.push(t->right);
			}
		}
	}
	return result;
}

int main()
{
	SetConsoleOutputCP(1251);
	std::ifstream file("tree_input_2.txt");
	if (file)
	{
		BinTree btree(file, false);
		if (btree.get_root())
		{
			btree.print(btree.get_root(), 0);

			// вариант 4
			// 
			// №1 ?
			// удаление листьев

			/*delete_leafs(btree, btree.get_root());
			btree.print(btree.get_root());*/

			// вариант 4
			//
			// №2 
			// сумма до заданного уровня

			//std::cout << sum_before_level(3, btree);

			// вариант 3
			// 
			// №1 
			// добавление листьев там, где возможно

			/*add_leafs(btree.get_root());
			btree.print(btree.get_root());*/

			//	вариант 3
			// 
			// №2
			// сумма по ветвям до первого четного

			//std::cout << sum_before_odd(btree);

			////рекурсия
			//bool result = true;
			//Tree t = btree.get_root();
			//task_rec(t, t, false, result);
			//if (result)
			//	std::cout << "yes";
			//else
			//	std::cout << "no";

			/*BinTree new_tree;
			new_tree.set_root(copy_with_leafs(btree.get_root()));
			new_tree.print(new_tree.get_root());*/

			/*int height = -1;
			std::cout << tree_height(0, height, btree.get_root());*/
			//std::cout << height;

			/*int lenght = 4;
			int* arr = new int[lenght];
			for (int i = 0; i < lenght; ++i)
				arr[i] = -1;
			task_ijfhn(lenght, 0, arr, btree.get_root());
			for (int i= 0; i < lenght; ++i)
				std::cout << arr[i] << '\n';*/
		}
		else
			std::cout << "Дерево пусто!\n";
	}
	else
		std::cout << "Ошибка файла!";
	file.close();
	std::cin.get();
	return 0;
}

bool is_leaf(const Tree& root)
{
	return !root->left && !root->right;
}

void print_to_level(Tree root, int count, const int level)
{
	if (count < level && root)
	{
		print_to_level(root->right, count + 1, level);
		for (int i = 0; i < count; ++i)
			std::cout << "  ";
		std::cout << root->info << '\n';
		print_to_level(root->left, count + 1, level);
	}
}

Tree copy(const Tree& root)
{
	Tree result = nullptr;
	auto IsLeaf = [](Tree root) -> bool
	{return !root->left && !root->right; };
	if (!IsLeaf(root))
	{
		result = new NODE(root->info);
		result->left = copy(root->left);
		result->right = copy(root->right);
	}
	return result;
}

void copy_without_leaves(BinTree source, BinTree& result)
{
	Tree root_source = source.get_root();
	Tree root_copy = copy(root_source);
	result.set_root(root_copy);
	//result.print(result.get_root());
}

void print_by_levels(BinTree& tree)
{
	Tree t = tree.get_root();
	std::queue <Tree> que;
	int level = 0;
	que.push(t);
	que.push(nullptr);
	while (!que.empty()) {
		std::cout << level << ": ";
		while (que.front()) {
			t = que.front();
			que.pop();
			std::cout << t->info << " ";
			if (t->left)
				que.push(t->left);
			if (t->right)
				que.push(t->right);
		}
		que.pop();
		std::cout << '\n';
		if (!que.empty())
			que.push(nullptr);
		++level;
	}
}


bool print_level(BinTree& drevo, int user_level)
{
	struct stTree
	{
		Tree ptr;
		int lev;
		stTree() {};
		stTree(Tree x, int y) : ptr(x), lev(y) {};
	};
	std::stack<stTree> st;
	Tree t = drevo.get_root();
	int current_lvl = 0;
	bool result = false;
	while (t && current_lvl <= user_level)
	{
		if (current_lvl == user_level)
		{
			std::cout << t->info << ' ';
			if (!st.empty())
			{
				t = st.top().ptr;
				current_lvl = st.top().lev;
				st.pop();
			}
			else
				t = nullptr;
			result = true;
		}
		else
		{
			if (t->left)
			{
				if (t->right)
					st.push(stTree(t->right, current_lvl + 1));
				t = t->left;
				current_lvl++;
			}
			else
			{
				if (t->right)
				{
					t = t->right;
					++current_lvl;
				}
				else {
					if (!st.empty())
					{
						t = st.top().ptr;
						current_lvl = st.top().lev;
						st.pop();
					}
					else
						t = nullptr;
				}
			}
		}
	}
	return result;
}

//void fill_queue(int result, std::queue<Tinfo>& que, BTree& tree, Tree root)
//{
//	int result = 0;
//
//	if (root)
//	{
//		que.push(root->info);
//		fill_queue(result, que, tree, root->left);
//		fill_queue(result, que, tree, root->right);
//		result += 1;
//	}
//}

//bool task(BTree& tree)
//{
//	bool result = true;
//	std::queue<Tinfo> que;
//	int count = 0;
//	fill_queue(count,que, tree, tree.get_ROOT());
//	int space = count;
//	for (int i = 0; i < count; ++i)
//	{
//		space = space / 2 - i + 1;
//		for (int k = 0; k < i; ++k)
//		{
//			for (int j = 0; j < space; ++j)
//				std::cout << " ";
//
//			std::cout << que.front();
//		}
//		std::cout << '\n';
//	}
//	return result;
//}