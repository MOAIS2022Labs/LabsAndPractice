using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp_Graph
{
    internal class MyPair<T> : IComparable<MyPair<T>> where T : IComparable<T>
    {
        public MyPair(T first, bool second)
        {
            First = first;
            Second = second;
        }
        public T First { get; set; }
        public bool Second { get; set; }

        public int CompareTo(MyPair<T>? other)
        {
            return First.CompareTo(other.First);
        }
    }
}
