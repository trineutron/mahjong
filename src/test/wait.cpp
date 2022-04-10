#include <iostream>

#include "../waitlib.h"

int main() {
    std::vector<int> hand{0, 3, 1};
    hand.resize(34);
    pattern_t pattern;
    std::vector<int> machi = list_wait(hand, pattern, 1);
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
