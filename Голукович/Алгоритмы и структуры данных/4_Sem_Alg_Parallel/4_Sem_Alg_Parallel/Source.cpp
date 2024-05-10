#include <iostream>
#include <Windows.h>
#include <process.h>
#include <thread>
#include <future>

const size_t HEIGHT = 13;
const size_t WIDTH = 23;
const size_t THREADS_COUNT = 4;

struct INFORM
{
	int* arr;
	size_t lines_count;
	size_t elem_count = 0;
	size_t max_dividers_count = 0;
};

void init_matrix(int* matrix, int a, int b)
{
	for (size_t i = 0; i < HEIGHT; ++i)
	{
		for (size_t j = 0; j < WIDTH; ++j)
		{
			
			if (i == HEIGHT - 1 && j == WIDTH - 1)
				*(matrix + i * WIDTH + j) = 102400;
			else
				*(matrix + i * WIDTH + j) = rand() % b + a;
			std::cout << *(matrix + i * WIDTH + j) << " ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

size_t find_dividers_count(int elem)
{
	size_t result = 2;
	int max = std::abs(elem) / 2;
	for (int i = 2; i <= max; ++i)
		if (elem % i == 0)
			result++;
	return result;
}

size_t task_non_parallel(int* matrix, size_t& max_dividers_count)
{
	size_t elem_count = 0;
	max_dividers_count = 0;

	for (int i = 0; i < HEIGHT * WIDTH; ++i)
	{
		size_t local_max_dividers_count = find_dividers_count(*(matrix + i));
		if (max_dividers_count == local_max_dividers_count)
			elem_count++;
		if (max_dividers_count < local_max_dividers_count)
		{
			elem_count = 1;
			max_dividers_count = local_max_dividers_count;
		}
	}

	return elem_count;
}




unsigned __stdcall task_1_count(void* args)
{
	INFORM* inform = (INFORM*)args;
	size_t local_elem_count = 0;
	size_t local_max_dividers_count = 0;
	size_t local_dividers_count = 0;
	size_t local_lines_count = inform->lines_count;
	for (size_t i = 0; i < WIDTH * local_lines_count; ++i)
	{
		local_dividers_count = find_dividers_count(*(inform->arr + i));
		if (local_dividers_count == local_max_dividers_count)
			local_elem_count++;
		if (local_dividers_count > local_max_dividers_count)
		{
			local_max_dividers_count = local_dividers_count;
			local_elem_count = 1;
		}
	}
	inform->elem_count = local_elem_count;
	inform->max_dividers_count = local_max_dividers_count;
	if (local_lines_count != HEIGHT % (THREADS_COUNT - 1))
		_endthreadex(0);
	return 0;
}

size_t task_1_parallel(int* matrix, size_t& max_dividers_count)
{
	HANDLE threads[THREADS_COUNT - 1];
	INFORM inform[THREADS_COUNT];
	size_t k = HEIGHT / (THREADS_COUNT - 1);
	for (size_t i = 0; i < THREADS_COUNT; ++i)
	{
		inform[i].arr = matrix + (k * i) * WIDTH;
		//std::cout << *(inform[i].arr) << " ";
		if (i < THREADS_COUNT - 1)
		{
			inform[i].lines_count = k;
			threads[i] = (HANDLE)_beginthreadex(nullptr, 0, &task_1_count, &inform[i], 0, nullptr);
		}
		else
			inform[i].lines_count = HEIGHT % (THREADS_COUNT - 1);
	}
	std::cout << '\n';
	task_1_count(inform + THREADS_COUNT - 1);
	WaitForMultipleObjects(THREADS_COUNT - 1, threads, true, INFINITE);

	size_t elem_count = 0;
	max_dividers_count = 0;
	for (size_t i = 0; i < THREADS_COUNT; ++i)
	{
		if (i < THREADS_COUNT - 1)
			CloseHandle(threads[i]);
		if (max_dividers_count == inform[i].max_dividers_count)
			elem_count += inform[i].elem_count;
		if (max_dividers_count < inform[i].max_dividers_count)
		{
			max_dividers_count = inform[i].max_dividers_count;
			elem_count = inform[i].elem_count;
		}
	}

	return elem_count;
}

void task_1(int* matrix)
{
	size_t max_dividers_count_parallel = 0;
	size_t elem_count_parallel = task_1_parallel(matrix, max_dividers_count_parallel);
	size_t max_dividers_count_non_parallel = 0;
	size_t elem_count_non_parallel = task_non_parallel(matrix, max_dividers_count_non_parallel);

	std::cout << "\n\nWinAPI\n           Параллельно   Не параллельно\n";
	std::cout << "Количество       " << elem_count_parallel << "          " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "          " << max_dividers_count_non_parallel << '\n';
}





void task_2_count(int* arr, size_t lines_count, std::pair<size_t, size_t>& result)
{
	size_t elem_count = 0;
	size_t max_dividers_count = 0;
	size_t dividers_count = 0;
	for (size_t i = 0; i < WIDTH * lines_count; ++i)
	{
		dividers_count = find_dividers_count(*(arr + i));
		if (dividers_count == max_dividers_count)
			elem_count++;
		if (dividers_count > max_dividers_count)
		{
			max_dividers_count = dividers_count;
			elem_count = 1;
		}
	}
	result = std::pair<size_t, size_t>(elem_count, max_dividers_count);
}

size_t task_2_parallel(int* matrix, size_t& max_dividers_count)
{
	std::thread threads[THREADS_COUNT - 1];
	size_t k = HEIGHT / (THREADS_COUNT - 1);
	std::pair<size_t, size_t> pairs[THREADS_COUNT];
	for (size_t i = 0; i < THREADS_COUNT - 1; ++i)
		if (i < THREADS_COUNT - 1)
			threads[i] = std::thread(task_2_count, matrix + i * k * WIDTH, k, std::ref(pairs[i]));
	task_2_count(matrix + (THREADS_COUNT - 1) * k * WIDTH, HEIGHT % (THREADS_COUNT - 1), pairs[THREADS_COUNT - 1]);

	size_t elem_count = 0;
	max_dividers_count = 0;
	for (size_t i = 0; i < THREADS_COUNT; ++i)
	{
		if (i < THREADS_COUNT - 1)
			threads[i].join();
		if (max_dividers_count == pairs[i].second)
			elem_count += pairs[i].first;
		if (max_dividers_count < pairs[i].second)
		{
			max_dividers_count = pairs[i].second;
			elem_count = pairs[i].first;
		}
	}
	return elem_count;
}

void task_2(int* matrix)
{
	size_t max_dividers_count_parallel = 0;
	size_t elem_count_parallel = task_2_parallel(matrix, max_dividers_count_parallel);
	size_t max_dividers_count_non_parallel = 0;
	size_t elem_count_non_parallel = task_non_parallel(matrix, max_dividers_count_non_parallel);

	std::cout << "\n\nthread\n           Параллельно   Не параллельно\n";
	std::cout << "Количество       " << elem_count_parallel << "          " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "          " << max_dividers_count_non_parallel << '\n';
}




std::pair<size_t, size_t> task_3_count(int* arr, size_t lines_count)
{
	std::pair<size_t, size_t> result;
	size_t elem_count = 0;
	size_t max_dividers_count = 0;
	size_t dividers_count = 0;
	for (size_t i = 0; i < WIDTH * lines_count; ++i)
	{
		dividers_count = find_dividers_count(*(arr + i));
		if (dividers_count == max_dividers_count)
			elem_count++;
		if (dividers_count > max_dividers_count)
		{
			max_dividers_count = dividers_count;
			elem_count = 1;
		}
	}
	result.first = elem_count;
	result.second = max_dividers_count;
	return result;
}

size_t task_3_parallel(int* matrix, size_t& max_dividers_count)
{
	std::future<std::pair<size_t, size_t>> threads[THREADS_COUNT - 1];
	size_t k = HEIGHT / (THREADS_COUNT - 1);
	std::pair<size_t, size_t> pairs[THREADS_COUNT];
	for (size_t i = 0; i < THREADS_COUNT - 1; ++i)
		threads[i] = std::async(std::launch::async, task_3_count, matrix + i * k * WIDTH, k);
	pairs[THREADS_COUNT - 1] = task_3_count(matrix + (THREADS_COUNT - 1) * k * WIDTH, HEIGHT % (THREADS_COUNT - 1));
	
	size_t elem_count = 0;
	max_dividers_count = 0;
	for (size_t i = 0; i < THREADS_COUNT; ++i)
	{
		if (i < THREADS_COUNT - 1)
			pairs[i] = threads[i].get();
		if (max_dividers_count == pairs[i].second)
			elem_count += pairs[i].first;
		if (max_dividers_count < pairs[i].second)
		{
			max_dividers_count = pairs[i].second;
			elem_count = pairs[i].first;
		}
	}
	return elem_count;
}

void task_3(int* matrix)
{
	size_t max_dividers_count_parallel = 0;
	size_t elem_count_parallel = task_3_parallel(matrix, max_dividers_count_parallel);
	size_t max_dividers_count_non_parallel = 0;
	size_t elem_count_non_parallel = task_non_parallel(matrix, max_dividers_count_non_parallel);

	std::cout << "\n\nfuture\n           Параллельно   Не параллельно\n";
	std::cout << "Количество       " << elem_count_parallel << "          " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "          " << max_dividers_count_non_parallel << '\n';
}



int main()
{
	SetConsoleOutputCP(1251);
	srand(GetTickCount());

	int matrix[WIDTH][HEIGHT];
	int a = -100, b = 100;
	init_matrix(&matrix[0][0], a, b);

	task_1(&matrix[0][0]);
	std::cout << "\n----------------\n";

	task_2(&matrix[0][0]);
	std::cout << "\n----------------\n";

	task_3(&matrix[0][0]);
	std::cout << "\n----------------\n";
	
	return 0;
}