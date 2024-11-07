#include <iostream>
#include <Windows.h>
#include <process.h>
#include <thread>
#include <future>
#include <queue>
#include <concrt.h>
#include <omp.h>

#include <fstream>

const size_t HEIGHT = 11;
const size_t WIDTH = 23;
const int A = -100, B = 100;
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
			/*
			if (i == HEIGHT - 1 && j == WIDTH - 1)
				*(matrix + i * WIDTH + j) = 102400;
			else
			*/	*(matrix + i * WIDTH + j) = rand() % b + a;
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
	std::cout << "Количество     " << elem_count_parallel << "              " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "              " << max_dividers_count_non_parallel << '\n';
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
	std::cout << "Количество     " << elem_count_parallel << "              " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "              " << max_dividers_count_non_parallel << '\n';
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
	std::cout << "Количество     " << elem_count_parallel << "              " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "              " << max_dividers_count_non_parallel << '\n';
}




std::atomic_flag atomic_flag_task_4 = ATOMIC_FLAG_INIT;

void task_4_count(int* arr, size_t lines_count, std::pair<size_t, size_t>& global_result)
{
	size_t local_elem_count = 0;
	size_t local_max_dividers_count = 0;
	size_t dividers_count = 0;
	for (size_t i = 0; i < WIDTH * lines_count; ++i)
	{
		dividers_count = find_dividers_count(*(arr + i));
		if (dividers_count == local_max_dividers_count)
			local_elem_count++;
		if (dividers_count > local_max_dividers_count)
		{
			local_max_dividers_count = dividers_count;
			local_elem_count = 1;
		}
	}

	if (local_max_dividers_count >= global_result.second)
	{
		while (atomic_flag_task_4.test_and_set())
			Sleep(0);

		if (local_max_dividers_count == global_result.second)
			global_result.first += local_elem_count;
		if (local_max_dividers_count > global_result.second)
		{
			global_result.first = local_elem_count;
			global_result.second = local_max_dividers_count;
		}

		atomic_flag_task_4.clear();
	}
}

size_t task_4_parallel(int* matrix, size_t& max_dividers_count)
{
	std::thread threads[THREADS_COUNT - 1];
	size_t k = HEIGHT / (THREADS_COUNT - 1);
	std::pair<size_t, size_t> global_result(0, 0);
	for (size_t i = 0; i < THREADS_COUNT - 1; ++i)
		threads[i] = std::thread(task_4_count, matrix + i * k * WIDTH, k, std::ref(global_result));
	task_4_count(matrix + (THREADS_COUNT - 1) * k * WIDTH, HEIGHT % (THREADS_COUNT - 1), global_result);

	for (size_t i = 0; i < THREADS_COUNT - 1; ++i)
			threads[i].join();

	max_dividers_count = global_result.second;
	return global_result.first;
}

void task_4(int* matrix)
{
	size_t max_dividers_count_parallel = 0;
	size_t elem_count_parallel = task_4_parallel(matrix, max_dividers_count_parallel);
	size_t max_dividers_count_non_parallel = 0;
	size_t elem_count_non_parallel = task_non_parallel(matrix, max_dividers_count_non_parallel);

	std::cout << "\n\nthread with critical section\n           Параллельно   Не параллельно\n";
	std::cout << "Количество     " << elem_count_parallel << "              " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "              " << max_dividers_count_non_parallel << '\n';
}





class ThreadSafeQueue
{
private:
	std::queue<std::pair<int*, size_t>> queue;
	concurrency::critical_section critical_section;
public:

	void push(int* first, size_t second)
	{
		critical_section.lock();
		queue.push({ first, second });
		critical_section.unlock();
	}

	bool try_pop(std::pair<int*, size_t>& pr)
	{
		bool result = false;
		critical_section.lock();
		if (!queue.empty())
		{
			result = true;
			pr = queue.front();
			queue.pop();
		}
		critical_section.unlock();
		return result;
	}

	bool empty()
	{
		return queue.empty();
	}

};

ThreadSafeQueue queue;
std::atomic_flag atomic_flag_task_5 = ATOMIC_FLAG_INIT;

void task_5_threadsafequeue_count(std::pair<size_t, size_t>& global_result)
{
	while (!queue.empty())
	{
		std::pair<int*, size_t> tmp;
		if (queue.try_pop(tmp))
		{
			size_t local_elem_count = 0;
			size_t local_max_dividers_count = 0;
			size_t dividers_count = 0;
			for (size_t i = 0; i < WIDTH * tmp.second; ++i)
			{
				dividers_count = find_dividers_count(*(tmp.first + i));
				if (dividers_count == local_max_dividers_count)
					local_elem_count++;
				if (dividers_count > local_max_dividers_count)
				{
					local_max_dividers_count = dividers_count;
					local_elem_count = 1;
				}
			}

			if (local_max_dividers_count >= global_result.second)
			{
				while (atomic_flag_task_5.test_and_set())
					Sleep(0);

				if (local_max_dividers_count == global_result.second)
					global_result.first += local_elem_count;
				if (local_max_dividers_count > global_result.second)
				{
					global_result.first = local_elem_count;
					global_result.second = local_max_dividers_count;
				}

				atomic_flag_task_5.clear();
			}
		}
	}
}

