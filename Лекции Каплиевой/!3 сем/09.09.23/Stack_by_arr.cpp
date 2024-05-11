#include "Stack_by_arr.h"

Stack::Stack()
{
    head = -1;
    count = 0;
}

bool Stack::empty()
{
    return head == -1;
    //return count == 0;
}

bool Stack::full()
{
    return head == MAX;
}

size_t Stack::size()
{
    //return count;
    return head+1;
}

void Stack::push(TInfo elem)
{
    elements[++head] = elem;
    count++;
}

void Stack::pop()
{
    head--;
    count--;
}

TInfo Stack::top()
{
    return elements[head];
}

void Stack::view()
{
    for (int i = head; i>=0; --i)
        std::cout<<  elements[i] << ' ';
    std::cout<<'\n';
}

/*
Условие задачи:
Вычислить формулу вида: 
<формула>::=<цифра | M(<формула>, <формула>) | m(<формула>,<формула>) >,
где цифра - это число от 0 до 9, M - max, m - min.
Написать программу, которая вычисляет заданную формулу. 
Гарнтируется, что формула записана верно.
Пример: m(3,M(7,9)) = 3.

*/

int Calculate(std::string file_name)
{
    std::ifstream file(file_name);
    Stack st;
    char c;
    while (file.get(c))
    {
        if (c == 'M' || c == 'm' || c >= '0' && c<='9')
            st.push(c);
        else
            if (c==')')
            {
                TInfo x = st.top(); 
                st.pop();
                TInfo y = st.top(); 
                st.pop();
                TInfo oper = st.top(); 
                st.pop();
                switch(oper)
                {
                    case 'M':
                        st.push(x>y ? x : y);
                        break;
                    case 'm':
                        st.push(x<y ? x : y);
                        break;
                }
            
            }
    }
    file.close();
    return st.top()-'0';
}

int main()
{
    std::cout<<Calculate("input.txt");
    std::cin.get();
    return 0;
}

