#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "pai_text.h"
#include "waitlib.h"

int main() {
    std::ifstream ifs("../score/hounan4/merged.txt");
    std::string line;
    std::vector<int> wait_count(34), wait_count_real(34);
    int total = 0;
    while (std::getline(ifs, line)) {
        auto pos = line.find(' ');
        std::string type = line.substr(0, pos);
        if (type != "<AGARI") continue;
        std::vector<int> hand(34);
        int count = 0;
        while (pos != std::string::npos) {
            auto pos_next = line.find(' ', pos + 1);
            std::string element = line.substr(pos + 1, pos_next - pos - 1);
            pos = pos_next;
            auto pos_element = element.find('=');
            std::string type_element = element.substr(0, pos_element);
            if (type_element == "hai") {
                std::stringstream ss(element.substr(pos_element + 1));
                while (true) {
                    int pai;
                    ss.ignore();
                    ss >> pai;
                    if (not ss) break;
                    hand[pai / 4]++;
                    count++;
                }
            } else if (type_element == "machi") {
                std::stringstream ss(element.substr(pos_element + 1));
                int pai;
                ss.ignore();
                ss >> pai;
                hand[pai / 4]--;
                count--;
                wait_count_real[pai / 4]++;
            }
        }
        pattern_t pattern;
        auto wait = list_wait(hand, pattern, (count - 1) / 3);
        for (auto &&x : wait) {
            wait_count[x]++;
        }
        total++;
    }

    for (int i = 0; i < 34; i++) {
        std::cout << pai_text[kind(4 * i + 1)] << '\t' << wait_count[i] << '\t'
                  << wait_count_real[i] << std::endl;
    }
    std::cout << "\t\t" << total << std::endl;
    for (int i = 0; i < 34; i++) {
        std::cout << pai_text[kind(4 * i + 1)] << '\t'
                  << double(wait_count[i]) / total << '\t'
                  << double(wait_count_real[i]) / total << std::endl;
    }

    return 0;
}
