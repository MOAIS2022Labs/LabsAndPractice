#include <map>
#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    // словарь - это контейнер, в котором элементы хранятся по принципу "ключ-значение"
    std::unordered_map<std::string, unsigned int> umap; // неупорядоченный словарь

    std::map<std::string, unsigned int> map // упорядоченный словарь
        {
             // варианты задания прары "ключ-значение":
            std::pair<std::string, unsigned int>{"one", 1},
            std::make_pair("two", 2),
            {"three", 3}
        };
    map["one"] = 11;   // обращение к значению по ключу и его изменение
    map.at("one") = 7; // более безопасный способ обращения к элементу

    // просмотр элементов в словаре:
    for (auto iter{map.cbegin()}; iter != map.cend(); ++iter) // через итераторы
    {
        std::cout << iter->first << ' ' << iter->second << '\n'; // итераторы в словаре - константые!
    }

    for (const auto &elem : map) // обход через for each (по ссылке, т.к. работаем со структурой pair)
    {
        std::cout << elem.first << ' ' << elem.second << '\n';
    }

    for (const auto &[word, number] : map) // разыменование (доступно с 17 стандарта С++)
    {
        std::cout << word << ' ' << number << '\n';
    }

    // методы работы со словарём
    // 1) добавление:
    map["four"] = 4; // если элемент есть в коллекции, то изменится значение, а если нет, то элемент добавится
    map.insert({"four", 4});
    map.emplace("four", 4); // через emplace объект задаётся сразу на месте (быстрее, чем insert)
    // 2) удаление
    map.erase("two"); // по ключу
    map.erase(next(map.begin())); // по итератору 
    map.erase(map.begin(), prev(map.end())); // несколько элементов по итераторам начала и конца

    map.size(); // 3) размер словаря
    map.empty(); // 4) проверка на пустоту
    map.count("elem"); // 5) проверка наличия элемента: 1 - есть, 0 - нет
    map.find("one"); // 6) принимает константый ключ; возвращает итератор, который соответствует данному ключу
    std::cin.get();
    return 0;
}