size_t task_5_threadsafequeue(int* matrix, size_t& max_dividers_count)
{
	std::thread threads[THREADS_COUNT - 1];
	std::pair<size_t, size_t> global_pair(0, 0);
	const size_t NBLOCKS = 5;
	size_t lines_count = HEIGHT / NBLOCKS;
	for (size_t i = 0; i < NBLOCKS; ++i)
		queue.push(matrix + i * WIDTH * lines_count, i < NBLOCKS - 1 ? lines_count : lines_count + HEIGHT % NBLOCKS);

	for (size_t i = 0; i < THREADS_COUNT - 1; ++i)
		threads[i] = std::thread(task_5_threadsafequeue_count, std::ref(global_pair));

	task_5_threadsafequeue_count(global_pair);

	for (size_t i = 0; i < THREADS_COUNT - 1; ++i)
		threads[i].join();

	max_dividers_count = global_pair.second;
	return global_pair.first;
}

void task_5(int* matrix)
{
	size_t max_dividers_count_parallel = 0;
	size_t elem_count_parallel = task_5_threadsafequeue(matrix, max_dividers_count_parallel);
	size_t max_dividers_count_non_parallel = 0;
	size_t elem_count_non_parallel = task_non_parallel(matrix, max_dividers_count_non_parallel);

	std::cout << "\n\nthread with thread safe queue\n           Параллельно   Не параллельно\n";
	std::cout << "Количество     " << elem_count_parallel << "              " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "              " << max_dividers_count_non_parallel << '\n';
}




ThreadSafeQueue TSQ;
std::mutex mut;
std::condition_variable cv;
volatile long volume_work_producer = 3;
volatile long volume_work_consumer = 7;

void task_producer(int ID)
{
	// цикл, в котором производители работают до полного выполнения работы
	while (_InterlockedExchangeAdd(&volume_work_producer, -1) > 0)
	{
		int* matrix = new int[HEIGHT*WIDTH];
		for (size_t i = 0; i < HEIGHT; ++i)
			for (size_t j = 0; j < WIDTH; ++j)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(3));
				*(matrix + i*WIDTH + j) = rand() % 100;
				std::this_thread::sleep_for(std::chrono::milliseconds(2));
			}
		TSQ.push(matrix, HEIGHT);
		std::cout << "P: " << ID << '\n';
		cv.notify_all();
	}
}

void task_consumer(int ID)
{
	while (_InterlockedExchangeAdd(&volume_work_consumer, -1) > 0)
	{
		std::pair<int*, size_t> elem;
		std::unique_lock<std::mutex> locker(mut);
		cv.wait_for(locker, std::chrono::seconds(5), []() {return !TSQ.empty(); });
		if (TSQ.try_pop(elem))
		{
			int* matrix = elem.first;
			size_t elem_count;
			size_t max_dividers_count = 0;
			for (size_t i = 0; i < HEIGHT; ++i)
				for (size_t j = 0; j < WIDTH; ++j)
					elem_count = task_non_parallel(matrix, max_dividers_count);
			delete matrix;

			std::cout << "C: " << ID << ": " << elem_count << ' ' << max_dividers_count << '\n';
		}
		else
			_InterlockedExchangeAdd(&volume_work_consumer, 1);
	}
}

int main2()
{
	srand(GetTickCount());
	std::thread workers[5];

	for (int i{}, j = 0; i < 5; ++i)
	{
		if (i < 2)
		{
			workers[i] = std::thread(task_producer, i);
			j++;
		}
		else
			workers[i] = std::thread(task_consumer, i);
	}

	for (int i{}; i < 5; ++i)
	{
		workers[i].join(); // Барьерная синхронизация
	}

	return 0;
}




size_t task_7_thread_task(int* arr, size_t lines_count, size_t& max_dividers_count)
{
	size_t local_elem_count = 0;
	size_t local_max_dividers_count = 0;
	size_t dividers_count = 0;
	for (size_t i = 0; i < WIDTH * lines_count; ++i)
	{
		dividers_count = find_dividers_count(*(arr + i));
		if (dividers_count == local_max_dividers_count)
			local_elem_count++;
		if (dividers_count > local_max_dividers_count)
		{
			local_max_dividers_count = dividers_count;
			local_elem_count = 1;
		}
	}
	max_dividers_count = local_max_dividers_count;
	return local_elem_count;
}

size_t task_7_omp(int* matrix, size_t& max_dividers_count)
{
	size_t global_elem_count = 0;
	size_t global_max_dividers_count = 0;
	//хз не работает(работает не так как надо)
#pragma omp parallel for shared(matrix, global_elem_count, global_max_dividers_count)
		for (int i = 0; i < HEIGHT; ++i)
		{
			size_t local_max_dividers_count = 0;
			size_t local_elem_count = task_7_thread_task(matrix + i * WIDTH, 1, local_max_dividers_count);
			if (local_max_dividers_count == global_max_dividers_count)
				global_elem_count += local_elem_count;
			if (local_max_dividers_count > global_max_dividers_count)
			{
				global_max_dividers_count = local_max_dividers_count;
				global_elem_count = local_elem_count;
			}
		}

	max_dividers_count = global_max_dividers_count;
	return global_elem_count;
}

