#include <iostream>
#include <fstream>

int main()
{
    constexpr int len = 5;
    std::ifstream ifs("/home/hokuto/mahjong/score/hounan4/merged.txt", std::ios::in);
    if (not ifs)
    {
        std::cerr << "ERROR" << std::endl;
    }
    char prev[len] = "";
    int idx = 0, ans = 0;
    while (not ifs.eof())
    {
        ifs >> prev[idx];
        idx++;
        if (idx == len)
        {
            idx = 0;
        }
        char current[len];
        for (int i = 0; i < len; i++)
        {
            current[i] = prev[(idx + i) % len];
        }

        bool good = true;
        for (int i = 0; i < len; i++)
        {
            if (current[i] != "<T0/>"[i])
            {
                good = false;
                break;
            }
        }

        if (good)
        {
            ans++;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
