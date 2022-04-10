#include <iostream>

#include "../waitlib.h"

int main() {
    std::vector<int> hand{0, 3, 3, 3, 2, 2};
    hand.resize(34);
    std::vector<std::vector<int>> pattern;
    std::vector<int> machi = list_wait(hand, pattern);
    for (auto &&x : machi) {
        std::cout << x << std::endl;
    }
    for (auto &&v : pattern) {
        for (auto &&x : v) {
            std::cout << ' ' << x;
        }
        std::cout << std::endl;
    }
    return 0;
}
