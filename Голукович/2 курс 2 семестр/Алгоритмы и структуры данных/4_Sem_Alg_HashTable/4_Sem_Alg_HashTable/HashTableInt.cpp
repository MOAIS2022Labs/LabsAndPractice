#include "HashTableInt.h"

void HashTableInt::ReHash()
{
    max_table_size *= 2;
    Vector new_table;
    new_table.resize(max_table_size);
    for (auto elem : table)
    {
        if (elem.used == 1)
        {
            std::shared_ptr<Wagon> info = elem.info;
            int index = Hash(info->get_number());
            while (new_table[index].used == 1 && new_table[index].info->get_number() != info->get_number())
                index = (index + 1) % (max_table_size * 2);

            new_table[index].used = 1;
            new_table[index].info = info;
        }
    }
    table = new_table;
    new_table.clear();
}

HashTableInt::HashTableInt(size_t max_size)
{
    max_table_size = max_size;
    table.resize(max_table_size);
}

int HashTableInt::Hash(int key)
{
    return key % max_table_size;
}

int HashTableInt::Find(int key, std::shared_ptr<Wagon>& elem)
{
    int result = -1;
    int index = Hash(key);
    while (!(table[index].used == 0 || table[index].used == 1 && table[index].info->get_number() == key))
        index = (index + 1) % max_table_size;
    if (table[index].used == 1)
    {
        result = index;
        table[index].info = elem;
    }
    return result;
}

bool HashTableInt::Add(std::shared_ptr<Wagon> elem)
{
    bool result = false;
    int index = Hash(elem->get_number());

    if (table[index].used == 1 && size > max_table_size * 0.8)
        ReHash();

    while (table[index].used == 1 && table[index].info->get_number() != elem->get_number())
        index = (index + 1) % max_table_size;

    if (table[index].used != 1)
    {
        result = true;
        size += 1;
        table[index].used = 1;
        table[index].info = elem;
    }
    return result;
}

bool HashTableInt::Erase(int key)
{
    bool result = false;
    int index = Hash(key);
    while (!(table[index].used == 0 || table[index].used == 1 && table[index].info->get_number() == key))
        index = (index + 1) % max_table_size;
    if (table[index].used == 1)
    {
        size -= 1;
        table[index].used = -1;
        result = true;
    }
    return result;
}

void HashTableInt::Fill(std::ifstream& file)
{
    char type;
    while (file >> type)
    {
        if (type == 'Ï')
            Add(std::make_shared<Passenger_Wagon>(file));
        else
            Add(std::make_shared<Freight_Wagon>(file));
    }
}

void HashTableInt::Print()
{
    int index = 0;
    for (auto elem : table)
    {
        if (elem.used == 1)
        {
            std::cout << index << "(" << Hash(elem.info->get_number()) << "): ";
            elem.info->print(std::cout);
            std::cout << '\n';
        }
        ++index;
    }
}