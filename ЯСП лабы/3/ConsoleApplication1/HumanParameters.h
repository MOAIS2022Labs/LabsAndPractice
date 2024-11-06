#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstring>
#include <sstream>

// пользовательская структура
struct HumanParameters
{
private:
    double age = 0, height = 0, weight = 0;
public:
    HumanParameters() {}
    HumanParameters(double a, double b, double c)
    {
        /*if (a < 0 || b < 0 || c < 0)
        {
            throw std::invalid_argument("Отрицательные значения в полях структуры!\n");
        }*/
        age=a, height = b, weight = c;
    }
    HumanParameters(const HumanParameters& other) : age(other.age), height(other.height), weight(other.weight) {}
    ~HumanParameters() {}
    bool operator ==(const HumanParameters& other)
    {
        return (abs(age - other.age)<0.001 && abs(height - other.height)<0.001 && abs(weight-other.weight)<0.001);
    }
    HumanParameters& operator =(const HumanParameters& other)
    {
        age = other.age;
        height = other.height;
        weight = other.weight;
        return *this;
    }
    bool operator !=(const HumanParameters& other)
    {
        return (age != other.age || height != other.height || weight != other.weight);
    }
    bool operator > (HumanParameters human)
    {
        return (age - human.age) > 0.001;
    }
    friend std::ostream& operator << (std::ostream& out, const HumanParameters& other)
    {
        //out << '<' << other.age << ',' << other.height << ',' << other.weight << '>';
        out << other.age << ' ' << other.height << ' ' << other.weight << '\n';
        return out;
    }
    friend std::istream& operator >> (std::istream& in, HumanParameters& other)
    {
        in >> other.age >> other.height >> other.weight;
        return in;
    }
};