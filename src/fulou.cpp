#include "fulou.h"

// 副露面子のデコード
// 参照: https://tenhou.net/img/tehai.js

// 副露タイプ
int fulou_type(const int code) {
    if (code >> 2 & 1) {
        return CHOW;
    } else if (code >> 3 & 1) {
        return TRIPLE;
    } else if (code >> 4 & 1) {
        return ADD_QUAD;
    } else if (code >> 5 & 1) {
        return NUKI;
    } else {
        return QUAD;
    }
}

// 副露面子・抜きドラに含まれる牌
std::vector<int> fulou_contain(const int code) {
    const int type = fulou_type(code);
    std::vector<int> res;
    if (type == CHOW) {
        int kind = (code >> 10) / 3;
        kind = kind / 7 * 9 + kind % 7;
        int pai_num[3]{(code >> 3) & 3, (code >> 5) & 3, (code >> 7) & 3};
        for (int i = 0; i < 3; i++) {
            res.push_back(4 * (kind + i) + pai_num[i]);
        }
    } else if (type == TRIPLE or type == ADD_QUAD) {
        int unused = (code >> 5) & 3;
        int kind = (code >> 9) / 3;
        if (type == ADD_QUAD) unused = -1;
        for (int i = 0; i < 4; i++) {
            if (i == unused) continue;
            res.push_back(4 * kind + i);
        }
    } else if (type == NUKI) {
        res.push_back(code >> 8);
    } else {
        for (int i = 0; i < 4; i++) {
            res.push_back(4 * (code >> 10) + i);
        }
    }
    return res;
}

// 他家から得た牌
int fulou_get(const int code) {
    const int type = fulou_type(code);
    if (type == NUKI) return -1;
    if (type == CHOW) {
        int kind = (code >> 10) / 3, tile_get = (code >> 10) % 3;
        kind = kind / 7 * 9 + kind % 7;
        int pai_num[3]{(code >> 3) & 3, (code >> 5) & 3, (code >> 7) & 3};
        return 4 * (kind + tile_get) + pai_num[tile_get];
    } else if (type == QUAD) {
        if ((code & 3) == 0) return -1;  // 暗槓
        return code >> 8;
    } else {
        int unused = (code >> 5) & 3;
        int kind = (code >> 9) / 3, tile_get = (code >> 9) % 3;
        if (unused <= tile_get) tile_get++;
        return 4 * kind + tile_get;
    }
}
