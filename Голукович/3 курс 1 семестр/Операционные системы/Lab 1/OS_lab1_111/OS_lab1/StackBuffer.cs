using System.Collections.Generic;

namespace OS_lab1
{
    public class StackBuffer<T>
    {
        //стэк
        private Stack<T> _threadSafeStack = new Stack<T>();
        //потолок по количеству значений
        private int _maxBufferSize;
        //объект синхронизации критической секции
        private object _lockObject = new object();
        //класс вывода в форму при пуше
        private Writer _push;
        //класс вывода в форму при попе (чзх отсылка на ASSembler???)
        private Writer _pop;

        //конструктор
        public StackBuffer(int maxBufferSize, Writer push, Writer pop)
        {
            _maxBufferSize = maxBufferSize;
            _push = push;
            _pop = pop;
        }

        public bool Push(T value)
        {
            bool result = false;
            //критическая секция
            lock (_lockObject)
            {
                //если количество элементов позволяет
                if (_threadSafeStack.Count < _maxBufferSize)
                {
                    //пушим
                    _threadSafeStack.Push(value);
                    result = true;
                    //пишем в буффер что запушили
                    _push.write($"{value}");
                }
            }
            return result;
        }

        public bool Pop(ref T value)
        {
            bool result = false;
            //критическая секция
            lock (_lockObject)
            {
                //если количество элементов позволяет
                if (_threadSafeStack.Count > 0)
                {
                    //соответственно поп
                    value = _threadSafeStack.Pop();
                    result = true;
                    //удаляем из буффера
                    _pop.write($"{value}");
                }
            }
            return result;
        }
    }
}
