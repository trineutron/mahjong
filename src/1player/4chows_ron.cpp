#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "xrand.h"

constexpr int kind = 34, tile = 4 * kind, player = 4, turn = 18, iter = 10000;

const std::vector<int> value{1, 2, 3, 4, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 4, 3, 2,
                             1, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0};

xrand rng;
std::uniform_int_distribution<> dist(0, tile - 1);

int count_chows(std::vector<int> hand) {
    auto hand_head = hand;
    int count = 0, count_head = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            const int idx = 9 * i + j;
            const int k = std::min({hand[idx], hand[idx + 1], hand[idx + 2]});
            count += k;
            hand[idx] -= k;
            hand[idx + 1] -= k;
            hand[idx + 2] -= k;
        }
    }
    for (int h = 0; h < kind; h++) {
        if (hand_head[h] < 2) continue;
        int count_head_h = 0;
        hand_head[h] -= 2;
        hand = hand_head;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                const int idx = 9 * i + j;
                const int k =
                    std::min({hand[idx], hand[idx + 1], hand[idx + 2]});
                count_head_h += k;
                hand[idx] -= k;
                hand[idx + 1] -= k;
                hand[idx + 2] -= k;
            }
        }
        hand_head[h] += 2;
        count_head = std::max(count_head, count_head_h);
        if (count_head == count) break;
    }
    if (count > count_head) {
        count--;
    }
    return count;
}

void simulate(std::vector<int> &magic, std::vector<int> &real) {
    std::vector<int> seen(kind), hand(kind), deck(kind, 4);
    std::vector<bool> draw(tile);
    bool win_seen = false, win_real = false;
    for (int i = 0; i < 13; i++) {
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
            deck.at(k / 4)--;
            seen.at(k / 4)++;
            if (not win_seen and count_chows(seen) >= 4) {
                win_seen = true;
            }
            if (p != 3) {
                seen.at(k / 4)--;
            }
            hand.at(k / 4)++;
            if (not win_real and count_chows(hand) >= 4) {
                win_real = true;
            }
            if (p != 3 or win_real) {
                hand.at(k / 4)--;
            } else {
                int chows_before = count_chows(hand);
                auto v = value;
                for (int j = 0; j < kind; j++) {
                    if (hand.at(j) == 0) {
                        continue;
                    }
                    int wait = 0;
                    hand.at(j)--;
                    for (int l = 0; l < kind; l++) {
                        int count = deck.at(l);
                        if (count == 0) {
                            continue;
                        }
                        hand.at(l)++;
                        for (int m = l; m < kind; m++) {
                            int n = count;
                            if (m != l) {
                                n *= deck.at(m);
                            } else {
                                n *= deck.at(m) - 1;
                                n /= 2;
                            }
                            if (n == 0) {
                                continue;
                            }
                            hand.at(m)++;
                            if (count_chows(hand) > chows_before) {
                                wait += n;
                            }
                            hand.at(m)--;
                        }
                        hand.at(l)--;
                    }
                    hand.at(j)++;
                    v.at(j) -= 100 * wait;
                }

                int x = -1;
                for (int j = 0; j < kind; j++) {
                    if (hand.at(j) == 0) {
                        continue;
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
