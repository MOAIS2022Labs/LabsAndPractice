using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Lab1Tree
{
    public class ArrayTree<T> : ITree<T> where T : IComparable<T>
    {
        private Node<T>?[] _nodes;
        private int _capacity;
        private uint _countLevels = 0;
        public ArrayTree(uint level = 1)
        {
            _countLevels = level;
            for (int i = 0; i < _countLevels; ++i)
                _capacity += (int)Math.Pow(2, i);
            _nodes = new Node<T>?[_capacity];
        }
        public uint Count { get; private set; }

        public bool IsEmpty { get => Count == 0; }

        private IEnumerable<Node<T>> GetNodes()
        {
            if (_nodes[0] is null)
                yield break;

            for (int i = 0; i < _capacity; ++i)
            {
                if (_nodes[i] is not null)
                    yield return _nodes[i];
            }

        }       

        public IEnumerable<Node<T>> Nodes
        {
            get
            {
                return GetNodes();
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
        private void Extend()
        {
            _capacity += (int)Math.Pow(2, _countLevels);
            ++_countLevels;
            var tmp = new Node<T>?[_capacity];
            for (int i = 0; i < Count; ++i)
                tmp[i] = _nodes[i];
            _nodes = tmp;
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
        private void SetIndexes(Node<T>? node, int index = 0)
        {
            if (node is not null && index < _capacity)
            {
                if (node.Left is not null && index * 2 + 1 < _capacity)
                    _nodes[index * 2 + 1] = node.Left;
                if (node.Right is not null && index * 2 + 2 < _capacity)
                    _nodes[index * 2 + 2] = node.Right;
                SetIndexes(node.Left, index * 2 + 1);
                SetIndexes(node.Right, index * 2 + 2);
            }
        }
        public void Add(T val)
        {
            if (Contains(val))
                throw new InvalidTreeOperationException("Элемент уже есть в дереве!");
            
            if (_capacity == Count)
                Extend();

            ++Count;
            
            _nodes[0] = Insert(_nodes[0], val);
            SetIndexes(_nodes[0]);
        }

        public void Clear()
        {
            if (IsEmpty)
                throw new InvalidTreeOperationException("Это дерево уже пустое!");

            Array.Clear(_nodes, 0, _capacity);
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

        public IEnumerator<Node<T>> GetEnumerator() => Nodes.GetEnumerator();
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
        public void Remove(T val)
        {
            if (IsEmpty)
                throw new InvalidTreeOperationException("Это дерево уже пустое!");
            if (!Contains(val))
                throw new InvalidTreeOperationException("Элемент отсутствует в дереве!");

            --Count;
            if (Count > 1)
                Array.Clear(_nodes, 1, _capacity - 1);
            _nodes[0] = DeleteByKey(_nodes[0], val);
            SetIndexes(_nodes[0]);
        }

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

        public override string ToString() => IsEmpty ? "Дерево пусто" : ShowTree(_nodes[0], 0);
        public T this[int index]
        {
            get
            {
                if (index >= _capacity || _nodes[index] is null)
                    throw new TreeOutOfRangeException("Под указанным индексом не находится ни одного значения");
                    
                return _nodes[index].Value;
            }
        }
    }
}
