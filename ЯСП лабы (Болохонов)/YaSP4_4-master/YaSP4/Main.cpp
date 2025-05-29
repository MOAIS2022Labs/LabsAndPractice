import RandList;
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator>
#include <numeric>

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
int check_file(std::fstream& file);
void print_file_info(std::fstream& file, std::string file_name);
short source_menu();
short task_menu();
std::fstream* fill_file_for(std::string file_name, int size, int radius);
std::fstream* fill_file_generate(std::string file_name, int size, int radius);


int main()
{	
    srand(time(NULL));
    short source{}; 
    while (source != 3)
    {
        source = source_menu();
        std::string file_name{};
        std::fstream* file = nullptr;
        switch (source)
        {
        case 1:     // new random file
        {
            int size{}, radius{};
            validation(file_name, [](std::string x) {return true; }, "Enter a file name");
            validation(size, [](int x) {return x > 0; }, "Enter a count of integers");
            validation(radius, [](int x) {return x > 0; }, "Enter a radius (-r, r)");
            std::cout << "Select fill method\n"
                << "1. for()\n" << "2. std::generate_n\n";
            short choice{};
            validation(choice, [](int x) {return x >= 1 && x <= 2; }, "");
            file = (choice == 1) ? fill_file_for(file_name, size, radius) : fill_file_generate(file_name, size, radius);
            std::cout << "'" << file_name << "' generated successfully\n";
            break;
        }
        case 2:     // existing file
        {
            short file_flag{};
            do
            {
                validation(file_name, [](std::string x) {return true; }, "Enter a file name");
                file = new std::fstream(file_name, std::fstream::out | std::fstream::in | std::fstream::app);
                file_flag = check_file(*file);
                print_file_info(*file, file_name);
            } while (file_flag != 1);
            break;
        }
        case 3:
            exit(0);
        }
        short task{};
        short output_choice{};
        RandList list(*file);
        (*file).close();
        delete file;
        file = nullptr;
        while (task != 4)
        {
            task = task_menu();
            switch (task)
            {
            case 1:
            {
                RandList list1 = list.modify_for();
                RandList list2 = list.modify_for_each();
                RandList list3 = list.modify_transform();
                validation(output_choice, [](short x) {return x >= 1 && x <= 2; }, "Choose output method:\n1. To Console\n2. To File\n");
                if (output_choice == 1)
                {
                    std::cout <<
                        "\nYour list\n" << list <<
                        "\nmodify_for:\n" << list1 <<
                        "\nmodify_for_each\n" << list2 <<
                        "\nmodify_transform\n" << list3 << '\n';
                }
                else
                {
                    validation(file_name, [](std::string x) {return true; }, "Enter file name");
                    std::ofstream file_out(file_name);
                    file_out <<
                        "\nYour list\n" << list <<
                        "\nmodify_for:\n" << list1 <<
                        "\nmodify_for_each\n" << list2 <<
                        "\nmodify_transform\n" << list3 << '\n';
                    file_out.close();
                }
                break;
            }
            case 2:
            case 3:
            {
                validation(output_choice, [](short x) {return x >= 1 && x <= 2; }, "Choose output method:\n1. To Console\n2. To File\n");
                if (output_choice == 1)
                {
                    std::cout << "Your list\n" << list;
                    std::cout << (task == 2 ? "\nSum of all elements: " : "\nAverage value: ");
                    std::cout << (task == 2 ? list.sum() : list.avg()) << '\n';
                }
                else
                {
                    validation(file_name, [](std::string x) {return true; }, "Enter file name");
                    std::ofstream file_out(file_name);
                    file_out << (task == 2 ? list.sum() : list.avg());
                    file_out.close();
                }
                break;
            }
            case 4:
                break;
            }
        }
    }
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

int check_file(std::fstream& file)
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

void print_file_info(std::fstream& file, std::string file_name)
{
    switch (check_file(file))
    {
    case -1:
        std::cout << "File not found!\n";
        break;
    case 0:
        std::cout << "File is empty!\n";
        break;
    default:
        std::cout << "File '" << file_name << "' read successfully\n";
        break;
    }
}

short source_menu()
{
    std::cout << "=== SOURCE MENU ===\n"
        << "1. Make a new file\n"
        << "2. Your file\n"
        << "3. Exit\n";
    short res{};
    validation(res, [](short x) {return x >= 1 && x <= 3; }, "");
    return res;
}

short task_menu()
{
    std::cout << "=== TASK MENU ===\n"
        << "1. Do the task\n"
        << "2. Find a sum\n"
        << "3. Find an average value\n"
        << "4. Change source\n";
    short res{};
    validation(res, [](short x) {return x >= 1 && x <= 4; }, "");
    return res;
}

std::fstream* fill_file_for(std::string file_name, int size, int radius)
{
    std::fstream* file = new std::fstream(file_name, std::ios::out | std::ios::in | std::fstream::trunc);

    for (size_t i = 0; i < size; i++)
    {
        int x = (rand() % (2 * radius + 1)) - radius;
        *file << x << ' ';
    }
    
    (*file).clear();
    (*file).seekg(0);
    return file;
}

std::fstream* fill_file_generate(std::string file_name, int size, int radius)
{
    std::fstream* file = new std::fstream(file_name, std::fstream::out | std::fstream::in | std::fstream::trunc);
    std::generate_n(std::ostream_iterator<int>(*file, " "), size, [&]() {return rand() % (2 * radius + 1) - radius; });

    (*file).clear();
    (*file).seekg(0);

    return file;
}

