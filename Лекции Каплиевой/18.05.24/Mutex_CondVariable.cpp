#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>
#include <condition_variable>

// Шестая задача на многопоточку

class ThreadSafeQueue // Реализация потокобезопасного контейнера (на примере очереди)
{
private:
    std::mutex mutex; // Через мьютексы
    std::queue<int> queue;
public:
    void push(int elem, int ID)
    {
        std::lock_guard<std::mutex> locker(mutex); // Критическая секция, I guess?..
        queue.push(elem);
        std::cout << "Producer" << ID << "->" << elem << '\n';
    }

    bool try_pop(int& elem, int ID)
    {
        bool result = false;
        std::lock_guard<std::mutex> locker(mutex); // Willkommen in Kritikal Section
        if (!queue.empty())
        {
            result = true;
            elem = queue.front();
            queue.pop();
            std::cout << "Consumer" << ID << "<-" << elem << '\n';
        }
        else
            std::cout << "Consumer" << ID << " sleep\n";
        return result;
    }

    bool empty()
    {
        return queue.empty();
    }
};

// Пример работы с потокобезопасной очередью
ThreadSafeQueue TSQ;
std::mutex mut;
std::condition_variable cv;
volatile long volume_work_producer = 10;
volatile long volume_work_consumer = 10;

void task_producer(int ID)
{
    // цикл, в котором производители работают до полного выполнения работы
    while (volume_work_producer)
    {
        int elem = rand() % 100;
        std::this_thread::sleep_for(std::chrono::milliseconds(2)); // задержка времени
        // Зачем? Помним, что рандом генерирует число в зависимости от текущего времени;
        // наши числа генерятся очень быстро, поэтому нужно сделать задержку.
        TSQ.push(elem + ID, ID);
        cv.notify_all();
    }
}

void task_consumer(int ID)
{
    while (volume_work_consumer)
    {
        int elem;
        std::unique_lock<std::mutex> locker(mut);
        cv.wait_for(locker, std::chrono::seconds(5), []() {return !TSQ.empty(); });
        if (TSQ.try_pop(elem, ID))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        else
        {
            ++volume_work_consumer; // Так неправильно
        }
    }
}

int main()
{
    srand(GetTickCount());
    std::thread workers[5];
    for (int i{}; i < 5; ++i)
    {
        if (i < 2)
            workers[i] = std::thread(task_producer, i);
        else
            workers[i] = std::thread(task_consumer, i);
    }

    for (int i{}; i < 5; ++i)
    {
        workers[i].join(); // Барьерная синхронизация
    }

    std::cin.get();
    return 0;
}
