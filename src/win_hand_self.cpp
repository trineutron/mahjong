#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "fulou.h"
#include "pai_text.h"

int main() {
    std::ifstream ifs("../score/hounan4/merged.txt");
    std::string line;
    std::vector<int> count(37);
    while (std::getline(ifs, line)) {
        auto pos = line.find(' ');
        std::string type = line.substr(0, pos);
        if (type != "<AGARI") continue;
        while (pos != std::string::npos) {
            auto pos_next = line.find(' ', pos + 1);
            std::string element = line.substr(pos + 1, pos_next - pos - 1);
            auto pos_element = element.find('=');
            std::string type_element = element.substr(0, pos_element);
            if (type_element == "hai") {
                std::stringstream ss(element.substr(pos_element + 1));
                while (true) {
                    int hai;
                    ss.ignore();
                    ss >> hai;
                    if (not ss) break;
                    count.at(kind(hai))++;
                }
            } else if (type_element == "m") {
                std::stringstream ss(element.substr(pos_element + 1));
                while (true) {
                    int code;
                    ss.ignore();
                    ss >> code;
                    if (not ss) break;
                    int tile_get = fulou_get(code);
                    std::vector<int> contain = fulou_contain(code);
                    for (auto &&hai : contain) {
                        if (hai == tile_get) {
                            tile_get = -1;
                        } else {
                            count.at(kind(hai))++;
                        }
                    }
                    assert(tile_get == -1);
                }
            }
            pos = pos_next;
        }
    }

    auto tile_total = 0;
    for (auto &&x : count) {
        tile_total += x;
    }

    for (int i = 0; i < 37; i++) {
        std::cout << pai_text[i] << '\t' << count[i] << '\t'
                  << double(count[i]) / tile_total << std::endl;
    }
    std::cout << '\t' << tile_total << std::endl;

    return 0;
}
