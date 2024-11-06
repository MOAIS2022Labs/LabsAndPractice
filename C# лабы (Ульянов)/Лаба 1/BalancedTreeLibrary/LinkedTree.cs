using System;
using System.Collections;
using System.Text;


namespace Lab1Tree
{

    public class LinkedTree<T> : ITree<T> where T : IComparable<T>
    {
        public Node<T>? Root { get; private set; }
        public LinkedTree()
        {
            Root = null;
            Count = 0;
        }
        public uint Count { get; private set; }

        public bool IsEmpty { get => Count == 0; }

        private static IEnumerable<Node<T>> GetNodes(Node<T>? node)
        {
            if (node is not null)
            {
                foreach (var val in GetNodes(node.Left))
                    yield return val;

                yield return node;

                foreach (var val in GetNodes(node.Right))
                    yield return val;
            }
        }

        public IEnumerable<Node<T>> Nodes 
        {
            get
            {
                return GetNodes(Root);
            }
        }
        private Node<T> RotateRight(Node<T> node)
        {
            var q = node.Left;
            node.Left = q.Right;
            q.Right = node;
            return q;
        }
        private Node<T> RotateLeft(Node<T> node)
        {
            var q = node.Right;
            node.Right = q.Left;
            q.Left = node;
            return q;
        }
        private Node<T> Balance(Node<T> node)
        {
            var bFactor = node.BalanceFactor;
            if (bFactor == 2)
            {
                if (node.Right.BalanceFactor < 0)
                    node.Right = RotateRight(node.Right);
                return RotateLeft(node);
            }
            if (bFactor == -2)
            {
                if (node.Left.BalanceFactor > 0)
                    node.Left = RotateLeft(node.Left);
                return RotateRight(node);
            }
            return node;
        }

        private Node<T> Insert(Node<T>? node, T val)
        {
            if (node is null)
                return new Node<T>(val);

            if (val.CompareTo(node.Value) < 0)
                node.Left = Insert(node.Left, val);
            else
                node.Right = Insert(node.Right, val);
            return Balance(node);
        }   

        public void Add(T val)
        {
            if (Contains(val))
                throw new InvalidTreeOperationException("Элемент уже есть в дереве!");
            Root = Insert(Root, val);
            ++Count;
        }

        public void Clear()
        {
            if (IsEmpty)
                throw new InvalidTreeOperationException("Это дерево уже пустое!");
            Root = null; 
            Count = 0;
        }

        public bool Contains(T val)
        {

            if (IsEmpty)
                return false;

            foreach (var node in Nodes)
                if (node.Value.CompareTo(val) == 0)
                    return true;
            return false;
        }        
        public void Remove(T val)
        {
            if (IsEmpty)
                throw new InvalidTreeOperationException("Это дерево уже пустое!");
            if (!Contains(val))
                throw new InvalidTreeOperationException("Элемент отсутствует в дереве!");

            Root = DeleteByKey(Root, val);
            --Count;
        }

        private Node<T>? DeleteByKey(Node<T>? node, T val)
        {
            if (node is null) return null;
            if (val.CompareTo(node.Value) < 0)
                node.Left = DeleteByKey(node.Left, val);
            else if (val.CompareTo(node.Value) > 0)
                node.Right = DeleteByKey(node.Right, val);
            else
            {
                var l = node.Left;
                var r = node.Right;
                if (r is null) return l;
                Node<T>? min, min_right = FindAndRemoveMin(r, out min);
                min.Right = min_right;
                min.Left = l;
                return Balance(min);
            }
            return Balance(node);
        }
       
        private Node<T>? FindAndRemoveMin(Node<T> node, out Node<T> min)
        {
            if (node.Left is null)
            {
                min = node;
                return node.Right;
            }
            node.Left = FindAndRemoveMin(node.Left, out min);
            return Balance(node);
        }

        public IEnumerator<Node<T>> GetEnumerator() => Nodes.GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();

        private static string ShowTree(Node<T>? node, int level)
        {
            StringBuilder result = new();
            if (node is not null)
            {
                result.Append(ShowTree(node.Right, level + 1));
                for (var i = 1; i <= level; ++i)
                    result.Append("\t");
                result.AppendLine(node.ToString());
                result.Append(ShowTree(node.Left, level + 1));
            }
            return result.ToString();
        }

        public override string ToString() => IsEmpty ? "Дерево пусто" : ShowTree(Root, 0);
    }
}
