#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "pai_text.h"

int main() {
    std::ifstream ifs("../score/hounan4/merged.txt");
    std::string line;
    std::map<std::pair<int, int>, int> count;
    int win_total = 0;
    while (std::getline(ifs, line)) {
        auto pos = line.find(' ');
        if (line.substr(0, pos) != "<AGARI") continue;
        while (pos != std::string::npos) {
            auto pos_next = line.find(' ', pos + 1);
            std::string element = line.substr(pos + 1, pos_next - pos - 1);
            auto pos_element = element.find('=');
            if (pos_element == std::string::npos) break;
            std::string type = element.substr(0, pos_element);
            if (type == "yaku" or type == "yakuman") {
                std::stringstream ss(element.substr(pos_element + 1));
                while (ss) {
                    int yaku_type = 0, yaku_han = 0;
                    ss.ignore();
                    ss >> yaku_type;
                    if (type == "yaku") {
                        ss.ignore();
                        ss >> yaku_han;
                    } else {
                        yaku_han = 13;
                    }
                    if (not ss) break;
                    count[{yaku_type, yaku_han}]++;
                }
                win_total++;
            }
            pos = pos_next;
        }
    }

    for (auto &&[yaku, times] : count) {
        auto [yaku_type, yaku_han] = yaku;
        std::cout << yaku_text[yaku_type] << yaku_han << '\t' << times << '\t'
                  << double(times) / win_total << std::endl;
    }
    std::cout << "total\t" << win_total << std::endl;

    return 0;
}
