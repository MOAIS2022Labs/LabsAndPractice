using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1Tree
{
    public class Node<T>
    {
        public T Value { get; set; }
        private Node<T>? _left;
        private Node<T>? _right;
        public Node<T>? Left
        {
            get => _left;
            set
            {
                _left = value;
                FixHeight();
            }
        }
        public Node<T>? Right
        {

            get => _right;
            set
            {
                _right = value;
                FixHeight();
            }
        }
        private int _height;
        public int BalanceFactor
        {
            get => (Right?._height ?? 0) - (Left?._height ?? 0);
        }
        private void FixHeight()
        {
            var heightLeft = Left?._height ?? 0;
            var heightRight = Right?._height ?? 0;
            _height = Math.Max(heightLeft, heightRight) + 1;
        }
        public Node(T value = default, Node<T>? left = null, Node<T>? right = null)
        {
            Value = value;
            Left = left;
            Right = right;
            _height = 1;
        }
        public override string ToString() => Value.ToString();
    }
}