void task_7(int* matrix)
{
	size_t max_dividers_count_parallel = 0;
	size_t elem_count_parallel = task_7_omp(matrix, max_dividers_count_parallel);
	size_t max_dividers_count_non_parallel = 0;
	size_t elem_count_non_parallel = task_non_parallel(matrix, max_dividers_count_non_parallel);

	std::cout << "\n\nOpenMP\n           Параллельно   Не параллельно\n";
	std::cout << "Количество     " << elem_count_parallel << "              " << elem_count_non_parallel << '\n';
	std::cout << "Делители       " << max_dividers_count_parallel << "              " << max_dividers_count_non_parallel << '\n';
}




int main3()
{
	SetConsoleOutputCP(1251);
	srand(GetTickCount());

	int matrix[WIDTH][HEIGHT];
	init_matrix(&matrix[0][0], A, B);

	/*task_1(*matrix);
	std::cout << "\n---------------------------------------\n";

	task_2(*matrix);
	std::cout << "\n---------------------------------------\n";

	task_3(*matrix);
	std::cout << "\n---------------------------------------\n";

	task_4(*matrix);
	std::cout << "\n---------------------------------------\n";*/

	/*task_5(*matrix);
	std::cout << "\n---------------------------------------\n";*/

	/*task_6(*matrix);
	std::cout << "\n---------------------------------------\n";*/

	task_7(*matrix);
	std::cout << "\n---------------------------------------\n";

	return 0;
}



#include <thread>
#include <atomic>

const size_t HEIGHT = 15;
const size_t WIDTH = 15;
const size_t NTHREADS = 4;

int sum_row(int* row)
{
	int result{};
	for (int i = 0; i < WIDTH; ++i)
		result += *(row + i);
	return result;
}

volatile unsigned long lock = 0;

void thread_task_find_max_sum_row(int* arr, int left, int right, int& global_sum, int& global_row)
{
	int local_row{ left };
	int local_sum = sum_row(arr + left * WIDTH);
	for (int i = left + 1; i < right; ++i)
	{
		int tmp = sum_row(arr + i * WIDTH);
		if (tmp > local_sum)
		{
			local_sum = tmp;
			local_row = i;
		}
	}
	if (local_sum > global_sum)
	{
		while (_InterlockedCompareExchange(&lock, 1, 0) == 1)
			Sleep(0);
		if (local_sum > global_sum)
		{
			global_sum = local_sum;
			global_row = local_row;
		}
		else if (local_sum == global_sum && local_row < global_row)
			global_row = local_row;
		_InterlockedCompareExchange(&lock, 0, 1);
	}
}

int find_max_sum_row_parallel(int* matrix)
{
	std::thread t[NTHREADS - 1];
	int block = HEIGHT / NTHREADS;
	int global_row{}, global_max_sum{};
	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i] = std::thread(thread_task_find_max_sum_row, matrix, block * i, block * (i + 1), std::ref(global_max_sum), std::ref(global_row));

	thread_task_find_max_sum_row(matrix, block * (NTHREADS - 1), HEIGHT, global_max_sum, global_row);

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].join();

	return global_row;
}

void init_matrix(int* matrix)
{
	for (size_t i = 0; i < HEIGHT; ++i)
	{
		for (size_t j = 0; j < WIDTH; ++j)
		{
			*(matrix + i * WIDTH + j) = rand() % 100;
			//std::cout << *(matrix + i * WIDTH + j) << '\t';
		}
		//std::cout << '\n';
	}
	//std::cout << '\n';
}

int find_max_sum_row_non_parallel(int* matrix)
{
	int result{};
	int max_sum = sum_row(matrix);
	for (size_t i = 1; i < HEIGHT; ++i)
	{
		int tmp = sum_row(matrix + i * WIDTH);
		if (tmp > max_sum)
		{
			max_sum = tmp;
			result = i;
		}
	}
	return result;
}

//void print_array(int* arr)
//{
//	for (size_t i = 0; i < COUNT; ++i)
//		std::cout << arr[i] << ' ';
//	std::cout << '\n';
//}

int main()
{

	for (int i = 0; i < 100; ++i)
	{
		srand(GetTickCount() + i);
		int matrix[HEIGHT][WIDTH];
		init_matrix(&matrix[0][0]);
		int a = find_max_sum_row_non_parallel(&matrix[0][0]);
		int b = find_max_sum_row_parallel(&matrix[0][0]);
		if (a != b)
		{
			std::cout << "NOOOOOO\n";
			break;
		}
		//std::cout << "non parallel = " << a << '\n';
		//std::cout << "parallel = " << b << '\n';
		//std::cout << "-----------------------------\n";
	}
	return 0;
}