#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric> // для accumulate
#include <sstream>

// вывести на экран значения элементов заданного диапазона
template <typename T>
void print_values(const T& x)
{
	for (auto it = std::cbegin(x); it != std::cend(x); ++it)
		std::cout << *it << ' ';
}
// для map
template <typename TKey, typename TValue>
void print_values(const std::map<TKey, TValue> m)
{
	for (const auto& [k, v] : m)
		std::cout << k << ": " << v << '\n';
}

// в обратном порядке
template <typename T>
void print_values_reverse(const T& x)
{
	for (auto it = std::crbegin(x); it != std::crend(x); ++it)
		std::cout << *it << ' ';
}

std::pair<float, float> get_point()
{
	return { 1.f, 2.f };
}

using some_tuple = std::tuple<int, std::string, float>;

std::tuple<int, std::string, float> t{ 1, "One", 1.f };

// вывести только чётные элементы заданного диапазона в обратном порядке
template <typename T>
void print_even_values_reverse(T x)
{
	std::for_each(std::crbegin(x), std::crend(x),
		[](auto x)
		{
			if (x % 2 == 0)
				std::cout << x << ' ';
		});
}

// объединить все строки в заданном диапазоне в одно значение
std::string concat(const std::vector<std::string>& vec)
{
	std::string result;
	std::for_each(std::cbegin(vec), std::cend(vec),
		[&result](const auto& s)
		{
			result += s;
		});
	return result;
}

// посчитать количество слов разделнных пробелом в тексте
int count_words(const std::string& str)
{
	int count{};
	std::stringstream ss(str);
	std::string word;
	while (ss >> word)
		++count;
	return count;
}

int main()
{

	std::vector<int> v{ 1,2,3 , 4, 5 ,6, 7, 8 };
	print_even_values_reverse(v);
	std::cout << '\n';
	/*const auto [x, y] = get_point();
	const auto [i, s, f] = some_tuple();*/

	std::vector<std::string> words{ "Loren", " ", "ipsum", " ", "dolor"," ", "sit", " ", "amet" };
	std::cout << concat(words) << '\n';
	// а можно через accumulate
	std::cout << std::accumulate(std::cbegin(words), std::cend(words), std::string{}) << '\n';

	std::string text = concat(words);
	std::cout << count_words(text) << '\n';

	// в современных плюсах не так. std::range сила!

	return 0;
}