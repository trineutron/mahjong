#include "waitlib.h"

bool split_mianzi(std::vector<int> &hand,
                  std::vector<std::vector<int>> &pattern, int remain,
                  int start = 0) {
    // 全面子取り出せた
    if (remain == 0) {
        pattern.emplace_back();
        return true;
    }

    bool res = false;

    // 刻子
    for (int i = 0; i < 34; i++) {
        if (i < start or hand[i] < 3) continue;
        hand[i] -= 3;
        bool res_split = split_mianzi(hand, pattern, remain - 1, i + 1);
        hand[i] += 3;
        if (res_split) {
            for (auto it = pattern.end() - 1; it >= pattern.begin(); it--) {
                if (int(it->size()) >= 3 * remain) break;
                it->emplace_back(i);
                it->emplace_back(i);
                it->emplace_back(i);
            }
            res = true;
        }
    }

    // 順子
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            const int idx = 9 * i + j;
            if (idx + 34 < start) continue;
            if (hand[idx] and hand[idx + 1] and hand[idx + 2]) {
                hand[idx]--;
                hand[idx + 1]--;
                hand[idx + 2]--;
                bool res_split =
                    split_mianzi(hand, pattern, remain - 1, idx + 34);
                hand[idx]++;
                hand[idx + 1]++;
                hand[idx + 2]++;
                if (res_split) {
                    for (auto it = pattern.end() - 1; it >= pattern.begin();
                         it--) {
                        if (int(it->size()) >= 3 * remain) break;
                        it->emplace_back(idx);
                        it->emplace_back(idx + 1);
                        it->emplace_back(idx + 2);
                    }
                    res = true;
                }
            }
        }
    }
    return res;
}

bool isagari(std::vector<int> &hand, std::vector<std::vector<int>> &pattern,
             int mianzi) {
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
    if (is_13orphans) {
        pattern.emplace_back();
        pattern.back().emplace_back(YAO13);
        for (auto &&x : yao) {
            for (int i = 0; i < hand[x]; i++) {
                pattern.back().emplace_back(x);
            }
        }
        return true;
    }

    // 七対子
    bool is_7pairs = true;
    for (int i = 0; i < 34; i++) {
        if (hand[i] != 0 and hand[i] != 2) {
            is_7pairs = false;
            break;
        }
    }
    if (is_7pairs) {
        pattern.emplace_back();
        pattern.back().emplace_back(PAIR7);
        for (int i = 0; i < 34; i++) {
            if (hand[i] == 2) {
                pattern.back().emplace_back(i);
                pattern.back().emplace_back(i);
            }
        }
    }

    // 面子手
    bool is_win_mianzi = false;
    for (int i = 0; i < 34; i++) {
        if (hand[i] < 2) continue;
        hand[i] -= 2;
        if (split_mianzi(hand, pattern, mianzi)) {
            for (auto it = pattern.end() - 1; it >= pattern.begin(); it--) {
                if (int(it->size()) >= 3 * mianzi + 2) break;
                it->emplace_back(i);
                it->emplace_back(i);
            }
            is_win_mianzi = true;
        }
        hand[i] += 2;
    }

    return is_7pairs or is_win_mianzi;
}

std::vector<int> list_wait(std::vector<int> &hand,
                           std::vector<std::vector<int>> &pattern, int mianzi) {
    std::vector<int> res;
    for (int i = 0; i < 34; i++) {
        hand[i]++;
        if (isagari(hand, pattern, mianzi)) res.push_back(i);
        hand[i]--;
    }
    return res;
}
