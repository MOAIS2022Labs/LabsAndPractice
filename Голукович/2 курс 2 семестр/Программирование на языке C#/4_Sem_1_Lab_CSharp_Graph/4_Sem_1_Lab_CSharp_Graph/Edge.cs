using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp
{
    public class Edge<N, L> : IComparable<Edge<N, L>> where N : IComparable<N> where L : IComparable<L>
    {
        public Edge(Node<N> from, Node<N> to, L weight)
        {
            From = from;
            To = to;
            Weight = weight;
        }

        //Начальная вершина
        public Node<N> From { get; set; }
        //Конечная вершина
        public Node<N> To { get; set; }
        //Вес
        public L Weight { get; set; }
        //Номер в графе
        public int Number { get; set; }

        //Определение CompareTo, сравнивающее значения ребра
        public int CompareTo(Edge<N, L>? other)
        {
            int weight = Weight.CompareTo(other.Weight);
            int from = From.CompareTo(other.From);
            int to = To.CompareTo(other.To);
            //если ребра по значениям равны - возвращаем 0
            if (weight == 0 && from == 0 && to == 0)
                return 0;
            //если ребра по весу равны - возвращаем сравнение ребер по номерам в графе
            if (weight == 0)
            {
                int number = Number.CompareTo(other.Number);
                //если ребра по номерам равны - возвращаем сравнение ребер по вершинам "откуда"
                if (number == 0)
                {
                    //если ребра по вершинам "откуда" равны - возвращаем сравнение ребер по вершинам "куда"
                    if (from == 0)
                        return to;
                    //иначе возвращаем сравнение ребер по вершинам "откуда"
                    return from;
                }
                //иначе возвращаем сравнение ребер по номеру в графе
                return number;
            }
            //иначе возвращаем сравнение ребер по весу
            return weight;
        }
    }
}
