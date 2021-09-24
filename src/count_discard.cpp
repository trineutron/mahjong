#include <iostream>
#include <fstream>

int kind(int pai_num)
{
    int res = pai_num / 4;
    for (int color = 0; color < 3; color++)
    {
        if (pai_num > 36 * color + 16)
        {
            res++;
        }
    }
    return res;
}

int main()
{
    constexpr int len = 2;
    std::ifstream ifs("../score/hounan4/merged.txt");
    if (not ifs)
    {
        std::cerr << "ERROR" << std::endl;
        std::exit(1);
    }
    char prev[len] = "";
    int idx = 0, ans[37] = {};
    while (ifs)
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

        if (current[0] != '<')
        {
            continue;
        }
        bool good = false;
        for (int i = 0; i < 4; i++)
        {
            if (current[1] == i + 'D')
            {
                good = true;
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
            ans[kind(pai_num)]++;
        }
    }

    for (int i = 0; i < 37; i++)
    {
        std::cout << i << '\t' << ans[i] << std::endl;
    }

    return 0;
}
