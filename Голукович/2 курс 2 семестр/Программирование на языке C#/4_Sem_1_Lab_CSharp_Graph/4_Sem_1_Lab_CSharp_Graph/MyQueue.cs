using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp_Graph
{
    internal class MyQueue<T> where T : IComparable<T>
    {

        public MyQueue() { }
        private MyLinkedList<T> _queue = new();
        public int Count { get { return _queue.Count; } }

        public void Push(T value)
        {
            _queue.Add(value);
        }

        public T? Pop()
        {
            T? value = default;
            if (_queue.Count > 0 )
            {
                value = _queue[0].Data;
                _queue.RemoveAt(0);
            }
            return value;
        }
    }
}
