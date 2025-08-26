using _4_Sem_1_Lab_CSharp_Graph;
using Microsoft.Msagl.Core.DataStructures;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp
{
    public static class GraphUtils<N, L> where N : IComparable<N> where L : IComparable<L>, IEquatable<L>, IAdditionOperators<L, L, L>, new()
    {

        public delegate IGraph<N, L> GraphConstuctorDelegate();

        public delegate bool CheckDelegate(Node<N> node);
        public delegate void ActionDelegate(Node<N> node);

        public static readonly GraphConstuctorDelegate ArrayGraphConstructor = () => new ArrayGraph<N, L>();
        public static readonly GraphConstuctorDelegate LinkedGraphConstructor = () => new LinkedGraph<N, L>();

        //Проверяет наличие элемента в графе, который удовлетворяет заданному условию pred
        public static bool Exists(IGraph<N, L> graph, CheckDelegate pred)
        {
            //для каждой вершины в графе проверить делегат pred
            foreach (var node in graph)
                if (pred.Invoke(node))
                    return true;
            return false;
        }

        //Проверяет, удовлетворяют ли все элементы графа заданному условию pred
        public static bool CheckForAll(IGraph<N, L> graph, CheckDelegate pred)
        {
            //для каждой вершины в графе проверить делегат pred
            foreach (var node in graph)
                if (!pred.Invoke(node))
                    return false;
            return true;
        }

        //Делегат CheckDelegate<N, L> проверяет каждый узел на соответствие заданному условию
        //Делегат GraphConstuctorDelegate создает новый экземпляр графа
        //Возвращает новый экземпляр, содержащий только те узлы и ребра, которые удовлетворяют заданному условию.
        public static IGraph<N, L> FindAll(IGraph<N, L> graph, CheckDelegate check, GraphConstuctorDelegate create)
        {
            //инициализаця пустого графа через делегат create
            var result = create.Invoke();
            //для каждой вершины в графе проверить делегат pred
            //если вершина удолетворяет pred - она добавляется в результирующий граф
            foreach (var node in graph)
                if (check.Invoke(node))
                    result.AddNode(node.Data);

            //для каждого ребра в графе проверить, связано ли оно с вершинами из графа
            foreach (var edge in graph.Edges)
            {
                var from = edge.From;
                var to = edge.To;
                var weight = edge.Weight;
                //если ребро связано с вершинами из результирующего графа - оно добавляется в результирующий граф
                if (result.Contains(from.Data) && result.Contains(to.Data))
                    result.AddEdge(from.Data, to.Data, weight);
            }
            return result;
        }

        //Возвращает список всех ребер, выходящих из заданной вершины
        public static MyLinkedList<Edge<N, L>> GetEdgesList(IGraph<N, L> graph, N node)
        {
            var result = new MyLinkedList<Edge<N, L>>();
            foreach (var edge in graph.Edges)
            {
                if (edge.From.Data.CompareTo(node) == 0)
                    result.Add(edge);
            }
            return result;
        }

        //Принимает экземпляр графа и делегат ActionDelegate<N, L>
        //Выполняет действие над каждым узлом графа
        public static void ForEach(IGraph<N, L> graph, ActionDelegate action)
        {
            foreach (var node in graph)
                action.Invoke(node);
        }

        //Проверка существования вершины, удолетворяющей делегату check
        //Поиск в ширину
        public static bool FindWidth(IGraph<N, L> graph, N node, CheckDelegate check)
        {
            bool result = true;

            var startNode = graph.FindNode(node);

            var queue = new MyQueue<Node<N>>();
            queue.Push(startNode);
            while (queue.Count > 0 && result == true)
            {
                var currentNode = queue.Pop();

                if (!check.Invoke(currentNode))
                {
                    result = false;
                    break;
                }

                var edges = graph.Edges.Where(e => e.From.CompareTo(currentNode) == 0);
                foreach (var edge in edges)
                    queue.Push(edge.To);
            }
            return result;
        }

        //Проверка существования вершины, удолетворяющей делегату check
        //Поиск в глубину
        public static bool FindDeep(IGraph<N, L> graph, N node, CheckDelegate check)
        {
            bool result = true;

            var startNode = graph.FindNode(node);

            var stack = new MyStack<Node<N>>();
            stack.Push(startNode);
            while (stack.Count > 0 && result == true)
            {
                var currentNode = stack.Pop();

                if (!check.Invoke(currentNode))
                {
                    result = false;
                    break;
                }

                var edges = graph.Edges.Where(e => e.From.CompareTo(currentNode) == 0);
                foreach (var edge in edges)
                    stack.Push(edge.To);
            }
            return result;
        }

        //Поиск длины пути из одной вершины в другую с помощью алгоритма волны
        public static L WaveAlgorithm(IGraph<N, L> graph, N start, N finish)
        {
            var _start = graph.FindNode(start);
            var _finish = graph.FindNode(finish);

            var frontier = new MyLinkedList<Node<N>>();
            var visited = new MyLinkedList<Node<N>>();
            var distance = new Dictionary<Node<N>, L>();
            frontier.Add(_start);
            var list = new List<Node<N>>();
            distance[_start] = new L();
            while (frontier.Count > 0)
            {
                frontier.Sort((v1, v2) => distance[v1].CompareTo(distance[v2]));
                var currentNode = frontier[0];
                frontier.RemoveAt(0);
                if (currentNode.Data.CompareTo(_finish) == 0)
                    return distance[currentNode.Data];

                visited.Add(currentNode.Data);
                foreach (var adjacentNode in graph.GetNodesList(currentNode.Data.Data))
                {
                    if (!visited.Contains(adjacentNode))
                    {
                        frontier.Add(adjacentNode);

                        var newDistance = distance[currentNode.Data] + graph.Edges.First(e => e.From.Equals(currentNode.Data) && e.To.Equals(adjacentNode)).Weight;

                        if (!distance.ContainsKey(adjacentNode) || newDistance.CompareTo(distance[adjacentNode]) < 0)
                            distance[adjacentNode] = newDistance;
                    }
                }
            }
            return new L();
        }
    }
}
