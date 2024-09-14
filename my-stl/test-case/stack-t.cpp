#include "../stack.cpp"
#include <iostream>

int main() {
    MyStl::stack<int> p(10);
    std::cout << p;
    return 0;
}