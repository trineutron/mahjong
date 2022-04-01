#include <fstream>
#include <iomanip>
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
    constexpr int len = 12;
    std::ifstream ifs("../score/hounan3/merged.txt");
    if (not ifs) {
        std::cerr << "ERROR" << std::endl;
        std::exit(1);
    }
    char prev[len] = "";
    int idx = 0, count_kyoku[16] = {}, count_ba[16] = {}, count_reach[16] = {};
    while (ifs) {
        ifs.get(prev[idx]);
        idx++;
        if (idx == len) {
            idx = 0;
        }

        bool good = true;
        int idx_next = idx;
        for (int i = 0; i < len; i++) {
            if (prev[idx_next] != "<INIT seed=\""[i]) {
                good = false;
                break;
            }
            idx_next++;
            if (idx_next >= len) idx_next -= len;
        }
        if (not good) {
            continue;
        }

        int kyoku = -1, ba = -1, reach = -1;
        ifs >> kyoku;
        ifs.ignore();
        ifs >> ba;
        ifs.ignore();
        ifs >> reach;
        ifs.ignore();

        count_kyoku[kyoku]++;
        count_ba[ba]++;
        count_reach[reach]++;
    }

    std::cout << "num" << '\t' << "kyoku" << '\t' << "ba" << '\t' << "reach"
              << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << i << '\t' << count_kyoku[i] << '\t' << count_ba[i] << '\t'
                  << count_reach[i] << std::endl;
    }

    int total_kyoku = 0, sum_ba = 0, sum_reach = 0;
    for (int i = 0; i < 16; i++) {
        total_kyoku += count_kyoku[i];
        sum_ba += i * count_ba[i];
        sum_reach += i * count_reach[i];
    }
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "avg" << '\t' << total_kyoku << '\t'
              << (double)sum_ba / total_kyoku << '\t'
              << (double)sum_reach / total_kyoku << std::endl;

    return 0;
}
