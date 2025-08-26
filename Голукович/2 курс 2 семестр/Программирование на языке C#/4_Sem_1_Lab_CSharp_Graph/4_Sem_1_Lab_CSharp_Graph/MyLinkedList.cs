using _4_Sem_1_Lab_CSharp;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp_Graph
{
    public class ListNode<T> where T : IComparable<T>
    {
        public ListNode(T data)
        {
            Data = data;
        }
        public T Data { get; set; }
        public ListNode<T>? Next { get; set; }

    }

    public class MyLinkedList<T> : IEnumerable<T> where T : IComparable<T>
    {
        ListNode<T>? head;
        ListNode<T>? tail;
        int size = 0;

        //Добавление элемента в список
        public void Add(T data)
        {
            ListNode<T> node = new ListNode<T>(data);

            if (head == null)
                head = node;
            else
                tail!.Next = node;
            tail = node;

            size++;
        }

        //Удаление элемента из списка
        public bool Remove(T data)
        {
            ListNode<T>? current = head;
            ListNode<T>? previous = null;

            while (current != null && current.Data != null)
            {
                if (current.Data.CompareTo(data) == 0)
                {
                    if (previous != null)
                    {
                        previous.Next = current.Next;
                        if (current.Next == null)
                            tail = previous;
                    }
                    else
                    {
                        head = head?.Next;
                        if (head == null)
                            tail = null;
                    }
                    size--;
                    return true;
                }

                previous = current;
                current = current.Next;
            }
            return false;
        }

        //Количество элементов в списке
        public int Count { get { return size; } }
        public bool Empty { get { return size == 0; } }
        //Очистка списка
        public void Clear()
        {
            head = null;
            tail = null;
            size = 0;
        }
        //Содержит ли список элемент с заданным значением
        public bool Contains(T data)
        {
            ListNode<T>? current = head;
            while (current != null && current.Data != null)
            {
                if (current.Data.Equals(data)) return true;
                current = current.Next;
            }
            return false;
        }

        //Добвление элемента в начало списка
        public void AppendFirst(T data)
        {
            ListNode<T> node = new ListNode<T>(data);
            node.Next = head;
            head = node;
            if (size == 0)
                tail = head;
            size++;
        }
        //Последний элемент списка
        public ListNode<T>? GetLast()
        {
            return tail;
        }
        //IEnumerator для элементов листа
        public IEnumerator<T> GetEnumerator()
        {
            ListNode<T>? current = head;
            while (current != null)
            {
                yield return current.Data;
                current = current.Next;
            }
        }

        //Реализация интерфейса IEnumerable
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        //Делегат-компаратор для сортировки
        public delegate int comparator(T left, T right);
        //Сортировка вставками
        public void Sort(comparator compare)
        {
            ListNode<T>? current = head;
            while (current != null)
            {
                ListNode<T>? next = current.Next;
                ListNode<T>? sorted = null;
                {
                    if (sorted == null || compare(sorted.Data, current.Data) > -1)
                    {
                        current.Next = sorted;
                        sorted = current;
                    }
                    else
                    {
                        ListNode<T>? cur = sorted;
                        while (cur.Next != null && compare(cur.Next.Data, current.Data) == -1)
                            cur = cur.Next;

                        current.Next = cur.Next;
                        cur.Next = current;
                    }
                }
                current = next;
            }
        }

        //Индексатор листа
        public ListNode<T> this[int index]
        {
            get
            { 
                ListNode<T> current = head;
                for (int i = 0; i < index && current != null; ++i)
                    current = current.Next;
                return current;
            }
            set
            {
                ListNode<T> current = head;
                for (int i = 0; i < index && current != null; ++i)
                    current = current.Next;
                current = value;
            }
        }

        //Удалить элемент по индексу
        public bool RemoveAt(int index)
        {
            if (index < 0 || index >= size)
                return false;

            ListNode<T> value = head;

            for (int i = 0; i < index - 1; i++)
                value = value.Next;

            if (index == 0)
                head = head.Next;
            else
                value = value.Next.Next;

            size--;
            return true;
        }
    }
}
