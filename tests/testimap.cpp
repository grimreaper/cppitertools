#include <imap.hpp>

#include <vector>
#include <iostream>

using iter::imap;

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6};
    std::vector<int> vec2 = {10, 20, 30, 40, 50, 60};
    for (auto i : imap([] (int x, int y) { return x + y; }, vec1, vec2)) {
        std::cout << i << '\n';
    }

    std::vector<int> vec3 = {100, 200, 300, 400, 500, 600};
    for (auto i : imap([] (int a, int b, int c) { return a + b + c; }, 
                vec1, vec2, vec3)) {
        std::cout << i << '\n';
    }

    for (auto i : imap([] (int i) {return i * i; }, vec1)) {
        std::cout << i << '\n';
    }

    return 0;
}
