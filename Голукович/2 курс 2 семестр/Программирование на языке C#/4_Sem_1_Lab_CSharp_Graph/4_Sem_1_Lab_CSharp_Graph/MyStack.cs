using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp_Graph
{
    internal class MyStack<T> where T : IComparable<T>
    {
        public MyStack() { }
        private MyLinkedList<T> _stack = new();
        public int Count { get { return _stack.Count; } }
        public void Push(T value)
        {
            _stack.Add(value);
        }

        public T? Pop()
        {
            T? value = default;
            if (_stack.Count > 0)
            {
                value = _stack.GetLast().Data;
                _stack.RemoveAt(Count - 1);
            }
            return value;
        }
    }
}
