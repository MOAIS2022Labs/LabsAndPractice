module;
#include <iostream>
#include <fstream>

export module Sequence;

export template <typename T>
class Node
{
public:
    T info;
    Node* next;
    Node(T info = T(), Node* ptr = nullptr) : info(info), next(ptr) {}
    ~Node() { next = nullptr; }
};

export template <typename T>
class Sequence
{
    using ptrNode = Node<T>*;
private:
    ptrNode head, tail;
    size_t size;
    void adding_by_pointer(ptrNode& ptr, T elem);
    void deleting_by_pointer(ptrNode& ptr);
    ptrNode get_head() const { return head; }
    ptrNode get_tail() const { return tail; }
    ptrNode get_ptr(size_t index) const
    {
        try
        {
            if (index >= size)
                throw std::out_of_range("Index out of range");
            else
            {
                ptrNode ptr = head->next;
                size_t i{};
                while (ptr)
                {
                    if (i == index)
                        return ptr;
                    i++;
                    ptr = ptr->next;
                }
            }
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            exit(1);
        }
    }
    T get_elem(ptrNode ptr) const { return ptr->info; }
    void set_tail(ptrNode ptr) { tail = ptr; }
    void add_to_head(T elem);
    void add_to_tail(T elem);
    void add_after(ptrNode ptr, T elem);
    void del_from_head();
    void del_after(ptrNode ptr);
public:
    Sequence();
    Sequence(const Sequence& other);
    Sequence(std::ifstream& file);
    ~Sequence();
    Sequence<T> operator+(const Sequence& other); // concatenation
    Sequence<T>& operator=(const Sequence& other);
    Sequence<T> subseq(const size_t index, const size_t length);
    T get_elem(size_t index) { return get_ptr(index)->info; }
    size_t get_size() const { return size; }
    int get_pos(T elem) const;
    int get_pos(const Sequence<T>& seq) const;
    void set_elem(T elem, size_t index);
    bool is_empty() const { return !head->next; }
    void del_elem(size_t index);
    void print(const char* message = "", const char* delim = " ", std::ostream& stream = std::cout) const;
    void clear(ptrNode& begin, ptrNode& end);
};

template<typename T>
void Sequence<T>::adding_by_pointer(ptrNode& ptr, T elem)
{
    ptr = new Node(elem, ptr);
    ++size;
}
template<typename T>
void Sequence<T>::deleting_by_pointer(ptrNode& ptr)
{
    ptrNode p = ptr;
    ptr = p->next;
    delete p;
    --size;
}

template<typename T>
Sequence<T>::Sequence()
{
    tail = head = new Node<T>();
    size = 0;
}

template<typename T>
Sequence<T>::Sequence(const Sequence& other)
{
    tail = head = new Node<T>();
    size = 0;
    ptrNode ptr = other.head;
    ptrNode ptr1 = head;
    while (ptr->next)
    {
        ptr1->next = new Node<T>(ptr->next->info);
        ptr = ptr->next;
        ptr1 = ptr1->next;
        ++size;
    }
    tail = ptr1->next;
}

template<typename T>
Sequence<T>::Sequence(std::ifstream& file)
{
    tail = head = new Node<T>();
    size = 0;
    T elem;
    while (file >> elem)
    {
        add_to_tail(elem);
    }
}

template<typename T>
Sequence<T>::~Sequence()
{
    while (head && !is_empty())
    {
        del_from_head();
    }
    delete head;
    head = tail = nullptr;
}

template<typename T>
Sequence<T> Sequence<T>::operator+(const Sequence& other)
{
    Sequence<T> res;
    ptrNode ptr = head->next;
    while (ptr)
    {
        res.add_to_tail(ptr->info);
        ptr = ptr->next;
    }

    ptr = other.head->next;
    while (ptr)
    {
        res.add_to_tail(ptr->info);
        ptr = ptr->next;
    }
    return res;
}

template<typename T>
Sequence<T>& Sequence<T>::operator=(const Sequence& other)
{
    if (this != &other)
    {
        clear(head, tail);
        tail = head = new Node(0);
        size = 0;
        ptrNode ptr = other.head;
        ptrNode ptr1 = head;
        while (ptr->next)
        {
            ptr1->next = new Node(ptr->next->info);
            ptr = ptr->next;
            ptr1 = ptr1->next;
            ++size;
        }
        tail = ptr1->next;
    }
    return *this;
}

template<typename T>
Sequence<T> Sequence<T>::subseq(const size_t index, const size_t length)
{
    Sequence<T> res;
    ptrNode ptr = get_ptr(index);
    ptrNode end = get_ptr(index + length);
    while (ptr != end)
    {
        res.add_to_tail(ptr->info);
        ptr = ptr->next;
    }
    return res;
}

template<typename T>
int Sequence<T>::get_pos(T elem) const
{
    ptrNode ptr{ head->next };
    int i{};
    while (ptr)
    {
        if (ptr->info == elem)
            return i;
        i++;
        ptr = ptr->next;
    }
    return -1;
}

template<typename T>
int Sequence<T>::get_pos(const Sequence<T>& seq) const
{
    T beg = seq.head->next->info;
    int pos = get_pos(beg);
    if (pos != -1)
    {
        ptrNode tmp = get_ptr(pos);
        ptrNode tmp_sub = seq.head->next;
        while (tmp_sub)
        {
            if (tmp->info != tmp_sub->info)
                return -1;
            tmp = tmp->next;
            tmp_sub = tmp_sub->next;
        }
    }
    return pos;
}

template<typename T>
void Sequence<T>::set_elem(T elem, size_t index)
{
    ptrNode ptr = get_ptr(index);
    ptr->info = elem;
}

template<typename T>
void Sequence<T>::add_to_head(T elem)
{
    adding_by_pointer(head->next, elem);
    if (head == tail)
        tail = tail->next;
}

template<typename T>
void Sequence<T>::add_to_tail(T elem)
{
    adding_by_pointer(tail->next, elem);
    tail = tail->next;
}

template<typename T>
void Sequence<T>::add_after(ptrNode ptr, T elem)
{
    if (ptr)
    {
        adding_by_pointer(ptr->next, elem);
        if (ptr == tail)
            tail = tail->next;
    }
}

template<typename T>
void Sequence<T>::del_from_head()
{
    if (head->next)
    {
        deleting_by_pointer(head->next);
        if (!head->next)
            tail = head;
    }
}

template<typename T>
void Sequence<T>::del_after(ptrNode ptr)
{
    if (ptr && ptr->next)
    {
        if (ptr->next == tail)
            tail = ptr;
        deleting_by_pointer(ptr->next);
    }
}

template<typename T>
void Sequence<T>::del_elem(size_t index)
{
    ptrNode ptr = get_ptr(index - 1);
    del_after(ptr);
}

template<typename T>
void Sequence<T>::print(const char* message, const char* delim, std::ostream& stream) const
{
    stream << message << '\n';
    ptrNode ptr = head->next;
    while (ptr)
    {
        stream << ptr->info << delim;
        ptr = ptr->next;
    }
    stream << '\n';
}

template<typename T>
void Sequence<T>::clear(ptrNode& begin, ptrNode& end)
{
    while (begin != end)
        del_after(begin);
    begin = end;
}
