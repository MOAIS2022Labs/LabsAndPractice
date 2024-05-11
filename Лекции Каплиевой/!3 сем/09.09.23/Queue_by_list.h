/*
Очередь - структура, работающая по принципу FIFO.
*/
#pragma once
#include <iostream>

using TInfo = int;

struct NODE
{
    TInfo info;
    NODE* next;
    NODE(TInfo info, NODE* ptr = nullptr) : info(info), next(ptr) {}
    ~NODE()
    {
        next = nullptr;
    }
};

using ptrNODE = NODE*;


struct Queue
{
private:
    ptrNODE head, tail;
    size_t count;
public:
    Queue();
    bool empty();
    size_t size();
    void push(TInfo elem);
    void pop();
    TInfo front();
    TInfo back();
    void view();
    void clear();
    ~Queue();
};