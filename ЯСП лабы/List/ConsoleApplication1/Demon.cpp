#include "Demon.h"

std::string Demon::get_name()
{
    return name;
}

std::string Demon::get_origin()
{
    return origin;
}

int Demon::get_height()
{
    return height;
}

std::string Demon::get_weapon()
{
    return weapon;
}

int Demon::get_horn_count()
{
    return horn_ñount;
}

int Demon::get_time()
{
    return time.count();
}

Color Demon::get_color()
{
    return color;
}


void Demon::set_name(std::string other_name)
{
    name = other_name;
}

void Demon::set_origin(std::string other_origin)
{
    origin = other_origin;
}

void Demon::set_height(int other_height)
{
    height = other_height;
}

void Demon::set_weapon(std::string other_weapon)
{
    weapon = other_weapon;
}

void Demon::set_horn_count(int other_horn_count)
{
    horn_ñount = other_horn_count;
}

void Demon::set_time(int number)
{
    Duration other_time(number);
    time = other_time;
}

void Demon::set_color(Color other_color)
{
    color = other_color;
}