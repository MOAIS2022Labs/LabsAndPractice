#include <iostream>
#include <thread> // пример с библиотекой thread
#include <Windows.h>
/*
Обязательные условия для сдачи лабы:
1. Должен быть пример с непараллельным решением.
2. Дублировать данные (например, из массива) в другие структуры не надо.
*/

/*
Класс thread не умеет возвращать результаты, поэтому механизм
работы с потоком схож с работой WinAPI.
*/
const size_t COUNT = 101;
const size_t NTHREADS = 4;

void sum(int *arr, size_t left, size_t right, int &result)
{
    // std::cout << "ID from C++ API:\t" << std::this_thread::get_id() << '\n'; // для просмотра сведений о потоке
    result = 0;
    for (size_t i{left}; i < right; ++i)
        result += arr[i];
}

int sum_parallel(int *arr)
{
    std::thread t[NTHREADS];
    size_t block = COUNT / NTHREADS;
    int sum_result[NTHREADS];
    for (size_t i = 0; i < NTHREADS; ++i)
    {
        if (i != NTHREADS - 1) // если имеем дело не с последним потоком
            t[i].right = std::thread(sum, arr, block * i, block * (i + 1), std::ref(sum_result[i])); // создаём его через конструктор std::thread
            // 1 параметр - указатель на функцию задачи
            // после имени  задачи слеюдует список параметров этой функции;
            // параметры в констурктор thread всегда передаются по значению
        else
             t[i].right = std::thread(sum, arr, block * i, COUNT, std::ref(sum_result[i]));
    }

    // Main thread должен работать до join, чтобы начать параллельное программирование
    
    // А вот и то самое параллельное программирование
    for (size_t i{}; i < NTHREADS; ++i)
        if (!t[i].joinable()) // если не присоединились до этого к потоку
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

    std::cout << "Non-parallel summ = " << 0 << "\n"; // сравнение с однопоточным кодом
    std::cout << "Parallel summ = " << sum_parallel(arr) << "\n";
    std::cin.get();
    return 0;
}