#include <iostream>
#include <process.h>
#include <Windows.h>

/*
Разберём первые три задачи на потоки:
1. С помощью WinApi (CreateThread + beginthreadex)
2. C++ thread
3. C++ future (асинхронное программирование)
*/

const size_t COUNT = 101;
const size_t NTHREADS = 4;

// информационная структура для нашей задачи
using INFORM = struct
{
    int *a;
    size_t left, right;
    int sum = 0; // наша локальная сумма для задачи
};

/*Задача потока должна иметь предопределённую сигнатуру:*/
unsigned __stdcall sum(void *arg) // с двумя подчёркиваниями
{
    std::cout << " Id from WinAPI: " << ::GetCurrentThreadId() << '\n'; // учесть, что печать информации о потоке идёт асинхронно
    // решение: использовать механизмы синхронизации (изучены будут позже)
    INFORM *inform = (INFORM *)arg;
    inform->sum = 0;
    for (size_t i = inform->left; i < inform->right; ++i)
        inform->sum += inform->a[i];
    _endthreadex(0);
    return 0;
}

int sum_parallel(int *arr)
{
    // Сначала создадим массив потоков
    // Каждый поток характеризуется дескриптором, и называется он хэндлером (указатель на поток);
    // хэндлер (физически) - это структура, которая хранит информацию о потоке.
    HANDLE t[NTHREADS];
    unsigned ThreadID[NTHREADS];
    size_t block = COUNT / NTHREADS;
    INFORM inform[NTHREADS];
    for (size_t i = 0; i < NTHREADS; ++i)
    {
        inform[i].a = arr;
        inform[i].left = block * i;
        inform[i].sum = 0;
        if (i != NTHREADS - 1)
            inform[i].right = block * (i + 1);
        else
            inform[i].right = COUNT;
        t[i] = (HANDLE)_beginthreadex(nullptr, 0, &sum, &inform[i], 0, &ThreadID[i]);
        // первый параметр - это ссылка на дочерние потоки;
        // второй параметр - это stack size для решения задачи;
        // третий параметр - это задача потока (start adress), т.е. где хранится задача потока;
        // четвёртый параметр - список данных;
        // пятый параметр - флаг инициализации (0 - сразу в активном состоянии, 1 - запустить потом)
    }
    WaitForMultipleObjects(NTHREADS, t, true, INFINITE);
    // 1 - сколько объектов считать
    // 2 - массив хэндлеров
    // 3 - ждать одного (false) или всех (true)
    // 4 - время ожидания (в мс): INIFNITE - бесконечно додгое ожидание
    int global_sum = 0;
    for (size_t i = 0; i < NTHREADS; ++i)
        global_sum += inform[i].sum; // из нашей информационной структуры берём полученные даннные
    for (size_t i = 0; i < NTHREADS; ++i)
        CloseHandle(t[i]);
    return global_sum;
}

void init_array(int* arr)
{
    srand(GetTickCount());
    for (size_t i = 0; i < COUNT; ++i)
        arr[i] = rand() % 100;
}

int main()
{
    int arr[COUNT];
    init_array(arr);

    std::cout<< "Non-parallel summ = " << 0 << "\n"; // сравнение с однопоточным кодом
    std::cout << "Parallel summ = " << sum_parallel(arr) << "\n";
    std::cin.get();
    return 0;
}