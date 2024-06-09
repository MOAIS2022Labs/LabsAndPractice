#include <iostream>
#include <Windows.h>

const int n = 5;
int map[n][n]
{
    1, 1, 0, 4, 0,
    0, 1, 0, 0, 0,
    1, 0, 1, 0, 0,
    0, 0, 1, 1, 0,
    1, 1, 0, 1, 1
};

bool reachable[n];

void Try(int start)
{
    for (int j = 0; j < n; ++j)
    {
        if (map[start][j] != 0 && !reachable[j])
        {
            reachable[j] = true;
            Try(j);
        }
    } 
}

int main()
{
	SetConsoleOutputCP(1251);
    int start;
    std::cout << "¬ведите стартовую точку: ";
    std::cin >> start;
    --start;
    for (int i = 0; i < n; ++i)
        reachable[i] = false;
    Try(start);
    for (int i = 0; i < n; ++i)
        if (!reachable[i])
            std::cout << i + 1 << ' ';
	return 0;
}