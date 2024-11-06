#include "ThreadsafeQueue.h"

bool ThreadsafeQueue::empty()
{
    return que.empty();
}

void ThreadsafeQueue::push(int first, int second)
{
    WaitForSingleObject(hSemaphore, INFINITE);
    try
    {
        que.push({ first, second });
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
    catch(std::exception)
    {
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
}

bool ThreadsafeQueue::try_pop(std::pair<int, int>& value)
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
