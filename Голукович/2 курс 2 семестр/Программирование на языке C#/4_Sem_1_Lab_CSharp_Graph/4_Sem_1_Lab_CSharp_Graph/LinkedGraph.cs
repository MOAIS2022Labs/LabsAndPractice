using _4_Sem_1_Lab_CSharp_Graph;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing.Text;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp
{
    public class LinkedGraph<N, L> : IGraph<N, L>, IEnumerable<Node<N>> where N : IComparable<N> where L : IComparable<L>, IEquatable<L>, IAdditionOperators<L, L, L>, new()
    {
        public int Count { get => _nodes.Count; }
        public bool Empty { get => _nodes.Count == 0; }

        private MyLinkedList<Node<N>> _nodes = new MyLinkedList<Node<N>>();

        private MyLinkedList<Edge<N, L>> _edges = new MyLinkedList<Edge<N, L>>();

        public IEnumerator<Node<N>> GetEnumerator()
        {
            return _nodes.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public IEnumerable<Edge<N, L>> Edges { get => _edges; }

        public LinkedGraph() { }

        public void Clear()
        {
            _edges.Clear();
            _nodes.Clear();
        }

        //Проверка, содержится вершина с заданным значением в графе
        public bool Contains(N node)
        {
            //проверка графа на пустоту
            if (_nodes.Count == 0)
                return false;
            //FindNode возвращает само ребро или null, если оно не найдено
            return FindNode(node) != null;
        }

        //Добавление вершины с заданным значением в граф
        public void AddNode(N elem)
        {
            //проверка новой вершины на существование
            if (Contains(elem))
                throw new DisabledAddGraphException("Граф уже содержит узел с данным значением");

            //создание и добавление в граф новой вершины
            var node = new Node<N>(elem);
            node.Number = Count;
            _nodes.Add(node);
        }

        //Удаление вершины с заданным значением из графа
        public void RemoveNode(N elem)
        {
            //поиск вершины с заданным значением и проверка ее существования
            var tmp = FindNode(elem);
            if (tmp == null)          
                throw new DisabledRemoveGraphException("Граф не содержит данный элемент");

            //удаление ребер, входящих или исходящих из ребра с заданным значением
            _edges = RemoveEdges(elem);
            //изменение номеров вершин в графе, стящих выше удаленного
            ChangeNodesNumbers(tmp.Number);
            //удаление вершины из графа
            _nodes.Remove(tmp);
        }

        //Вспомогательный метод удаления ребер, возвращает лист удаленных ребер
        private MyLinkedList<Edge<N, L>> RemoveEdges(N elem)
        {
            //инициализация пустого результирующего листа
            MyLinkedList<Edge<N, L>> tmp = new MyLinkedList<Edge<N, L>>();

            //проходимся по всем рёбрам
            foreach (var edge in _edges)
                //если ребро входит или исходит из заданной вершины, оно удаляется из графа и добавляется в результирующий лист
                if (edge.To.Data.CompareTo(elem) != 0 && edge.From.Data.CompareTo(elem) != 0)
                    tmp.Add(edge);
            return tmp;
        }

        //Вспомогательный метод смены номеров ребер
        private void ChangeNodesNumbers(int num)
        {
            //для каждого ребра, номер которого выше заданого
            foreach (var node in _nodes)
                if (node.Number > num)
                    node.Number--;
        }

        //Добавление ребра между двумя вершинами с заданными значениеми
        public void AddEdge(N from, N to, L weight)
        {
            //поиск вершин ребра и проверка их существования
            var nodeFrom = FindNode(from);
            var nodeTo = FindNode(to);
            if (nodeFrom == null || nodeTo == null)
                throw new DisabledFindGraphException("Один или оба элемента не найдены.");

            //создание ребра
            var newEdge = new Edge<N, L>(nodeFrom, nodeTo, weight);
            //проверка, что такое ребро уже существует
            foreach (var edge in _edges)
                if (edge.CompareTo(newEdge) == 0)
                    throw new DisabledAddGraphException("Невозможно добавить ребро. Такое ребро уже существует.");

            //добавление ребра в граф
            _edges.Add(newEdge);

            //проверка на ацикличность: если граф перестанет быть ацикличным - добавленное ребро будет исключено из графа
            if (IsCyclic())
            {
                _edges.Remove(newEdge);
                throw new DisabledAddGraphException("Невозможно добавить ребро. Граф должен быть ациклическим.");
            }
        }

        //Поиск заданного узла в списке
        public Node<N> FindNode(N src)
        {
            //проверка графа на пустоту
            if (_nodes.Count == 0)
                throw new DisabledFindGraphException("Невозможно найти узел. Граф пуст.");

            //поиск вершины с заданным значением через enumerator текущего графа
            foreach (var node in _nodes)
                if (node.Data.CompareTo(src) == 0)
                    return node;

            //если вершина с заданным значением не найдена
            return null;
        }

        //Метод, возвращающий список всех вершин, связанных с заданной вершиной
        public MyLinkedList<Node<N>> GetNodesList(N node)
        {
            //инициализация пустого результирующего листа
            var result = new MyLinkedList<Node<N>>();

            //для каждого ребра в графе
            foreach (var edge in _edges)
                //если ребро исходит из вершины с заданным значением - добавляем вершину "куда" в лист
                if (edge.From.Data.CompareTo(node) == 0)
                    result.Add(edge.To);
            return result;
        }

        //Проверка графа на цикличность
        private bool IsCyclic()
        {
            //для каждой вершины из графа
            foreach (var toVisit in _nodes)
            {
                //инициализация списка посещаемости вершин (карта посещений)
                var visitedList = new MyLinkedList<MyPair<Node<N>>> { new MyPair<Node<N>>(toVisit, true) };
                foreach (var node in _nodes)
                    if (node.CompareTo(toVisit) != 0)
                        visitedList.Add(new MyPair<Node<N>>(node, false));

                //список вершин, в которые можно попасть из исходной вершины
                var nodes = GetNodesList(toVisit.Data);
                if (nodes.Count > 0)
                {
                    //алгоритм прохода в глубину
                    var stack = new MyStack<Node<N>>();
                    //вершины, посещенные за один спуск
                    var localVisited = new MyLinkedList<Node<N>>();
                    //добавляем в стек вершины, в которые можно попасть из исходной вершины
                    foreach (var tmp in nodes)
                        stack.Push(tmp);
                    bool flagOfCycle = false;
                    while (stack.Count > 0 && !flagOfCycle)
                    {
                        var node = stack.Pop();
                        //null - признак вершины без потомков
                        if (node == null)
                        {
                            //для всех посещенных вершин, кроме исходной, в карте посещений меняем флаги на false
                            while (localVisited.Count > 0)
                            {
                                var prev = localVisited[0] as Node<N>;
                                localVisited.RemoveAt(0);
                                if (prev != null)
                                { 
                                    //переинициализация списка посещаемости вершин, тк дошли до одной из конечных вершин графа
                                    foreach (var visited in visitedList)
                                        if (visited.First.CompareTo(prev) != 0 && visited.Second)
                                            visited.Second = false;
                                }
                            }
                        }
                        else
                        {
                            //если пришли в вершину, в которой уже были - граф цикличен
                            foreach (var val in visitedList)
                                if (node.CompareTo(val.First) == 0)
                                {
                                    //если граф цикличен - выход из алгоритма с флагом true
                                    if (val.Second == true)
                                        return true;
                                    else
                                        val.Second = true;
                                }

                            //иначе добавляем в стек вершины, в которые можно попасть из текущей вершины
                            if (!flagOfCycle)
                            {
                                //добавляем в стек вершины, в которые можно попасть из текущей вершины
                                nodes = GetNodesList(node.Data);
                                //если дошли до одной из конечных вершин графа - положить в стек null чтобы потом переинициализировать пройденные вершины
                                if (nodes.Empty)
                                    stack.Push(null);
                                foreach (var tmp in nodes)
                                    stack.Push(tmp);
                            }
                        }
                    }
                }
            }
            //если прошлись по всем вершинам с флагом false - граф ацикличен
            return false;
        }
    }
}
