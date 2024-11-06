#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>


template<class X>
inline bool is_valid_input(std::istream& stream, X& info)
{
    bool isCorrectInfo = false;
    while (!isCorrectInfo)
    {
        stream >> info;
        if (!stream.fail())
            isCorrectInfo = true;
        else
        {
            std::cout << "Ошибка. Попробуйте снова.\n --> ";
            stream.clear();
            stream.ignore(stream.rdbuf()->in_avail());
        }
    }
    return isCorrectInfo;
}

// Проверка ввода
inline int vvod_int(std::istream& stream, int min, int max)
{
    int choice;
    while (!is_valid_input(stream, choice) || !(choice >= min && choice <= max))
        std::cout << "Ошибка.\n --> ";
    return choice;
}

// Тип std::chrono::duration представляет собой интервал времени, который может быть представлен в различных единицах измерения времени. 
// В данном случае, std::chrono::duration<int, std::ratio<3600>> означает, что Duration является интервалом времени, представленным целым числом(int),
// где каждая единица равна 3600 секундам (т.е. 1 час).
using Duration = std::chrono::duration<int, std::ratio<3600>>;

enum Color
{
    RED,
    BLUE,
    GREEN,
    BLACK,
    WHITE
};

struct Demon
{
private:
    std::string name;
    std::string origin;
    int height;
    std::string weapon;
    int horn_сount;
    Duration time;
    Color color;
public:
    void set_name(std::string name);
    void set_origin(std::string origin);
    void set_height(int height);
    void set_weapon(std::string weapon);
    void set_horn_count(int hornCount);
    void set_time(int number);
    void set_color(Color color);

    std::string get_name();
    std::string get_origin();
    int get_height();
    std::string get_weapon();
    int get_horn_count();
    int get_time();
    Color get_color();

    friend std::ostream& operator << (std::ostream& out, const Demon& demon)
    {
        out << demon.name << "\n";
        out << demon.origin << "\n";
        out << demon.height << "\n";
        out << demon.weapon << "\n";
        out << demon.horn_сount << "\n";

        out << demon.time.count() << "\n";

        switch (demon.color)
        {
        case Color::RED:
            out << "Красный" << "\n";
            break;
        case Color::BLUE:
            out << "Синий" << "\n";
            break;
        case Color::GREEN:
            out << "Зелёный" << "\n";
            break;
        case Color::BLACK:
            out << "Чёрный" << "\n";
            break;
        case Color::WHITE:
            out << "Белый" << "\n";
            break;
        }
        return out;
    }
    friend std::istream& operator >> (std::istream& in, Demon& demon)
    {
        std::string name;
        if (in >> name)
        {
            in.ignore(255, '\n');
            demon.set_name(name);

            int num{};
            std::string str;

            std::getline(in, str);
            demon.set_origin(str);

            num = vvod_int(in, 0, 99999);
            in.ignore(255, '\n');
            demon.set_height(num);

            std::getline(in, str);
            demon.set_weapon(str);

            num = vvod_int(in, 0, 99999);
            in.ignore(255, '\n');
            demon.set_horn_count(num);

            num = vvod_int(in, 0, 99999);
            in.ignore(255, '\n');
            demon.set_time(num);

            in >> str;
            num = 3;
            if (str == "Красный")
                num = 0;
            else if (str == "Синий")
                num = 1;
            else if (str == "Зелёный")
                num = 2;
            else if (str == "Чёрный")
                num = 3;
            else if (str == "Белый")
                num = 4;
            demon.set_color(static_cast<Color>(num));
        }
        return in;
    }
};