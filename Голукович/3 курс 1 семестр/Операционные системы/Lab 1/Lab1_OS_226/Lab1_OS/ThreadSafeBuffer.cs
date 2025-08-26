using System;
using System.Collections.Generic;
using System.Threading;

namespace OS_Lab1.Model
{
    public class ThreadSafeBuffer //сама модель буффер
    {
        //очередь, хранит в себе (int, int) - номер потока и значение (индекс)
        private Queue<(int, int)> _threadSafeQueue = new Queue<(int, int)>();
        //максимальный размер буффера
        private int _maxBufferSize;
        //семафор пустоты
        private Semaphore _emptySemaphore;
        //семафор полноты
        private Semaphore _maxSizeSemaphore;
        //мютекс для критической секции
        private Mutex _mutex = new Mutex();
        //тот самый action, задаваемый из формы, печатающий что-либо на форму
        private Action<string> _writeAction;

        //конструктор, передаем размер и action
        public ThreadSafeBuffer(int maxBufferSize, Action<string> writeAction)
        {
            _maxBufferSize = maxBufferSize;
            _writeAction = writeAction;
            _emptySemaphore = new Semaphore(0, _maxBufferSize);
            _maxSizeSemaphore = new Semaphore(_maxBufferSize, _maxBufferSize);
    }

        //собственно метод push (кладем (int, int), что это - писал выше)
        public void Push((int, int) value)
        {
            //ждем, пока семафор полноты нас не уведомит, что в буффере есть место
            _maxSizeSemaphore.WaitOne();
            //заходим в крит секцию
            _mutex.WaitOne();
            //кладем
            _threadSafeQueue.Enqueue(value);
            //печатаем в форму
            _writeAction(value + " push");
            //выходим из крит секции
            _mutex.ReleaseMutex();
            //уведомляем семафор пустоты, что буффер теперь не пуст
            _emptySemaphore.Release();
        }

        //собственно метод pop
        public void Pop()
        {
            //ждем, пока семафор пустоты нас не уведомит, что в буффере есть место
            _emptySemaphore.WaitOne();
            //заходим в крит секцию
            _mutex.WaitOne();
            //забираем
            (int, int) value = _threadSafeQueue.Dequeue();
            //печатаем в форму
            _writeAction(value + " pop");
            //уведомляем семафор полноты, что буффер теперь не пуст
            _maxSizeSemaphore.Release();
            //выходим из крит секции
            _mutex.ReleaseMutex();
        }

        //очистка буффера
        public void Clear()
        {
            _threadSafeQueue.Clear();
            _maxBufferSize = 0;
        }
    }
}
