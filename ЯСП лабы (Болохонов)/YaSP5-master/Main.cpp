#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <deque>
#include <functional>
#include <Windows.h>

import Manuscript;
import Library;

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
short check_file(std::fstream& file);
void fill_from_file(Library<Manuscript>& library);
void print_to_file(Library<Manuscript>& library);
void fill_from_console(Library<Manuscript>& library);
short source_menu();
short task_menu();
short select_menu();
void hello_message();
void show_sample();


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Library<Manuscript> library;
    short source_choice{};
    bool first_enter{ true };
    do
    {
        source_choice = source_menu();
        switch (source_choice)
        {
        case 1:
            fill_from_file(library);
            break;
        case 2:
            fill_from_console(library);
            break;
        default: break;
        }
        if (source_choice != 3)
        {
            if (first_enter)
            {
                hello_message();
                first_enter = false;
            }
            short action_choice{};
            do
            {
                try
                {
                    action_choice = task_menu();
                    switch (action_choice)
                    {
                    case 1:
                        std::cout << library;
                        break;
                    case 2:
                        print_to_file(library);
                        break;
                    case 3:
                    {
                        show_sample();
                        std::cin.ignore(std::cin.rdbuf()->in_avail());
                        std::istream_iterator<Manuscript> it(std::cin);
                        library.add_left(*it);
                        break;
                    }
                    case 4:
                    {
                        show_sample();
                        std::cin.ignore(std::cin.rdbuf()->in_avail());
                        std::istream_iterator<Manuscript> it(std::cin);
                        library.add_right(*it);
                        break;
                    }
                    case 5:
                        library.remove_left();
                        break;
                    case 6:
                        library.remove_right();
                        break;
                    case 7:
                    {
                        show_sample();
                        std::cin.ignore(std::cin.rdbuf()->in_avail());
                        std::istream_iterator<Manuscript> it(std::cin);
                        library.change_left(*it);
                        break;
                    }
                    case 8:
                    {
                        show_sample();
                        std::cin.ignore(std::cin.rdbuf()->in_avail());
                        std::istream_iterator<Manuscript> it(std::cin);
                        library.change_right(*it);
                        break;
                    }
                    case 9:
                    {
                        short select_choice = select_menu();
                        Library<Manuscript> tmp_lib{};
                        switch (select_choice)
                        {
                        case 1:
                        {
                            int size1{};
                            int size2{};
                            validation(size1, [](int x) {return x >= 0; }, "От скольки символов ищем?");
                            validation(size2, [size1](int x) {return x > size1; }, "И до скольки?");
                            tmp_lib = library.selection([size1, size2](const Manuscript& elem)
                                { return size2 > elem.get_text().size() && size1 <= elem.get_text().size(); });
                            break;
                        }
                        case 2:
                        {
                            std::cin.ignore(std::cin.rdbuf()->in_avail());
                            std::cout << "Пиши даты по образцу: 1980-05-01\n";
                            std::chrono::year_month_day date1{}, date2{};
                            bool fl{ false };
                            while (!fl)
                            {
                                std::cout << "С какой даты ищем?\n";
                                std::chrono::from_stream(std::cin, "%F", date1);
                                std::cin.ignore();
                                if (std::cin.fail())
                                    throw std::invalid_argument("Недопустимое значение даты\n");
                                std::cout << "По какую?\n";
                                std::chrono::from_stream(std::cin, "%F", date2);
                                if (std::cin.fail())
                                    throw std::invalid_argument("Недопустимое значение даты\n");
                                if (date1 < date2)
                                    fl = true;
                                else
                                    std::cout << "Ты не похож на Бенджамина Баттона, странник!\n";
                            }
                            tmp_lib = library.selection([date1, date2](const Manuscript& elem)
                                { return date2 > elem.get_date() && date1 <= elem.get_date(); });
                            break;
                        }
                        case 3:
                        {
                            std::cout << "Чьи рукописи тебе интересны?: ";
                            std::cin.ignore(std::cin.rdbuf()->in_avail());
                            std::string str{};
                            std::getline(std::cin, str);
                            tmp_lib = library.selection([str](const Manuscript& elem)
                                { return str == elem.get_author(); });
                            break;
                        }
                        }
                        std::cout << tmp_lib;
                        break;
                    }
                    case 10:
                        std::cout << "В моей библиотеке уже " << library.size() << " накопилось...\n";
                        break;
                    }
                }
                catch (std::invalid_argument exception)
                {
                    std::cout << "Ошибка чтения! " << exception.what() << '\n';
                }
                catch (std::out_of_range exception)
                {
                    std::cout << "Ошибка: " << exception.what() << '\n';
                }
                
            } while (action_choice != 11);
        }
    } while (source_choice != 3);
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

