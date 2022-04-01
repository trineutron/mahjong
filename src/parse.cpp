#include <iostream>

int main() {
    std::string s;
    while (true) {
        int c = getchar();
        if (c == EOF) break;
        s.push_back(c);
        if (c == '>') {
            std::cout << s << '\n';
            s.clear();
        }
    }
    return 0;
}
