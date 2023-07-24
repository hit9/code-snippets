// clang++ main.cc -std=c++20

#include <iostream>

#include "skiplist.hpp"

int main(void) {
    Skiplist<int> s;

    s.Put(3);
    s.Put(9);
    s.Put(1);
    s.Put(4);
    s.Put(5);
    s.Put(8);
    s.Put(7);
    s.Put(2);
    s.Put(10);

    s.Print();

    std::cout << s.Has(3) << std::endl;  // 1
    std::cout << s.Top() << std::endl;   // 1
    s.PopFirst();
    std::cout << s.Top() << std::endl;  // 2
    return 0;
}
