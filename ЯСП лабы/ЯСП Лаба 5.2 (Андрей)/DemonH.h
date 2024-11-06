#pragma once

#include <ctime>
#include "HelpH.h"

enum Color { Red, Blue, Green, White };

struct Demon
{
private:
    std::string name;
    std::string origin;
    int height;
    std::string weapon;
    int horn_сount;
	std::time_t time;
	Color color;
public:
    void set_name(std::string name);
    void set_origin(std::string origin);
	void set_weapon(std::string weapon);

    void set_height(int height);  
    void set_horn(int сount);
    void set_time(int number);
    void set_color(Color color);

    std::string get_name();
    std::string get_origin();
	std::string get_weapon();

    int get_height();
    int get_horn();
    int get_time();

    Color get_color();
	int define_color();

    friend std::ostream& operator << (std::ostream& out, const Demon& demon)
    {		
        out << demon.name << "\n";
        out << demon.origin << "\n";
        out << demon.height << "\n";
        out << demon.weapon << "\n";
        out << demon.horn_сount << "\n";    
		out << demon.time << "\n";

        switch (demon.color)
        {
        case Color::Red:
            out << "Красный" << "\n";
            break;
        case Color::Blue:
            out << "Синий" << "\n";
            break;
        case Color::Green:
            out << "Зелёный" << "\n";
            break;
		default:
			out << "Белый" << "\n";
            break;
        }
        return out;
    }

    friend std::istream& operator >> (std::istream& in, Demon& demon)
    {
        std::string str;
		int num;
        if (in >> str)
        {
            in.ignore(255, '\n');
            demon.set_name(str);

            std::getline(in, str);
            demon.set_origin(str);

            num = read_check_int(in, 0, 1000);
            in.ignore(255, '\n');
            demon.set_height(num);

            std::getline(in, str);
            demon.set_weapon(str);

            num = read_check_int(in, 0, 1000);
            in.ignore(255, '\n');
            demon.set_horn(num);

            num = read_check_int(in, 0, 1000);
            in.ignore(255, '\n');
            demon.set_time(num);

            in >> str;
            
            if (str == "Красный")
                num = 0;
            else if (str == "Синий")
                num = 1;
            else if (str == "Зелёный")
                num = 2;
            else 
                num = 3;
            demon.set_color(static_cast<Color>(num));
        }
        return in;
    }
};

void read_demon(std::istream& in, Demon& demon);

bool check_demons_file(std::string file_name);


