#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

import Vector3D;

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
bool check_coordinate(double x);
bool check_source(short x);
bool check_choice(short x);
int check_file(std::ifstream& file);
vector3D read_and_check(const char* message, bool console = true);
std::ifstream read_filename();
short task_menu();
void output_menu(std::string info);

int main()
{
    short source{};
    validation(source, *check_source, "Choose source for vector A:\n1. Console\n2. File");
    vector3D a = read_and_check("Vector A input", source == 1 ? true : false);
    validation(source, *check_source, "Choose source for vector B:\n1. Console\n2. File");
    vector3D b = read_and_check("Vector B input", source == 1 ? true : false);
    
    short choice{};
    do
    {
        choice = task_menu();
        
        vector3D res{};
        double scalar{};
        double value{};
        int cmp_key{};
        std::string answer{};

        switch (choice)
        {
        case 1:
            validation(source, *check_source, "Choose source for vector A:\n1. Console\n2. File");
            a = read_and_check("Vector A input", source == 1 ? true : false);
            break;
        case 2:
            validation(source, *check_source, "Choose source for vector B:\n1. Console\n2. File");
            b = read_and_check("Vector B input", source == 1 ? true : false);
            break;
        case 3:
            res = a + b;
            res.print();
            output_menu(res.to_string());
            break;
        case 4:
            res = a - b;
            res.print();
            output_menu(res.to_string());
            break;
        case 5:
            res = b - a;
            res.print();
            output_menu(res.to_string());
            break;
        case 6:
            validation(scalar, *check_coordinate, "Enter scalar");
            res = a * scalar;
            res.print();
            output_menu(res.to_string());
            break;
        case 7:
            validation(scalar, *check_coordinate, "Enter scalar");
            res = b * scalar;
            res.print();
            output_menu(res.to_string());
            break;
        case 8:
            value = dot(a, b);
            std::cout << value << '\n';
            output_menu(std::to_string(value));
            break;
        case 9:
            res = cross(a, b);
            res.print();
            output_menu(res.to_string());
            break;
        case 10:
            value = a.len();
            std::cout << "|A| = " << value << '\n';
            output_menu(std::to_string(value));
            break;
        case 11:
            value = b.len();
            std::cout << "|B| = " << value << '\n';
            output_menu(std::to_string(value));
            break;
        case 12:
            cmp_key = a.compare(b);
            if (cmp_key == 0)
                answer = "A = B";
            else
                if (cmp_key == 1)
                    answer = "A > B";
                else
                    answer = "A < B";
            std::cout << answer << '\n';
            output_menu(answer);
            break;
        case 13:
            if (equal_by_coord(a, b))
                answer = "A = B";
            else
                answer = "A != B";
            std::cout << answer << '\n';
            output_menu(answer);
            break;
        case 14:
            a.print();
            output_menu(a.to_string());
            break;
        case 15:
            b.print();
            output_menu(b.to_string());
            break;
        default:
            break;
        }
    } while (choice != 16);
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
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}

bool check_coordinate(double x)
{
    return true;
}

bool check_source(short x)
{
    return x >= 1 && x <= 2;
}

bool check_choice(short x)
{
    return x >= 1 && x <= 16;
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


vector3D read_and_check(const char* message, bool console)
{
    std::cout << message << '\n';
    double x{}, y{}, z{};

    if (console)
    {
        validation(x, *check_coordinate, "Enter x");
        validation(y, *check_coordinate, "Enter y");
        validation(z, *check_coordinate, "Enter z");
    }
    else
    {
        std::ifstream file = read_filename();
        file >> x >> y >> z;
        std::cout << "Successfully read from file\n";
    }
    
    return vector3D(x, y, z);
}

std::ifstream read_filename()
{
    while (true)
    {
        std::cout << "Enter filename *.txt\n>>> ";
        std::string filename{};
        std::cin >> filename;
        filename += ".txt";
        std::ifstream file(filename);
        if (check_file(file) == 1)
            return file;
        else
            std::cout << "Input error!" << '\n';
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
    }
}

short task_menu()
{
    std::cout << "\nMENU\n" <<
        "1. Change vector A\n" <<
        "2. Change vector B\n" <<
        "3. A + B\n" <<
        "4. A - B\n" <<
        "5. B - A\n" <<
        "6. A * scalar\n" <<
        "7. B * scalar\n" <<
        "8. (A, B)\n" <<
        "9. A x B\n" <<
        "10. Find length of A\n" <<
        "11. Find length of B\n" <<
        "12. Compare A and B (by length)\n" <<
        "13. Compare A and B (by coordinates)\n" <<
        "14. Print vector A\n" <<
        "15. Print vector B\n" <<
        "16. Exit\n";
    short res{};
    validation(res, *check_choice, "");
    return res;
}

void output_menu(std::string info)
{
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::string flag{};
    std::cout << "Enter /f to print answer to file\nPress Enter to continue\n";
    if (std::cin.peek() == '\n')
        return;
    else
    {
        std::cin >> flag;
        if (flag == "/f")
        {
            std::cout << "Enter filename *.txt\n>>> ";
            std::string filename{};
            std::cin >> filename;
            filename += ".txt";
            std::ofstream file(filename);
            file << info;
            std::cout << "Succsessfully printed to'" << filename << "'\n";
            file.close();
        }
    }
}