short check_file(std::fstream& file)
{
    short res = 1;
    if (!file)
    {
        res = -1; // file not found
    }
    else
        if (file.peek() == EOF)
            res = 0; // file is empty
    return res;
}

void fill_from_file(Library<Manuscript>& library)
{
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::fstream file;
    std::string filename;
    std::cout << "Введите имя файла\n>>> ";
    std::cin >> filename;
    file = std::fstream(filename, std::fstream::out | std::fstream::in | std::fstream::app);
    int is_file = check_file(file);
    switch (is_file)
    {
    case -1:
        std::cout << "Ошибка\n";
        break;
    case 0:
        std::cout << "Файл пуст\n";
        break;
    default:
        try
        {
            file >> library;
        }
        catch (std::invalid_argument exception)
        {
            std::cout << "Ошибка чтения файла! " << exception.what() << '\n';
        }
        break;
    }
    file.close();
}

void print_to_file(Library<Manuscript>& library)
{
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::string filename;
    std::cout << "Введите имя файла:\n-> ";
    std::cin >> filename;
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла для записи!\n";
        return;
    }
    try
    {
        file << library;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка при записи в файл: " << e.what() << '\n';
    }
    file.close();
}

void fill_from_console(Library<Manuscript>& library)
{
    show_sample();
    try
    {
        std::cin >> library;
    }
    catch (std::invalid_argument exception)
    {
        std::cout << "Неправильно! Пример для кого показываю? " << exception.what() << '\n';
    }
}

short source_menu()
{
    std::cout << "<======= ЗАГРУЗИТЕ ДАННЫЕ =======>\n" 
        << "1. Из файла\n"
        << "2. Вручную\n"
        << "3. Выход\n";
    short res{};
    validation(res, [](short x) {return x >= 1 && x <= 3; }, "");
    return res;
}

short task_menu()
{
    std::cout
        << "\n1. Прочесть рукописи\n"
        << "2. Переписать рукописи себе\n"
        << "3. Добавить рукопись слева\n"
        << "4. Добавить рукопись справа\n"
        << "5. Удалить рукопись слева\n"
        << "6. Удалить рукопись справа\n"
        << "7. Изменить рукопись слева\n"
        << "8. Изменить рукопись справа\n"
        << "9. Выбрать рукописи\n"
        << "10. [ВОПРОС] А сколько рукописей в твоей библиотеке?\n"
        << "11. Выход";
    short res{};
    validation(res, [](short x) {return x >= 1 && x <= 11; }, "");
    return res;
}

short select_menu()
{
    std::cout << "Как выбирать будем?\n"
        << "1. По количеству символов\n"
        << "2. По дате создания\n"
        << "3. По автору\n";
    short res{};
    validation(res, [](short x) {return x >= 1 && x <= 4; }, "");
    return res;
}

void hello_message()
{
    std::cout << "<======= ОТКРЫТА НОВАЯ ЛОКАЦИЯ =======>\n"
        << "Монах:  Добро пожаловать в древнюю библиотеку, путник.\n"
        << "        Рад, что ещё одна заблудшая душа приблизилась к вечным истинам...\n"
        << "        За сотни лет, что я провёл в этой библиотеке, я успел переписать все\n"
        << "        рукописи в этот великий-книга-толмут. Ты можешь прочесть любую рукопись,\n"
        << "        но учти, что если ты пожелаешь забрать, поменять или добавить рукопись в мою\n"
        << "        библиотеку, выбери место слева или справа от меня. Увы, я слишком стар,\n"
        << "        чтобы ходить дальше...\n"
        << "        Ну, так чего изволишь?\n\n";
}

void show_sample()
{
    std::cout << "Пиши как показано\n\n";
    std::cout << "Табличка\nИмя автора\n1890-05-21\nТекст\n" <<
        "Вместо таблички также может быть: Пергамент, Свиток или Книга\n\n";
}
