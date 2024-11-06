using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1Tree
{
    public interface ITree<T> : IEnumerable<Node<T>> where T : IComparable<T>
    {
        void Add(T val);
        void Clear();
        bool Contains(T val);
        void Remove(T val);
        uint Count { get; }
        bool IsEmpty { get; }
        IEnumerable<Node<T>> Nodes { get; }
    }
}
