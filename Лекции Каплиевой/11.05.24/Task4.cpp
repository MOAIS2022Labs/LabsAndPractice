#include <iostream>
#include <thread>
#include <Windows.h>
#include <atomic>

// Задача 4 по ЛР - механизмы синхронизации

volatile long ResourceInUse = false; // volatile - разделяемый ресурс
volatile long lock = 0;
std::atomic_bool alock = false;
std::atomic_flag aflag = ATOMIC_FLAG_INT;


// Данный пример показывает, в каком порядке потоки работают друг с другом
// без механизма синхронизации
// void thread_task(int ID)
// {
//     for (int i{}; i < 100; ++i)
//     {
//         for (int j{}; j < 50; ++j)
//             std::cout << ID;
//         std::cout << "\n";
//     }
// }


// Основные механизмы синхронизации
void thread_task_exchange(int ID)
{
    for (int i{}; i < 100; ++i)
    {
        while (_InterlockedExchange(&ResourceInUse, true))
            Sleep(0);

        // Зона критической секции
        // ------------------
        for (int j{}; j < 50; ++j)
            std::cout << ID;
        std::cout << "\n";
        // ------------------
        _InterlockedExchange(&ResourceInUse, false);
    }
}

void thread_task_compare_exchange(int ID)
{
    for (int i{}; i < 100; ++i)
    {
        while (_InterlockedCompareExchange(&lock, 1, 0) == 1)
            Sleep(0);

        // Зона критической секции
        // ------------------
        for (int j{}; j < 50; ++j)
            std::cout << ID;
        std::cout << "\n";
        // ------------------
        _InterlockedCompareExchange(&lock, 0, 1);
    }
}

// Механизмы через атомарные типы

void thread_task_atomic1(int ID)
{
    for (int i{}; i < 100; ++i)
    {
        while (alock.exchange(true))
            Sleep(0);

        // Зона критической секции
        // ------------------
        for (int j{}; j < 50; ++j)
            std::cout << ID;
        std::cout << "\n";
        // ------------------
        alock.store(false);
    }
}

void thread_task_atomic2(int ID)
{
    for (int i{}; i < 100; ++i)
    {
        while (aflag.test_and_set())
            Sleep(0);

        // Зона критической секции
        // ------------------
        for (int j{}; j < 50; ++j)
            std::cout << ID;
        std::cout << "\n";
        // ------------------
        aflag.clear();
    }
}

int main()
{
    // std::thread t1(thread_task, 1);
    // std::thread t2(thread_task, 2);

    // // Ждём потоки
    // t1.join();
    // t2.join();

    std::cin.get();
    return 0;
}