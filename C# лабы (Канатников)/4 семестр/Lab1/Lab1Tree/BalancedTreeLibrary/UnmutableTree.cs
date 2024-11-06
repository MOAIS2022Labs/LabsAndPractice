using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1Tree
{
    public class UnmutableTree<T> : ITree<T> where T : IComparable<T>
    {
        private readonly ITree<T> tree;
        public UnmutableTree(ITree<T> other)
        {
            tree = other;
        }

        public uint Count => tree.Count;

        public bool IsEmpty => tree.IsEmpty;

        public IEnumerable<Node<T>> Nodes => tree.Nodes;

        public void Add(T val)
        {
            throw new ForbiddenTreeModificationException("Нельзя менять неменяемое!");
        }

        public void Clear()
        {
            throw new ForbiddenTreeModificationException("Нельзя менять неменяемое!");
        }

        public bool Contains(T val) => tree.Contains(val);

        public IEnumerator<Node<T>> GetEnumerator() => Nodes.GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();

        public void Remove(T val)
        {
            throw new ForbiddenTreeModificationException("Нельзя менять неменяемое!");
        }

        public override string ToString() => tree.ToString();
    }
}
