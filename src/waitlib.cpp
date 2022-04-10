#include "waitlib.h"

bool split_mianzi(std::vector<int> &hand, int remain) {
    // 全面子取り出せた
    if (remain == 0) return true;

    // 刻子
    for (int i = 0; i < 34; i++) {
        if (hand[i] < 3) continue;
        hand[i] -= 3;
        bool res = split_mianzi(hand, remain - 1);
        hand[i] += 3;
        if (res) return true;
    }

    // 順子
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            const int idx = 9 * i + j;
            if (hand[idx] and hand[idx + 1] and hand[idx + 2]) {
                hand[idx]--;
                hand[idx + 1]--;
                hand[idx + 2]--;
                bool res = split_mianzi(hand, remain - 1);
                hand[idx]++;
                hand[idx + 1]++;
                hand[idx + 2]++;
                if (res) return true;
            }
        }
    }
    return false;
}

bool isagari(std::vector<int> &hand) {
    // 国士無双
    const std::vector<int> yao{0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33};
    bool is_13orphans = true;
    int count_yao = 0;
    for (auto &&x : yao) {
        if (hand[x] == 0) {
            is_13orphans = false;
            break;
        }
        count_yao += hand[x];
    }
    if (count_yao != 14) is_13orphans = false;
    if (is_13orphans) return true;

    // 七対子
    bool is_7pairs = true;
    for (int i = 0; i < 34; i++) {
        if (hand[i] != 0 and hand[i] != 2) {
            is_7pairs = false;
            break;
        }
    }
    if (is_7pairs) return true;

    // 面子手
    bool is_win_mianzi = false;
    for (int i = 0; i < 34; i++) {
        if (hand[i] < 2) continue;
        hand[i] -= 2;
        if (split_mianzi(hand, 4)) {
            is_win_mianzi = true;
        }
        hand[i] += 2;
        if (is_win_mianzi) return true;
    }

    return false;
}

std::vector<int> list_wait(std::vector<int> &hand) {
    std::vector<int> res;
    for (int i = 0; i < 34; i++) {
        hand[i]++;
        if (isagari(hand)) res.push_back(i);
        hand[i]--;
    }
    return res;
}
