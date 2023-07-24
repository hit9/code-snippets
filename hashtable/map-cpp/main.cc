#include <iostream>

#include "map.hpp"

int main(void) {
    Map<int, int, 5> m;
    std::cout << m.Cap() << std::endl;
    std::cout << std::boolalpha << m.Set(5, 10) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(6, 12) << std::endl;  // true
    std::cout << std::boolalpha << m.Set(7, 13) << std::endl;  // true
    std::cout << m.Get(5) << std::endl;                        // 10
    std::cout << m.Get(6) << std::endl;                        // 12
    std::cout << m.Get(7) << std::endl;                        // 13
    std::cout << m.Size() << std::endl;                        // 3
    std::cout << m.Pop(7) << std::endl;                        // 13
    std::cout << m.Size() << std::endl;                        // 2
    return 0;
}
