#pragma once
#include <iostream>
#include <fstream>
#include <string>


const size_t MAX = 100;

using TInfo = char;
using Array = TInfo[MAX];

struct Stack
{
private:
    Array elements;
    size_t count;
    int head;
public:
    Stack();
    bool empty();
    bool full();
    size_t size();
    void push(TInfo size);
    void pop();
    TInfo top();
    void view();
};