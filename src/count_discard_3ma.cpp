#include <fstream>
#include <iostream>

const std::string text[]{"1m",  "2m", "3m", "4m", "r5m", "5m", "6m",  "7m",
                         "8m",  "9m", "1p", "2p", "3p",  "4p", "r5p", "5p",
                         "6p",  "7p", "8p", "9p", "1s",  "2s", "3s",  "4s",
                         "r5s", "5s", "6s", "7s", "8s",  "9s", "東",  "南",
                         "西",  "北", "白", "發", "中"};

int kind(int pai_num) {
    int res = pai_num / 4;
    for (int color = 0; color < 3; color++) {
        if (pai_num > 36 * color + 16) {
            res++;
        }
    }
    return res;
}

int main() {
    constexpr int len = 2;
    std::ifstream ifs("../score/hounan3/merged.txt");
    if (not ifs) {
        std::cerr << "ERROR" << std::endl;
        std::exit(1);
    }
    char prev[len] = "";
    int idx = 0, draw[37] = {}, discard[37] = {};
    while (ifs) {
        ifs.get(prev[idx]);
        idx++;
        if (idx == len) {
            idx = 0;
        }
        char current[len];
        for (int i = 0; i < len; i++) {
            current[i] = prev[(idx + i) & 1];
        }

        if (current[0] != '<') {
            continue;
        }
        bool good = false, is_draw = false, is_discard = false;
        for (int i = 0; i < 4; i++) {
            if (current[1] == i + 'D') {
                good = true;
                is_discard = true;
                break;
            }
            if (current[1] == i + 'T') {
                good = true;
                is_draw = true;
                break;
            }
        }
        if (not good) {
            continue;
        }

        bool fst = true;
        int pai_num = 0;
        char digit;
        while (true) {
            ifs >> digit;
            if (not isdigit(digit)) {
                if (fst) {
                    pai_num = -1;
                }
                break;
            }
            pai_num *= 10;
            pai_num += digit - '0';
            fst = false;
        }
        if (pai_num == -1) {
            continue;
        }
        if (is_draw) {
            draw[kind(pai_num)]++;
        } else if (is_discard) {
            discard[kind(pai_num)]++;
        }
    }

    std::cout << "text" << '\t' << "draw" << '\t' << "discard" << std::endl;
    for (int i = 0; i < 37; i++) {
        std::cout << text[i] << '\t' << draw[i] << '\t' << discard[i]
                  << std::endl;
    }

    return 0;
}
