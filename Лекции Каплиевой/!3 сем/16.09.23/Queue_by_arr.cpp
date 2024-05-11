#include "Queue_by_arr.h"

Queue::Queue()
{
    head = 0;
    tail = -1;
    count = 0;
}

bool Queue::empty()
{
    return tail == -1;
    // return count == 0;
}

bool Queue::full()
{
    return tail-head+1 == MAX;
    //return count == MAX;
}

size_t Queue::size()
{
    return tail - head + 1;
    // return count;
}

void Queue::push(TInfo elem)
{
    if(!full())
    {
        if (tail == MAX - 1)
        {
            for (int i = head; i < tail; ++i)
                elements[i-head] = elements[i];
            tail = tail - head;
            head = 0;
        }
        elements[++tail] = elem;
        count++;
    }
}

void Queue::pop()
{
    if (!empty())
    {
        if (head == tail)
        {
            head = 0;
            tail = -1;
        }
        else
            head++;
        count--;
    }
}

TInfo Queue::front()
{
    TInfo elem = 0;
    if (!empty())
        elem = elements[head];
    else
        std::cout<<"Queue is empty!\n";
    return elem;
}

TInfo Queue::back()
{
    TInfo elem = 0;
    if (!empty())
        elem = elements[tail];
    else
        std::cout<<"Queue is empty!\n";
    return elem;
}

void Queue::view()
{
    for (int i = head; i <= tail; ++i)
        std::cout<<elements[i]<<' ';
    std::cout<<'\n';
}



int main()
{
    /*
    Пример задачи с очередью: 
    Дан файл с целыми числами.
    Распечатать значения в диапазоне от заданных A и В.
    */
    Queue que;
    for (int i = 1; i <= 5; ++i)
        que.push(i);
    que.view();


    std::cin.get();
    return 0;
}
