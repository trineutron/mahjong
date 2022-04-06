#include <iostream>
#include <random>
#include <vector>

#include "xrand.h"

constexpr int kind = 34, tile = 4 * kind, player = 4, turn = 18, iter = 1000000;

xrand rng;
std::uniform_int_distribution<> dist(0, tile - 1);

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
            if (seen.at(k / 4) == 3) {
                win_seen = true;
            }
            if (p != 3) {
                seen.at(k / 4)--;
            }
            if (hand.at(k / 4) == 3) {
                win_real = true;
            } else if (p == 3 and hand.at(k / 4) == 2) {
                for (int j = 0; j < kind; j++) {
                    if (hand.at(j) == 1) {
                        hand.at(j)--;
                        break;
                    }
                }
            } else {
                hand.at(k / 4)--;
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
