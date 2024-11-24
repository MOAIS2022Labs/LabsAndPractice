namespace OS_Lab1.Model
{
    public class ThreadSafeBuffer<T>
    {
        private Stack<T> _threadSafeStack = new();
        private int _maxBufferSize;
        private Semaphore _maxSizeSemaphore;
        private Semaphore _emptySemaphore;
        private Mutex _mutex = new();
        public int Id { get; }

        public ThreadSafeBuffer(int maxBufferSize, int id)
        {
            _maxBufferSize = maxBufferSize;
            _maxSizeSemaphore = new(_maxBufferSize, _maxBufferSize);
            _emptySemaphore = new(0, _maxBufferSize);
            Id = id;
        }

        public void Push(T value)
        {
            _maxSizeSemaphore.WaitOne();
            _mutex.WaitOne();
            _threadSafeStack.Push(value);
            _emptySemaphore.Release();
            _mutex.ReleaseMutex();
        }

        public void Pop(ref T value)
        {
            _emptySemaphore.WaitOne();
            _mutex.WaitOne();
            value = _threadSafeStack.Pop();
            _maxSizeSemaphore.Release();
            _mutex.ReleaseMutex();
        }

        public void Clear()
        {
            _threadSafeStack.Clear();
            _maxBufferSize = 0;
            _mutex.Dispose();
            _emptySemaphore.Dispose();
            _maxSizeSemaphore.Dispose();
        }
    }
}
