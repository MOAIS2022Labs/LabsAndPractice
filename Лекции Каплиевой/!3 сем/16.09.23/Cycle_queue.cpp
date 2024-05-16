#include "Cycle_queue.h"

// Реализация очереди с помощью кольцевого массива
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
    // Формула расчёта количества элементов по кольцу:
    return !empty() && (tail-head + MAX)%MAX + 1 == MAX; 
    //return count == MAX;
}

size_t Queue::size()
{
    return (tail-head + MAX)%MAX + 1;
    // return count;
}

void Queue::push(TInfo elem)
{
    if(!full())
    {
        tail = (tail + 1) % MAX; // Формула движения по кольцу
        elements[tail] = elem;
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
            head = (head+1)%MAX;
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
    for (int i = head; i != tail + 1; i=(i+1)%MAX)
        std::cout<<elements[i]<<' ';
    std::cout<<'\n';
}

/*
Распечатать содержимое файла, 
разделённого на строки, 
перенося числа из строк в начало, а остальные символы в конец.
*/

void print_queue(Queue& que)
{
    while(!que.empty())
    {
        std::cout<<que.front();
        que.pop();
    }
    std::cout<<'\n';
}
// модель работы с символами
// void print_lines(std::string file_name)
// {
//     std::ifstream file(file_name);
//     Queue que;
//     char c;
//     while(file.get(c))
//     {
//         if (c == '\n')
//             print_queue(que);
//         else
//         {
//             if (c >='0' && c <='9')
//                 std::cout<<c;
//             else
//                 que.push(c);
//         }
//     }
//     print_queue(que);
//     file.close();
// }


// модель работы со строковым потоком
void print_lines(std::string file_name)
{
    std::ifstream file(file_name);
    Queue que;
    char c;
    std::string line;
    std::stringstream ss;
    while(std::getline(file,line))
    {
        // ss << line; // 1 способ положить строку
        ss.str(line); // 2 способ
        while (ss.get(c))
        {
            if (c >='0' && c <='9')
                std::cout<<c;
            else
                que.push(c);
        }
        print_queue(que);
        ss.clear();
    }
    file.close();
}

int main()
{
    print_lines("data.txt");
    std::cin.get();
    return 0;
}
/*
Задачи на практику по очередям:
1. Дан файл, который содержит в каждой строчке одно слово.
Необходимо распечатать все слова максимальной длины в порядке, 
в каком они следуют в файле.

2. Генеалогическое древо. 
Есть матрица 5х5  и отдельный массив из 5 элементов.
В каждой ячейке массива есть имена. Матрица состоит из нулей и единиц.
По главной диагонали матрицы стоят нули.
Единица означает, что j-й столбец является потомком i-й строки.
Гарантируется правильность заполнения матрицы.
Необходимо распечатать генеалогическое древо, где в каждой строчке
распечатать потомков конкретного человека. 
Номеру строки/столбца соответсвует имя человека в массиве (по индексу).
*/