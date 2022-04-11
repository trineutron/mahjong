#include <vector>

using pattern_t = std::vector<std::vector<int>>;
constexpr int NORMAL = -1, PAIR7 = -2, YAO13 = -3;

bool split_mianzi(std::vector<int> &, pattern_t &, int, int);
bool isagari(std::vector<int> &, pattern_t &, int);
std::vector<int> list_wait(std::vector<int> &, pattern_t &, int);
