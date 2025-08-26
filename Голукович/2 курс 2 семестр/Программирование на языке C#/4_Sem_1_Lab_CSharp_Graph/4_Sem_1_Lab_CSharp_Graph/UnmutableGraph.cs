using _4_Sem_1_Lab_CSharp_Graph;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp
{
    public class UnmutableGraph<N, L> : IGraph<N, L> where N : IComparable<N> where L : IComparable<L>, IEquatable<L>, IAdditionOperators<L, L, L>, new()
    {
        private IGraph<N, L> _graph;

        public UnmutableGraph(IGraph<N, L> _graph) { this._graph = _graph; }

        public int Count { get => _graph.Count; }
        public bool Empty { get => _graph.Empty; }

        public IEnumerator<Node<N>> GetEnumerator()
        {
            return _graph.GetEnumerator();
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        public IEnumerable<Edge<N, L>> Edges { get => _graph.Edges; }
        public void AddEdge(N src, N dst, L weight)
        {
            throw new DisabledChangeGraphException("Данная операция невозможна.");
        }

        public void AddNode(N elem)
        {
            throw new DisabledChangeGraphException("Данная операция невозможна.");
        }

        public void Clear()
        {
            throw new DisabledChangeGraphException("Данная операция невозможна.");
        }

        public bool Contains(N node)
        {
            return _graph.Contains(node);
        }

        public Node<N> FindNode(N src)
        {
            return _graph.FindNode(src);
        }

        public MyLinkedList<Node<N>> GetNodesList(N node)
        {
            return _graph.GetNodesList(node);
        }

        public void RemoveNode(N node)
        {
            throw new DisabledChangeGraphException("Данная операция невозможна.");
        }
    }
}
