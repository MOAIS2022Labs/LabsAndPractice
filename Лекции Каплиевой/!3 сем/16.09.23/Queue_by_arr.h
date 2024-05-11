#pragma once
#include <iostream>

const int MAX = 100;

using TInfo = int;
using Array = TInfo[MAX];

struct Queue
{
private:
    Array elements;
    size_t count; // Необязательный элемент
    int head, tail;
public:
    Queue();
    bool empty();
    bool full();
    size_t size();
    void push(TInfo elem);
    void pop();
    TInfo front();
    TInfo back();
    void view();
};