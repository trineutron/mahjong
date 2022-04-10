#include <iostream>

#include "../waitlib.h"

int main() {
    std::vector<int> hand{0, 2, 3, 2, 1, 2, 0, 3};
    hand.resize(34);
    std::vector<int> machi = list_wait(hand);
    for (auto &&x : machi) {
        std::cout << x << std::endl;
    }
    return 0;
}
