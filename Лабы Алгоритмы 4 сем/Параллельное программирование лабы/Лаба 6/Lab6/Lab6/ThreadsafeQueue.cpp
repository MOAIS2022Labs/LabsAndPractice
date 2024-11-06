#include "ThreadsafeQueue.h"

bool ThreadsafeQueue::empty()
{
    return que.empty();
}

void ThreadsafeQueue::push(int* arr)
{
    WaitForSingleObject(hSemaphore, INFINITE);
    try
    {
        que.push(arr);
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
    catch(std::exception)
    {
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
}

bool ThreadsafeQueue::try_pop(int*& value)
{
    bool result = false;
    WaitForSingleObject(hSemaphore, INFINITE);
    try
    {
        if (!que.empty())
        {
            result = true;
            value = que.front();
            que.pop();
        }
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
    catch (std::exception)
    {
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
    return result;
}
