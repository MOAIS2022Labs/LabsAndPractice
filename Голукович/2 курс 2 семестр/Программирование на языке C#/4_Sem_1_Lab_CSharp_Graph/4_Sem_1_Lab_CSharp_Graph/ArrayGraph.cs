using _4_Sem_1_Lab_CSharp_Graph;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.VisualStyles;
using System.Windows.Navigation;
using System.Xml.Linq;

namespace _4_Sem_1_Lab_CSharp
{
    public class ArrayGraph<N, L> : IGraph<N, L> where N : IComparable<N> where L : IComparable<L>, IEquatable<L>, IAdditionOperators<L, L, L>, new()
    {
        //максимальные размеры графа
        private static int _nodesCapacity;
        private static int _edgesCapacity;

        public int Count { get => nodesCount; }
        public bool Empty { get => nodesCount == 0; }

        private int edgesCount { get; set; }
        private int nodesCount { get; set; }

        private Node<N>[] _nodes;

        private Edge<N, L>[] _edges;

        //Enumerator графа для вершин
        public IEnumerator<Node<N>> GetEnumerator()
        {
            for (int i = 0; i < nodesCount; i++)
                yield return _nodes[i];
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        //IEnumerable для ребер
        public IEnumerable<Edge<N, L>> Edges
        { 
            get 
            {
                for (int i = 0; i < edgesCount; i++)
                    yield return _edges[i];
            } 
        }

        //Конструктор графа со станданртым максимальным количеством вершин 10 и ребер 99
        public ArrayGraph(int capacity = 10)
        {
            _nodesCapacity = capacity;
            _edgesCapacity = capacity * (capacity - 1);
            edgesCount = 0;
            nodesCount = 0;
            //массивы
            _nodes = new Node<N>[_nodesCapacity];
            _edges = new Edge<N, L>[_edgesCapacity];
        }


        //Очистка графа
        public void Clear()
        {
            for (int i = 0; i < nodesCount; i++)
                _nodes[i] = null;
            for (int i = 0; i < edgesCount; i++)
                _edges[i] = null;

            nodesCount = 0;
            edgesCount = 0;
        }

        //Добавление ребра между двумя вершинами с заданными значениеми
        public void AddEdge(N from, N to, L weight)
        {
            //проверки возможности добавить ребро в текущий граф
            if (nodesCount <= 1)
                throw new DisabledAddGraphException("Невозможно добавить ребро. Нет узлов или существует только один узел.");
            if (edgesCount >= _edgesCapacity)
                throw new DisabledAddGraphException("Невозможно добавить ребро. Массив переполнен.");

            //поиск вершин ребра и проверка их существования
            var nodeFrom = FindNode(from);
            var nodeTo = FindNode(to);
            if (nodeFrom == null || nodeTo == null)
                throw new DisabledFindGraphException("Один или оба элемента не найдены.");

            //создание ребра
            var newEdge = new Edge<N, L>(nodeFrom, nodeTo, weight);
            //проверка, что такое ребро уже существует
            foreach (var edge in Edges)
                if (edge.CompareTo(newEdge) == 0)
                    throw new DisabledAddGraphException("Невозможно добавить ребро. Такое ребро уже существует.");

            //добавление ребра в граф
            _edges[edgesCount] = newEdge;
            newEdge.Number = edgesCount;
            edgesCount++;

            //проверка на ацикличность: если граф перестанет быть ацикличным - добавленное ребро будет исключено из графа
            if (IsCyclic())
            {
                edgesCount--;
                _edges[edgesCount] = null;
                throw new DisabledAddGraphException("Невозможно добавить ребро. Граф должен быть ациклическим.");
            }        
        }

        //Добавление вершины с заданным значением в граф
        public void AddNode(N elem)
        {
            //проверка новой вершины на существование
            if (nodesCount > 0 && FindNode(elem) != null)
                throw new DisabledAddGraphException("Граф уже содержит узел с данным значением");

            //проверки возможности добавить вершину в текущий граф
            if (Count >= _nodesCapacity)
                throw new DisabledAddGraphException("Граф полон.");

            //создание и добавление в граф новой вершины
            var node = new Node<N>(elem);
            node.Number = nodesCount;
            _nodes[nodesCount] = node;
            nodesCount++;
        }

        //Поиск заданного узла в списке
        public Node<N> FindNode(N src)
        {
            //проверка графа на пустоту
            if (nodesCount == 0)
                throw new DisabledFindGraphException("Невозможно найти узел. Граф пуст.");

            //поиск вершины с заданным значением через enumerator текущего графа
            foreach (var node in this)
                if (node.Data.CompareTo(src) == 0)
                    return node;

            //если вершина с заданным значением не найдена
            return null;
        }

        //Удаление вершины с заданным значением из графа
        public void RemoveNode(N elem)
        {
            //поиск вершины с заданным значением и проверка ее существования
            var tmp = FindNode(elem);
            if (tmp == null)
                throw new DisabledRemoveGraphException("Граф не содержит данный элемент.");

            //удаление ребер, входящих или исходящих из ребра с заданным значением
            RemoveEdges(tmp);
            //изменение номеров вершин в графе, стящих выше удаленного
            ChangeNodesNumbers(tmp.Number);

            //удаление вершины из графа
            _nodes[tmp.Number] = null;
            nodesCount--;

            //переинициализация массива вершин, чтобы в промежутках между вершинами в массиве не было пустых значений
            _nodes = _nodes.Where(x => x != null).ToArray();
            Array.Resize(ref _nodes, _nodesCapacity);
        }

        //Вспомогательный метод удаления ребер
        private void RemoveEdges(Node<N> node)
        {
            //проходимся по всем рёбрам
            foreach (var edge in Edges)
            {
                //если ребро входит или исходит из заданной вершины, оно удаляется из графа
                if ((edge.To.Data.CompareTo(node.Data) == 0) || (edge.From.Data.CompareTo(node.Data) == 0))
                {
                    //изменение номеров ребер в графе, стящих выше удаленного
                    ChangeEdgesNumbers(edge.Number);

                    //удаление ребра из массива ребер
                    _edges[edge.Number] = null;
                    edgesCount--;

                    //переинициализация массива вершин, чтобы в промежутках между ребрами в массиве не было пустых значений
                    _edges = _edges.Where(x => x != null).ToArray();
                    Array.Resize(ref _edges, _edgesCapacity);
                }
            }
        }

        //Вспомогательный метод смены номеров вершин
        private void ChangeNodesNumbers(int num)
        {
            //для каждой вершины, номер которой выше заданой
            foreach (var node in this)
                if (node.Number > num)
                    node.Number--;
        }

        //Вспомогательный метод смены номеров ребер
        private void ChangeEdgesNumbers(int num)
        {
            //для каждого ребра, номер которого выше заданого
            foreach (var edge in Edges)
                if (edge.Number > num)
                    edge.Number--;
        }

        //Проверка, содержится вершина с заданным значением в графе
        public bool Contains(N node)
        {
            //проверка графа на пустоту
            if (nodesCount == 0)
                return false;
            //FindNode возвращает само ребро или null, если оно не найдено
            return FindNode(node) != null;
        }

        //Метод, возвращающий список всех вершин, связанных с заданной вершиной
        public MyLinkedList<Node<N>> GetNodesList(N node)
        {
            //инициализация пустого результирующего листа
            var result = new MyLinkedList<Node<N>>();

            //для каждого ребра в графе
            foreach (var edge in Edges)
                //если ребро исходит из вершины с заданным значением - добавляем вершину "куда" в лист
                if (edge.From.Data.CompareTo(node) == 0)
                    result.Add(edge.To);
            return result;
        }

        //Проверка графа на цикличность
        private bool IsCyclic()
        {
            //для каждой вершины из графа
            foreach (var toVisit in this)
            {
                //инициализация списка посещаемости вершин (карта посещений)
                var visitedList = new MyLinkedList<MyPair<Node<N>>> { new MyPair<Node<N>>(toVisit, true) };
                foreach (var node in this)
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
