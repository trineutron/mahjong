#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "fulou.h"
#include "waitlib.h"

int main() {
    std::ifstream ifs("../score/hounan4/merged.txt");
    std::string line;
    std::vector<std::unordered_set<int>> hand(4);
    std::vector<int> count_n_wait(35);
    int reach_total = 0, wrong = 0;
    while (std::getline(ifs, line)) {
        const int len = line.size();
        if (len <= 7) {
            int pai_num = std::stoi(line.substr(2));
            if (line[1] >= 'T') {
                if (hand[line[1] - 'T'].size() % 3 != 1) {
                    wrong++;
                }
                assert(hand[line[1] - 'T'].insert(pai_num).second);
            } else {
                assert(hand[line[1] - 'D'].erase(pai_num) == 1);
            }
            continue;
        }
        int player = -1;
        auto pos = line.find(' ');
        std::string type = line.substr(0, pos);
        if (type != "<INIT" and type != "<N" and type != "<REACH") continue;
        while (pos != std::string::npos) {
            auto pos_next = line.find(' ', pos + 1);
            std::string element = line.substr(pos + 1, pos_next - pos - 1);
            pos = pos_next;
            auto pos_element = element.find('=');
            std::string type_element = element.substr(0, pos_element);
            std::stringstream ss(element.substr(pos_element + 1));
            if (type == "<INIT" and type_element.substr(0, 3) == "hai") {
                player = type_element[3] - '0';
                hand[player].clear();
                while (true) {
                    int hai;
                    ss.ignore();
                    ss >> hai;
                    if (not ss) break;
                    hand[player].insert(hai);
                }
            } else if (type == "<N") {
                if (type_element == "who") {
                    ss.ignore();
                    ss >> player;
                }
                if (type_element == "m") {
                    assert(player >= 0);
                    int code;
                    ss.ignore();
                    ss >> code;
                    int get = fulou_get(code);
                    auto contain = fulou_contain(code);
                    for (auto &&hai : contain) {
                        if (hai == get) continue;
                        hand[player].erase(hai);
                    }
                }
            } else if (type == "<REACH") {
                if (type_element == "who") {
                    ss.ignore();
                    ss >> player;
                } else if (type_element == "step") {
                    int step = 0;
                    ss.ignore();
                    ss >> step;
                    if (step == 2) {
                        int mianzi = hand[player].size() / 3;
                        std::vector<int> hand_kind(34);
                        pattern_t pattern;
                        for (auto &&hai : hand[player]) {
                            hand_kind[hai / 4]++;
                        }
                        count_n_wait[list_wait(hand_kind, pattern, mianzi)
                                         .size()]++;
                        reach_total++;
                    }
                }
            }
        }
    }

    for (int i = 0; i <= 34; i++) {
        if (count_n_wait[i] == 0) continue;
        std::cout << i << '\t' << count_n_wait[i] << '\t'
                  << double(count_n_wait[i]) / reach_total << std::endl;
    }
    std::cout << '\t' << reach_total << std::endl;

    return 0;
}
