using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp
{
    public class Node<N> : IComparable<Node<N>> where N : IComparable<N>
    {
        //Данные
        public N Data { get; set; }
        //Номер в графе
        public int Number { get; set; }

        public Node(N data)
        {
            Data = data;
            Number = 0;
        }
        public override string ToString() => Data.ToString();

        public int CompareTo(Node<N>? other)
        {
            return Data.CompareTo(other.Data);
        }
    }
}
