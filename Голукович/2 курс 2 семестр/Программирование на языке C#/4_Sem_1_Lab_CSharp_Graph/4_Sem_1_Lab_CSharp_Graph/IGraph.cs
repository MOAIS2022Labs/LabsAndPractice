using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using _4_Sem_1_Lab_CSharp_Graph;

namespace _4_Sem_1_Lab_CSharp
{
    public interface IGraph { }

    public interface IGraph<N, L> : IGraph, IEnumerable<Node<N>> where N : IComparable<N> where L : IComparable<L>, IEquatable<L>, IAdditionOperators<L, L, L>, new()
    {
        bool Empty { get; }

        //Свойство количества вершин в графе
        int Count { get; }
        //IEnumerable для ребер
        public IEnumerable<Edge<N, L>> Edges { get; }
        //Добавление вершины с заданным значением в граф
        void AddNode(N node);
        //Добавление ребра между двумя вершинами с заданными значениеми
        void AddEdge(N from, N to, L weight);
        //Очистка графа
        void Clear();
        //Проверка, содержится вершина с заданным значением в графе
        bool Contains(N node);
        //Удаление вершины с заданным значением из графа
        void RemoveNode(N node);
        //Поиск заданного узла в списке
        Node<N> FindNode(N src);
        //Метод, возвращающий список всех вершин, связанных с заданной вершиной
        MyLinkedList<Node<N>> GetNodesList(N node); 
    }
}
