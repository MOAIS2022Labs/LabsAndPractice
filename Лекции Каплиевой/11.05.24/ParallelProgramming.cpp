#include <iostream>
#include <thread> // пример с библиотекой thread
#include <Windows.h>

const size_t COUNT = 101;
const size_t NTHREADS = 4;

void sum(int *arr, size_t left, size_t right, int &global_sum)
{
    int local_sum = 0;
    for (size_t i{left}; i < right; ++i)
        local_sum += arr[i];
    _InterlockedExchangeAdd(&global_sum, local_sum); // Пример с функцией InterlockedExchange
}

int sum_parallel(int *arr)
{
    std::thread t[NTHREADS];
    size_t block = COUNT / NTHREADS;
    int sum_result[NTHREADS];
    for (size_t i = 0; i < NTHREADS; ++i)
    {
        if (i != NTHREADS - 1) // если имеем дело не с последним потоком
            t[i] = std::thread(sum, arr, block * i, block * (i + 1), std::ref(sum_result[i])); // создаём его через конструктор std::thread
        else
             t[i] = std::thread(sum, arr, block * i, COUNT, std::ref(sum_result[i]));
    }

  
    for (size_t i{}; i < NTHREADS; ++i)
        t[i].join(); // заставляем потоки ждать через функцию присоединения (join)
    // После этого гарантируется, что все дочерние функции сложены в массив результатов

    int global_sum = 0;
    for (size_t i{}; i< NTHREADS; ++i)
        global_sum += sum_result[i];
    return global_sum;
}

void init_array(int *arr)
{
    srand(GetTickCount());
    for (size_t i = 0; i < COUNT; ++i)
        arr[i] = rand() % 100;
}

int main()
{
    int arr[COUNT];
    init_array(arr);
    std::cout << "Parallel summ = " << sum_parallel(arr) << "\n";
    std::cin.get();
    return 0;
}