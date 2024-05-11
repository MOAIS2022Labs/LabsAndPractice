#include <iostream>
#include <memory>

struct ELEM
{
    int x;
    std::unique_ptr<int> y;
    int* z;

    ELEM(int x, int y, int z) : x(x)
    {
        this->y = std::move(std::make_unique<int>(y));
        this->z = new int(z);
    }

    ~ELEM()
    {
        delete z; // удаление идёт чисто динамических ресурсов
    }

    void print()
    {
        std::cout << x << *y << *z << '\n';
    }

};

std::unique_ptr<int> function(int x)
{
    // return std::unique_ptr<int>(new int(x));
    return std::make_unique<int>(x);
}

int main()
{
    // ELEM elem (1,2,3);
    // elem.print();

    // int *ptr_int = new int(5);
    // std::unique_ptr<int> ptr1 = std::make_unique<int>(*ptr_int);
    // std::unique_ptr<int> ptr2 = std::make_unique<int>(*ptr_int);

    // std::cout << ptr_int <<'\n';
    // std::cout<< ptr1.get() << '\n';
    // std::cout<< ptr2.get() << '\n';

    // int *ptr_int = new int(5);
    // std::shared_ptr<int> ptr1(ptr_int);
    // {
    //     auto ptr2 = ptr1;
    // }


    std::unique_ptr<int> ptr1 = function(5);
    std::unique_ptr<int> ptr2 = function(7);

    std::unique_ptr<int[]> arr1(new int[10]);
    auto arr2 = std::make_unique<int[]>(10);

    std::shared_ptr<int[]> arr2(new int[10], std:: default_delete<int[]>());

    std::cin.get();
    return 0;
}