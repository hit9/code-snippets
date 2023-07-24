#include <iostream>

#include "map.hpp"

int main(void) {
    Map<int, int> m;
    std::cout << m.Cap() << std::endl;
    std::cout << std::boolalpha << m.Set(5, 10) << std::endl;   // true
    std::cout << std::boolalpha << m.Set(6, 12) << std::endl;   // true
    std::cout << std::boolalpha << m.Set(7, 13) << std::endl;   // true
    std::cout << m.Get(5) << std::endl;                         // 10
    std::cout << m.Get(6) << std::endl;                         // 12
    std::cout << m.Get(7) << std::endl;                         // 13
    std::cout << m.Size() << std::endl;                         // 3
    std::cout << m.Pop(7) << std::endl;                         // 13
    std::cout << m.Size() << std::endl;                         // 2
    std::cout << std::boolalpha << m.Set(8, 14) << std::endl;   // true
    std::cout << std::boolalpha << m.Set(9, 15) << std::endl;   // true
    std::cout << std::boolalpha << m.Set(10, 16) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(11, 17) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(12, 18) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(13, 19) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(14, 20) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(15, 21) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(16, 22) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(17, 23) << std::endl;  // true
    std::cout << m.Cap() << std::endl;                          // 16
    std::cout << m.Size() << std::endl;                         // 10

    return 0;
}
