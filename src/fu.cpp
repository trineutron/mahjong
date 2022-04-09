#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

int main() {
    std::ifstream ifs("../score/hounan4/merged.txt");
    std::string line;
    std::map<int, int> count;
    int win_total = 0;
    while (std::getline(ifs, line)) {
        auto pos = line.find(' ');
        auto type = line.substr(0, pos);
        if (type != "<AGARI") continue;
        while (pos != std::string::npos) {
            auto pos_next = line.find(' ', pos + 1);
            std::string element = line.substr(pos + 1, pos_next - pos);
            auto pos_element = element.find('=');
            if (element.substr(0, pos_element) == "ten") {
                int fu = 0;
                std::stringstream ss(element.substr(pos_element + 1));
                ss.ignore();
                ss >> fu;
                count[fu]++;
                win_total++;
            }
            pos = pos_next;
        }
    }

    for (auto &&[fu, times] : count) {
        std::cout << fu << '\t' << times << '\t' << double(times) / win_total
                  << std::endl;
    }
    std::cout << "total\t" << win_total << std::endl;

    return 0;
}
