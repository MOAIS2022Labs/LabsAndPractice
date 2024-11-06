#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstring>
#include <sstream>

// пользовательская структура
struct Point
{
private:
    double x = 0, y = 0, z = 0;
public:
    Point() {}
    Point(double a, double b, double c) : x(a), y(b), z(c) {}
    Point(const Point& other) : x(other.x), y(other.y), z(other.z) {}
    ~Point() {}
    bool operator ==(const Point& other)
    {
        return (abs(x - other.x) < 0.001 && abs(y - other.y) < 0.001 && abs(z - other.z) < 0.001);
    }
    Point& operator =(const Point& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    bool operator !=(const Point& other)
    {
        return (x != other.x || y != other.y || z != other.z);
    }
    bool operator > (Point human)
    {
        return (x - human.x) > 0.001;
    }
    friend std::ostream& operator << (std::ostream& out, const Point& other)
    {
        out << other.x << ' ' << other.y << ' ' << other.z << '\n';
        return out;
    }
    friend std::istream& operator >> (std::istream& in, Point& other)
    {
        in >> other.x >> other.y >> other.z;
        return in;
    }
};