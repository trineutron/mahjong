#include <cassert>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("../score/hounan3/merged.txt");
    std::string line;
    int agari = 0;
    int tsumo = 0, ron = 0, ron2 = 0, ryuukyoku = 0, nm = 0;
    int yao9 = 0, kaze4 = 0, reach4 = 0, kan4 = 0, ron3 = 0;
    bool in_game = false;
    while (std::getline(ifs, line)) {
        auto pos = line.find(' ');
        auto type = line.substr(0, pos);
        if (type == "<INIT") {
            if (in_game) {
                if (agari == 2) {
                    ron2++;
                } else if (agari == 1) {
                    ron++;
                }
            }
            in_game = true;
            agari = 0;
        } else if (type == "</mjloggm>") {
            if (agari == 2) {
                ron2++;
            } else if (agari == 1) {
                ron++;
            }
            in_game = false;
            agari = 0;
        } else if (type == "<AGARI") {
            int who = -1, fromwho = -1;
            while (pos != std::string::npos) {
                std::string param;
                auto prev = pos + 1;
                pos = line.find(' ', prev);
                if (pos == std::string::npos) {
                    param = line.substr(prev);
                } else {
                    param = line.substr(prev, pos - prev);
                }
                auto pos_eq = param.find('=');
                auto key = param.substr(0, pos_eq);
                if (key == "who") {
                    who = param.at(pos_eq + 2) - '0';
                } else if (key == "fromWho") {
                    fromwho = param.at(pos_eq + 2) - '0';
                }
            }
            assert(who != -1);
            assert(fromwho != -1);
            if (who == fromwho) {
                tsumo++;
            } else {
                agari++;
            }
        } else if (type == "<RYUUKYOKU") {
            ryuukyoku++;
            while (pos != std::string::npos) {
                std::string param;
                auto prev = pos + 1;
                pos = line.find(' ', prev);
                if (pos == std::string::npos) {
                    param = line.substr(prev);
                } else {
                    param = line.substr(prev, pos - prev);
                }
                auto pos_eq = param.find('=');
                auto key = param.substr(0, pos_eq);
                if (key == "type") {
                    ryuukyoku--;
                    auto pos_end = param.find('"', pos_eq + 2);
                    auto type = param.substr(pos_eq + 2, pos_end - pos_eq - 2);
                    if (type == "nm") {
                        nm++;
                    } else if (type == "yao9") {
                        yao9++;
                    } else if (type == "kaze4") {
                        kaze4++;
                    } else if (type == "reach4") {
                        reach4++;
                    } else if (type == "kan4") {
                        kan4++;
                    } else if (type == "ron3") {
                        ron3++;
                    } else {
                        assert(false);
                    }
                }
            }
        }
    }
    std::cout << u8"ツモ\t" << tsumo << std::endl;
    std::cout << u8"ロン\t" << ron << std::endl;
    std::cout << u8"ダブロン\t" << ron2 << std::endl;
    std::cout << u8"流局\t" << ryuukyoku << std::endl;
    std::cout << u8"流し満貫\t" << nm << std::endl;
    std::cout << u8"九種九牌\t" << yao9 << std::endl;
    std::cout << u8"四風子連打\t" << kaze4 << std::endl;
    std::cout << u8"四家立直\t" << reach4 << std::endl;
    std::cout << u8"四槓散了\t" << kan4 << std::endl;
    std::cout << u8"三家和\t" << ron3 << std::endl;
    return 0;
}
