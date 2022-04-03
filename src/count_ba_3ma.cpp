#include <fstream>
#include <iomanip>
#include <iostream>

int main() {
    std::ifstream ifs("../score/hounan3/merged.txt");
    std::string line;
    std::stringstream ss;
    int count_kyoku[16] = {}, count_ba[16] = {}, count_reach[16] = {};
    while (std::getline(ifs, line)) {
        if (line.substr(0, 12) != "<INIT seed=\"") {
            continue;
        }

        int kyoku = -1, ba = -1, reach = -1;
        ss.str("");
        ss << line;
        ss.ignore(12);
        ss >> kyoku;
        ss.ignore();
        ss >> ba;
        ss.ignore();
        ss >> reach;

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
