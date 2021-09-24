#include <iostream>
#include <fstream>

int main()
{
    constexpr int len = 2;
    std::ifstream ifs("/home/hokuto/mahjong/score/hounan4/merged.txt", std::ios::in);
    if (not ifs)
    {
        std::cerr << "ERROR" << std::endl;
        std::exit(1);
    }
    char prev[len] = "";
    int idx = 0, ans = 0;
    while (ifs.good())
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
            if (current[i] != "<D"[i])
            {
                good = false;
                break;
            }
        }

        if (good)
        {
            bool fst = true;
            int pai_num = 0;
            char digit;
            while (true)
            {
                ifs >> digit;
                if (not isdigit(digit))
                {
                    if (fst)
                    {
                        pai_num = -1;
                    }
                    break;
                }
                pai_num *= 10;
                pai_num += digit - '0';
                fst = false;
            }
            if (pai_num == -1)
            {
                continue;
            }
            if (not ifs.good())
            {
                std::cerr << "ERROR" << std::endl;
                std::exit(1);
            }
            if (pai_num / 4 == 0)
            {
                ans++;
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
