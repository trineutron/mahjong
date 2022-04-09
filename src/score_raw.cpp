#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

int main() {
    std::ifstream ifs("../score/hounan4/merged.txt");
    std::string line;
    std::map<int, int> count, count_1000;
    double win_total = 0, score_total = 0;
    while (std::getline(ifs, line)) {
        auto pos = line.find(' ');
        auto type = line.substr(0, pos);
        if (type != "<AGARI") continue;
        while (pos != std::string::npos) {
            auto pos_next = line.find(' ', pos + 1);
            std::string element = line.substr(pos + 1, pos_next - pos);
            auto pos_element = element.find('=');
            if (element.substr(0, pos_element) == "ten") {
                int fu = 0, score_raw = 0;
                std::stringstream ss(element.substr(pos_element + 1));
                ss.ignore();
                ss >> fu;
                ss.ignore();
                ss >> score_raw;
                count[score_raw]++;
                count_1000[score_raw / 1000 * 1000]++;
                win_total++;
                score_total += score_raw;
            }
            pos = pos_next;
        }
    }

    std::cout << "RAW" << std::endl;
    for (auto &&[score_raw, times] : count) {
        std::cout << score_raw << '\t' << times << '\t' << times / win_total
                  << std::endl;
    }
    std::cout << std::endl;
    std::cout << "N * 1000" << std::endl;
    for (auto &&[score_raw, times] : count_1000) {
        std::cout << score_raw << '\t' << times << '\t' << times / win_total
                  << std::endl;
    }
    std::cout << std::endl;
    std::cout << "total\t" << int(win_total) << '\t' << score_total / win_total
              << std::endl;

    return 0;
}
