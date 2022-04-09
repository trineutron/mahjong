#include <fstream>
#include <iostream>

#include "pai_text.h"

int main() {
    std::ifstream ifs("../score/hounan3/merged.txt");
    std::string line;
    int draw[37] = {}, discard[37] = {};
    while (std::getline(ifs, line)) {
        bool good = false, is_draw = false, is_discard = false;
        for (int i = 0; i < 4; i++) {
            if (line[1] == i + 'D') {
                good = true;
                is_discard = true;
                break;
            }
            if (line[1] == i + 'T') {
                good = true;
                is_draw = true;
                break;
            }
        }
        if (not good) {
            continue;
        }
        if (not isdigit(line[2])) {
            continue;
        }

        int pai_num = 0, idx = 2;
        while (true) {
            int digit = line[idx];
            if (not isdigit(digit)) {
                break;
            }
            pai_num *= 10;
            pai_num += digit - '0';
            idx++;
        }
        if (is_draw) {
            draw[kind(pai_num)]++;
        } else if (is_discard) {
            discard[kind(pai_num)]++;
        }
    }

    std::cout << "text" << '\t' << "draw" << '\t' << "discard" << std::endl;
    for (int i = 0; i < 37; i++) {
        std::cout << pai_text[i] << '\t' << draw[i] << '\t' << discard[i]
                  << std::endl;
    }

    return 0;
}
