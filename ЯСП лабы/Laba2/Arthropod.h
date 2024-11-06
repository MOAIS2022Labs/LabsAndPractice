#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Utils.h"
#include <unordered_set>

enum Class_type {Насекомое=1, Ракообразное=2, Паукообразное=3, Многоножка=4 };
//насекомые, ракообразные, паукообразные и многоножки
class Arthropod {
private:
    std::string type;
    time_t date;
    Class_type class_animal;
    int num_limbs;
    int num_wings;
    double max_length;
    double max_weight;
    
public:
    Arthropod(){
        type = {};
        date = {};
        class_animal = {};
        num_limbs = {};
        num_wings = {};
        max_length = {};
        max_weight = {};
    }
    Arthropod(const Arthropod& other);
    Arthropod(std::string type, time_t date, Class_type class_animal,
        int num_limbs, int num_wings, double max_lenght, double max_weight) : type(type), date(date),
        class_animal(class_animal), num_limbs(num_limbs), num_wings(num_wings), max_length(max_lenght), max_weight(max_weight) {}

    std::string get_type() const;
    void set_type(const std::string& new_type);

    time_t get_date() const;
    void set_date(const time_t& new_date);

    Class_type get_class_animal() const;
    std::string get_class_animal_string() const;
    void set_class_animal();
    bool set_class_animal(std::string new_class_animal);

    int get_num_limbs() const;
    void set_num_limbs(int new_num_limbs);

    int get_num_wings() const;
    void set_num_wings(int new_num_wings);

    double get_max_length() const;
    void set_max_length(double new_max_length);

    double get_max_weight() const;
    void set_max_weight(double new_max_weight);
    void read_console()
    {
        std::cout << "Введите название вида\n-->";
        std::cin.ignore();
        std::getline(std::cin, type);
        std::cout << "Введите дату открытия вида\n-->";
        is_valid_input(date);
        std::cout << "Доступны классы: Насекомое, Ракообразное,"
            " Паукообразное, Многоножка\n";
        std::cout << "Введите класс\n-->";
        set_class_animal();
        std::cout << "Введите число конечностей\n-->";
        num_limbs = input_in_range(0, INT_MAX);
        std::cout << "Введите число крыльев\n-->";
        num_wings = input_in_range(0, INT_MAX);
        std::cout << "Введите максимальную длину\n-->";
        max_length = input_in_range(0.0, DBL_MAX);
        std::cout << "Введите максимальную массу\n-->";
        max_weight = input_in_range(0.0, DBL_MAX);
    }
    void print_console();
};
bool operator==(const Arthropod& first, const Arthropod& second);
std::ostream& operator<<(std::ostream& os, const Arthropod& elem);
std::istream& operator>>(std::istream& is, Arthropod& elem);

template <>
struct std::hash<Arthropod> {

    std::size_t operator()(const Arthropod& customType) const {
   
        return std::hash<std::string>()(customType.get_type());
    }
};