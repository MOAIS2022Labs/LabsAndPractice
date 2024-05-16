#include <iostream>
#include <future> // пример с библиотекой future
#include <Windows.h>

const size_t COUNT = 101;
const size_t NTHREADS = 4;

int sum(int *arr, size_t left, size_t right) // теперь задачу поткоа можно возвращать в виде результата
{
    // std::cout << "ID from C++ API:\t" << std::this_thread::get_id() << '\n'; // для просмотра сведений о потоке
    int result = 0;
    for (size_t i{left}; i < right; ++i)
        result += arr[i];
    return result;
}

int sum_parallel(int *arr)
{
    std::future<int> t[NTHREADS]; 
    size_t block = COUNT / NTHREADS;
    for (size_t i = 0; i < NTHREADS; ++i)
    {
        if (i != NTHREADS - 1) // если имеем дело не с последним потоком
            t[i] = std::async(std::launch::async, sum, arr, block * i, block * (i + 1)); // создаём его через конструктор std::thread
            // 1 параметр - создание асинхронной задачи для класса future,
            // без данного парамтера ОС сама будет принимать решения: создавать отдельный поток или нет.
            // Далее следует сама задача и её параметры 
        else
            t[i] =  std::async(std::launch::async, sum, arr, block * i, COUNT);
    }
    int global_sum = 0;
    for (size_t i{}; i< NTHREADS; ++i)
        global_sum += t[i].get();
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

    std::cout << "Non-parallel summ = " << 0 << "\n"; // сравнение с однопоточным кодом
    std::cout << "Parallel summ = " << sum_parallel(arr) << "\n";
    std::cin.get();
    return 0;
}