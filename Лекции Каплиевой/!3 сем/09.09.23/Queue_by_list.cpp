#include "Queue_by_list.h"

Queue::Queue()
{
    head = tail = nullptr;
    count = 0;
}

bool Queue::empty()
{
    return head == nullptr;
    // return count == 0;
}

size_t Queue::size()
{
    return count;
}

void Queue::push(TInfo elem)
{
    if (empty())
    {
        head = new NODE(elem);
        tail = head;
    }
    else
    {
        tail->next = new NODE(elem);
        tail = tail->next;
    }
    count++;
}

void Queue::pop()
{
    ptrNODE ptr = head;
    head = head->next;
    delete ptr;
    count--;
}

TInfo Queue::front()
{
    return head->info;
}

TInfo Queue::back()
{
    return tail->info;
}

void Queue::view()
{
    ptrNODE ptr;
    while (ptr)
    {
        std::cout<<ptr->info<<' ';
        ptr = ptr->next;
    }
    std::cout<<"\n";
}

void Queue::clear()
{
    while(!empty())
        pop();
}

Queue::~Queue()
{
    clear();
}
