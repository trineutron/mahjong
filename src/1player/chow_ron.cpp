#include <iostream>
#include <random>
#include <vector>

#include "xrand.h"

constexpr int kind = 34, tile = 4 * kind, player = 4, turn = 18, iter = 1000000;

const std::vector<int> value{1, 2, 3, 4, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 4, 3, 2,
                             1, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0};

xrand rng;
std::uniform_int_distribution<> dist(0, tile - 1);

bool contain_chow(const std::vector<int> &hand) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (hand.at(9 * i + j) and hand.at(9 * i + j + 1) and
                hand.at(9 * i + j + 2)) {
                return true;
            }
        }
    }
    return false;
}

void simulate(std::vector<int> &magic, std::vector<int> &real) {
    std::vector<int> seen(kind), hand(kind);
    std::vector<bool> draw(tile);
    bool win_seen = false, win_real = false;
    for (int i = 0; i < 2; i++) {
        int k = dist(rng);
        while (draw.at(k)) {
            k = dist(rng);
        }
        draw.at(k) = true;
        seen.at(k / 4)++;
        hand.at(k / 4)++;
    }
    for (int i = 0; i < turn; i++) {
        for (int p = 0; p < player; p++) {
            int k = dist(rng);
            while (draw.at(k)) {
                k = dist(rng);
            }
            draw.at(k) = true;
            seen.at(k / 4)++;
            hand.at(k / 4)++;
            if (not win_seen and contain_chow(seen)) {
                win_seen = true;
            }
            if (p != 3) {
                seen.at(k / 4)--;
            }
            if (not win_real and contain_chow(hand)) {
                win_real = true;
            }
            if (p != 3 or win_real or hand.at(k / 4) >= 2 or
                value.at(k / 4) == 0) {
                hand.at(k / 4)--;
            } else {
                auto v = value;
                for (int j = 0; j < 3; j++) {
                    for (int l = 0; l < 7; l++) {
                        for (int m = 0; m < 3; m++) {
                            for (int n = 0; n < 3; n++) {
                                if (m == n) {
                                    continue;
                                }
                                v.at(9 * j + l + m) +=
                                    10 * hand.at(9 * j + l + n);
                            }
                        }
                    }
                }

                int x = -1;
                for (int j = 0; j < kind; j++) {
                    if (hand.at(j) == 0) {
                        continue;
                    }
                    if (hand.at(j) >= 2 or v.at(j) == 0) {
                        x = j;
                        break;
                    }
                    if (x < 0 or v.at(j) < v.at(x)) {
                        x = j;
                    }
                }
                hand.at(x)--;
            }
            if (p == 3 and win_seen) {
                magic.at(i)++;
            }
            if (p == 3 and win_real) {
                real.at(i)++;
            }
        }
    }
}

int main() {
    std::vector<int> magic(turn), real(turn);
    for (int i = 0; i < iter; i++) {
        simulate(magic, real);
    }
    std::cout << "turn" << '\t' << "magic" << '\t' << "real" << '\t' << "ratio"
              << std::endl;
    for (int i = 0; i < turn; i++) {
        std::cout << i + 1 << '\t' << magic.at(i) << '\t' << real.at(i) << '\t'
                  << double(magic.at(i)) / real.at(i) << std::endl;
    }
    return 0;
}
