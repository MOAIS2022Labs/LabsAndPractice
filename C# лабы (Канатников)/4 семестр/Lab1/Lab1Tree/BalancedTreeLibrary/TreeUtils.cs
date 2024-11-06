using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1Tree
{
    public static class TreeUtils<T> where T : IComparable<T>
    {        
        public delegate bool CheckDelegate(Node<T> node);
        public delegate void ActionDelegate(Node<T> node);
        public delegate ITree<T> TreeConstructorDelegate();

        public static readonly TreeConstructorDelegate ArrayTreeConstructor = () => new ArrayTree<T>();
        public static readonly TreeConstructorDelegate LinkedTreeConstructor = () => new LinkedTree<T>();

        public static bool Exists(ITree<T> tree, CheckDelegate check)
        {
            if (tree.IsEmpty)
                throw new InvalidTreeOperationException("Это дерево пустое!");

            foreach (var node in tree) 
                if (check.Invoke(node))
                    return true;
            return false;
        }

        public static ITree<T> FindAll(ITree<T> tree, CheckDelegate check, TreeConstructorDelegate ctor)
        {
            if (tree.IsEmpty)
                throw new InvalidTreeOperationException("Это дерево пустое!");

            var result = ctor.Invoke();
            foreach (var node in tree)
                if (check.Invoke(node))
                    result.Add(node.Value);
            return result;
        }

        public static void ForEach(ITree<T> tree, ActionDelegate action)
        {
            if (tree.IsEmpty)
                throw new InvalidTreeOperationException("Это дерево пустое!");

            foreach (var node in tree)
                action.Invoke(node);          
        }

        public static bool CheckForAll(ITree<T> tree, CheckDelegate check)
        {
            if (tree.IsEmpty)
                throw new InvalidTreeOperationException("Это дерево пустое!");

            foreach (var node in tree)
                if (!check.Invoke(node))
                    return false;
            return true;
        }
    }
}
