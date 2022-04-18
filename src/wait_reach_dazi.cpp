#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "fulou.h"
#include "pai_text.h"
#include "waitlib.h"

int main() {
    std::ifstream ifs("../score/hounan4/merged.txt");
    std::string line;
    std::vector<std::unordered_set<int>> hand(4);
    std::map<std::string, int> count_wait;
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
                        list_wait(hand_kind, pattern, mianzi);
                        for (auto &&x : pattern) {
                            std::string wait_text;
                            wait_text += pai_text[kind(4 * x.back() + 1)];
                            wait_text += ' ';
                            if (x[0] == NORMAL) {
                                for (int i = 0; i <= mianzi; i++) {
                                    int tiles_block = 3;
                                    if (i == mianzi) tiles_block = 2;
                                    std::vector<int> pai_block;
                                    bool contain_wait = false;
                                    for (int j = 0; j < tiles_block; j++) {
                                        int pai = x[3 * i + j + 1];
                                        pai_block.push_back(pai);
                                        if (pai == x.back()) {
                                            contain_wait = true;
                                        }
                                    }
                                    if (contain_wait) {
                                        for (int j = 0; j < tiles_block; j++) {
                                            wait_text += pai_text[kind(
                                                4 * pai_block[j] + 1)];
                                        }
                                    }
                                }
                            } else if (x[0] == PAIR7) {
                                wait_text += u8"七対子";
                            } else {
                                wait_text += u8"国士無双";
                                if (std::count(x.begin() + 1, x.end() - 1,
                                               x.back()) == 2) {
                                    wait_text += u8"13面";
                                } else {
                                    wait_text += u8"1面";
                                }
                            }
                            count_wait[wait_text]++;
                        }
                        reach_total++;
                    }
                }
            }
        }
    }

    for (auto &&[wait_text, count] : count_wait) {
        std::cout << wait_text << '\t' << count << '\t'
                  << double(count) / reach_total << std::endl;
    }
    std::cout << '\t' << reach_total << std::endl;

    return 0;
}
