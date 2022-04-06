#include <iostream>
#include <random>
#include <vector>

#include "xrand.h"

constexpr int kind = 34, tile = 4 * kind, turn = 18, iter = 1000000;

xrand rng;
std::uniform_int_distribution<> dist(0, tile - 1);

bool contain_3pairs(const std::vector<int> &hand) {
    int count_pairs = 0;
    for (int i = 0; i < kind; i++) {
        if (hand.at(i) >= 2) {
            count_pairs++;
        }
    }
    return count_pairs >= 3;
}

void simulate(std::vector<int> &magic, std::vector<int> &real) {
    std::vector<int> seen(kind), hand(kind);
    std::vector<bool> draw(tile);
    bool win_seen = false, win_real = false;
    for (int i = 0; i < 5; i++) {
        int k = dist(rng);
        while (draw.at(k)) {
            k = dist(rng);
        }
        draw.at(k) = true;
        seen.at(k / 4)++;
        hand.at(k / 4)++;
    }
    for (int i = 0; i < turn; i++) {
        int k = dist(rng);
        while (draw.at(k)) {
            k = dist(rng);
        }
        draw.at(k) = true;
        seen.at(k / 4)++;
        hand.at(k / 4)++;
        if (contain_3pairs(seen)) {
            win_seen = true;
        }
        if (contain_3pairs(hand)) {
            win_real = true;
        }
        int discard = k / 4;
        for (int j = 0; j < kind; j++) {
            if (hand.at(j) >= 3) {
                discard = j;
                break;
            }
            if (hand.at(j) == 1 and hand.at(discard) == 2) {
                discard = j;
            }
        }
        hand.at(discard)--;
        if (win_seen) {
            magic.at(i)++;
        }
        if (win_real) {
            real.at(i)++;
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
