#include <iostream>

#include "../waitlib.h"

int main() {
    std::vector<int> hand{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
                          1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    hand.resize(34);
    pattern_t pattern;
    int m = 4;
    std::vector<int> machi = list_wait(hand, pattern, m);
    for (auto &&x : machi) {
        std::cout << x << std::endl;
    }
    for (auto &&v : pattern) {
        for (auto &&x : v) {
            std::cout << ' ' << x;
        }
        std::cout << std::endl;
    }
    for (auto &&v : pattern) {
        int type = v.front(), win_tile = v.back();
        if (type == NORMAL) {
            for (int i = 0; i < m; i++) {
                bool contain_win_tile = false;
                int tiles[3];
                for (int j = 0; j < 3; j++) {
                    tiles[j] = v[3 * i + j + 1];
                    if (tiles[j] == win_tile) {
                        contain_win_tile = true;
                    }
                }
                if (contain_win_tile) {
                    for (int j = 0; j < 3; j++) {
                        if (tiles[j] == win_tile) {
                            win_tile = -1;
                        } else {
                            std::cout << tiles[j];
                        }
                    }
                    std::cout << ' ';
                }
                win_tile = v.back();
            }
            if (v[3 * m + 1] == v.back()) {
                std::cout << v.back();
            }
        } else if (type == PAIR7) {
            std::cout << u8"七対子" << win_tile;
        } else {
            int count_win_tile = 0;
            for (int i = 1; i <= 3 * m + 2; i++) {
                if (v[i] == win_tile) count_win_tile++;
            }
            if (count_win_tile == 2) {
                std::cout << u8"国士無双13面" << win_tile;
            } else {
                std::cout << u8"国士無双1面" << win_tile;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
