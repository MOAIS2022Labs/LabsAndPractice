#include <iostream>
#include <fstream>
#include <string>

import Sequence;
import Vector3D;

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
int check_file(std::ifstream& file);
std::ifstream read_filename();
bool check_type(short x) { return x >= 1 && x <= 4; }
bool check_choice(short x) { return x >= 1 && x <= 11; }
bool check_coordinate(double x) { return true; }
short type_menu();
short task_menu();

template<typename T>
void process();

template<typename T>
T read_elem_from_keyboard(Sequence<T>& seq);



int main()
{
    short choice{}, type{};
    do
    {
        type = type_menu();
        switch (type)
        {
        case 1:
            process<int>();
            break;
        case 2:
            process<std::string>();
            break;
        case 3:
            process<vector3D>();
            break;
        }
    } while (type != 4);

}



template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
    std::cout << message << "\n>>> ";
    while (!(std::cin >> x && condition(x)))
    {
        std::cout << "Input error!" << '\n';
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << message << "\n>>> ";
    }
}

template<typename T>
void process()
{
    std::ifstream inp_file = read_filename();
    std::ofstream out_file("output.txt");
    Sequence<T> seq(inp_file);
    int pos{};
    T elem;
    inp_file.close();
    short choice{};
    do
    {
        choice = task_menu();
        switch (choice)
        {
        case 1:
            seq.print();
            break;
        case 2:
            seq.print("Sequence:", " ", out_file);
            std::cout << "Successfully printed to 'output.txt'\n";

            break;
        case 3:
            elem = read_elem_from_keyboard(seq);
            seq.add_to_tail(elem);
            std::cout << "The element has been appended\n";
            break;
        case 4:
            elem = read_elem_from_keyboard(seq);
            pos = seq.get_pos(elem);
            if (pos != -1)
                std::cout << "Index: " << pos << '\n';
            else std::cout << "There's no your element\n";
            break;
        case 5:
        {
            std::cout << "Finding subsequence from file\n";
            std::ifstream sub_f = read_filename();
            Sequence<T> sub(sub_f);
            pos = seq.get_pos(sub);
            sub.print("Subsequence:");
            if (pos != -1)
                std::cout << "Index: " << pos << '\n';
            else std::cout << "There's no your subsequence\n";
            break;
        }
        case 6:
        {
            size_t size = seq.get_size();
            validation(pos, [size](int x) { return x < size; }, "Enter index");
            std::cout << seq.get_elem(pos) << '\n';
            break;
        }
        case 7:
        {
            size_t size = seq.get_size();
            elem = read_elem_from_keyboard(seq);
            validation(pos, [size](int x) { return x < size; }, "Enter index");
            seq.set_elem(elem, pos);
            std::cout << "Changed\n";
            break;
        }
        case 8:
        {
            size_t size = seq.get_size();
            validation(pos, [size](int x) { return x < size; }, "Enter index");
            seq.del_elem(pos);
            std::cout << "Deleted\n";
            break;
        }
        case 9:
        {
            size_t size = seq.get_size();;
            validation(pos, [size](int x) { return x < size; }, "Enter index");
            size_t length;
            validation(length, [size, pos](int x) {return x < size - pos; }, "Enter length");
            Sequence sub = seq.subseq(pos, length);
            sub.print("Subsequence:");
            break;
        }
        case 10:
            choice = 11;
            break;
        case 11:
            exit(0);
        }
    } while (choice != 11);
}

template<typename T>
T read_elem_from_keyboard(Sequence<T>& seq)
{
    T res;
    if constexpr (std::is_same<T, vector3D>::value)
    {
        double x{}, y{}, z{};
        validation(x, *check_coordinate, "Enter x: ");
        validation(y, *check_coordinate, "Enter y: ");
        validation(z, *check_coordinate, "Enter z: ");
        res = vector3D(x, y, z);
    }
    else
    {
        if (std::is_same<T, int>::value)
            validation(res, [](T x) { return true; }, "Enter int: ");
        if (std::is_same<T, std::string>::value)
            validation(res, [](T x) { return true; }, "Enter string: ");
    }
    return res;
}

int check_file(std::ifstream& file)
{
    int res = 1;
    if (!file)
    {
        res = -1; // file not found
    }
    else
        if (file.peek() == EOF)
            res = 0; // file is empty
    return res;
}

std::ifstream read_filename()
{
    while (true)
    {
        std::cout << "Enter filename (with spec)\n>>> ";
        std::string filename{};
        std::cin >> filename;
        std::ifstream file(filename);
        if (check_file(file) == 1)
            return file;
        else
            std::cout << "Input error!" << '\n';
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
    }
}

short type_menu()
{
    std::cout << "Choose the type of Sequence:\n" <<
        "1. int\n" <<
        "2. string\n" <<
        "3. vector3D\n" <<
        "4. Exit\n";
    short res{};
    validation(res, *check_type, "");
    return res;
}

short task_menu()
{
    std::cout << "\n *-<===> Task Menu <===>-* \n" <<
        "1. Print to console\n" <<
        "2. Print to file\n" <<
        "3. Append\n" <<
        "4. Find index of the element\n" <<
        "5. Find the first index of subsequence\n" <<
        "6. Get element by index\n" <<
        "7. Change element by index\n" <<
        "8. Delete element by index\n" <<
        "9. Make subsequence\n" << 
        "10. Change type\n" << 
        "11 Exit\n";
    short res{};
    validation(res, *check_choice, "");
    return res;
}

