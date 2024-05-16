#include "Stack_by_list.h"

Stack::Stack()
{
    head = nullptr;
    count = 0;
}

bool Stack::empty()
{
    return head == nullptr;
    // 2 вариант: return count == 0;
}

size_t Stack::size()
{
    return count;
}

void Stack::push(TInfo elem)
{
    // по адресу head создать новый узел:
    head = new NODE(elem, head);
    count++;
}

void Stack::pop()
{
    // Запомнить адрес удаляемого элемента, исключить элемент, память освободить:
    ptrNODE ptr = head;
    head = head->next;
    delete ptr;
    count--;
}

TInfo Stack::top()
{
    return head->info;
}

void Stack::view()
{
    ptrNODE ptr = head;
    while (ptr)
    {
        std::cout << ptr->info << ' ';
        ptr = ptr->next;
    }
    std::cout<<'\n';
}

void Stack::clear()
{
    while(!empty())
    {
        pop();
    }
}

Stack::~Stack()
{
    clear();
}

int main()
{
    Stack st;
    for (int i = 1; i <= 5; ++i)
        st.push(i);
    st.view();
    std::cin.get();
    return 0;
}