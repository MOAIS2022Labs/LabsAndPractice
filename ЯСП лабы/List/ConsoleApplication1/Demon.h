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
            std::cout << "������. ���������� �����.\n --> ";
            stream.clear();
            stream.ignore(stream.rdbuf()->in_avail());
        }
    }
    return isCorrectInfo;
}

// �������� �����
inline int vvod_int(std::istream& stream, int min, int max)
{
    int choice;
    while (!is_valid_input(stream, choice) || !(choice >= min && choice <= max))
        std::cout << "������.\n --> ";
    return choice;
}

// ��� std::chrono::duration ������������ ����� �������� �������, ������� ����� ���� ����������� � ��������� �������� ��������� �������. 
// � ������ ������, std::chrono::duration<int, std::ratio<3600>> ��������, ��� Duration �������� ���������� �������, �������������� ����� ������(int),
// ��� ������ ������� ����� 3600 �������� (�.�. 1 ���).
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
    int horn_�ount;
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
        out << demon.horn_�ount << "\n";

        out << demon.time.count() << "\n";

        switch (demon.color)
        {
        case Color::RED:
            out << "�������" << "\n";
            break;
        case Color::BLUE:
            out << "�����" << "\n";
            break;
        case Color::GREEN:
            out << "������" << "\n";
            break;
        case Color::BLACK:
            out << "׸����" << "\n";
            break;
        case Color::WHITE:
            out << "�����" << "\n";
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
            if (str == "�������")
                num = 0;
            else if (str == "�����")
                num = 1;
            else if (str == "������")
                num = 2;
            else if (str == "׸����")
                num = 3;
            else if (str == "�����")
                num = 4;
            demon.set_color(static_cast<Color>(num));
        }
        return in;
    }
};