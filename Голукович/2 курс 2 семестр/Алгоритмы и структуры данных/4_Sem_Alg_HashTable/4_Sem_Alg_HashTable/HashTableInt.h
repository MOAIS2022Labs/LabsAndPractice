#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>
#include "Passenger_Wagon.h"
#include "Freight_Wagon.h"

struct Cell
{
    std::shared_ptr<Wagon> info;
    int used = 0;
};
using Vector = std::vector<Cell>;

class HashTableInt
{
private:
    Vector table;
    size_t max_table_size;
    size_t size;
    void ReHash();
public:
    HashTableInt(size_t max_size);
    int Hash(int key);

    int Find(int key, std::shared_ptr<Wagon>& elem);
    bool Add(std::shared_ptr<Wagon> elem);
    bool Erase(int key);
    void Fill(std::ifstream& file);
    void Print();
};