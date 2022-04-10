#include <vector>

using pattern_t = std::vector<std::vector<int>>;
constexpr int PAIR7 = -1, YAO13 = -2;

bool split_mianzi(std::vector<int> &, int, int, pattern_t &);
bool isagari(std::vector<int> &, pattern_t &, int);
std::vector<int> list_wait(std::vector<int> &, pattern_t &, int);
