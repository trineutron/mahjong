#include <iostream>
#include <vector>

constexpr int kind = 34, tile = 4 * kind, turn = 18, iter = 1000000;

const std::vector<int> value{1, 2, 3, 4, 5, 4, 3, 2, 1,
                             1, 2, 3, 4, 5, 4, 3, 2, 1,
                             1, 2, 3, 4, 5, 4, 3, 2, 1,
                             0, 0, 0, 0, 0, 0, 0};

uint32_t xrand()
{
    static uint64_t x = 1;
    x ^= x << 9;
    x ^= x >> 7;
    return (x * 0x123456789abcdef) >> 32;
}

int count_chows(std::vector<int> hand)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            while (hand.at(9 * i + j) and hand.at(9 * i + j + 1) and hand.at(9 * i + j + 2))
            {
                count++;
                hand.at(9 * i + j)--;
                hand.at(9 * i + j + 1)--;
                hand.at(9 * i + j + 2)--;
            }
        }
    }
    return count;
}

void simulate(std::vector<int> &magic, std::vector<int> &real)
{
    std::vector<int> seen(kind), hand(kind);
    std::vector<bool> draw(tile);
    bool win_seen = false, win_real = false;
    for (int i = 0; i < 5; i++)
    {
        int k = xrand() % tile;
        while (draw.at(k))
        {
            k = xrand() % tile;
        }
        draw.at(k) = true;
        seen.at(k / 4)++;
        hand.at(k / 4)++;
    }
    for (int i = 0; i < turn; i++)
    {
        int k = xrand() % tile;
        while (draw.at(k))
        {
            k = xrand() % tile;
        }
        draw.at(k) = true;
        seen.at(k / 4)++;
        hand.at(k / 4)++;
        if (not win_seen and count_chows(seen) >= 2)
        {
            win_seen = true;
        }
        if (not win_real and count_chows(hand) >= 2)
        {
            win_real = true;
        }
        if (win_real or hand.at(k / 4) >= 2 or value.at(k / 4) == 0)
        {
            hand.at(k / 4)--;
        }
        else
        {
            int chows_before = count_chows(hand);
            int wait_no_loss = 0;
            for (int l = 0; l < kind; l++)
            {
                int count = 0;
                for (int m = 0; m < 4; m++)
                {
                    if (not draw.at(4 * l + m))
                    {
                        count++;
                    }
                }
                if (count == 0)
                {
                    continue;
                }
                hand.at(l)++;
                if (count_chows(hand) > chows_before)
                {
                    wait_no_loss += count;
                }
                hand.at(l)--;
            }
            auto v = value;
            for (int j = 0; j < kind; j++)
            {
                if (hand.at(j) == 0)
                {
                    continue;
                }
                int wait = 0;
                hand.at(j)--;
                for (int l = 0; l < kind; l++)
                {
                    int count = 0;
                    for (int m = 0; m < 4; m++)
                    {
                        if (not draw.at(4 * l + m))
                        {
                            count++;
                        }
                    }
                    if (count == 0)
                    {
                        continue;
                    }
                    hand.at(l)++;
                    if (count_chows(hand) > chows_before)
                    {
                        wait += count;
                    }
                    hand.at(l)--;
                }
                hand.at(j)++;
                v.at(j) += 100 * (wait_no_loss - wait);
            }

            int x = -1;
            for (int j = 0; j < kind; j++)
            {
                if (hand.at(j) == 0)
                {
                    continue;
                }
                if (hand.at(j) >= 2 or v.at(j) == 0)
                {
                    x = j;
                    break;
                }
                if (x < 0 or v.at(j) < v.at(x))
                {
                    x = j;
                }
            }
            hand.at(x)--;
        }
        if (win_seen)
        {
            magic.at(i)++;
        }
        if (win_real)
        {
            real.at(i)++;
        }
    }
}

int main()
{
    std::vector<int> magic(turn), real(turn);
    for (int i = 0; i < iter; i++)
    {
        simulate(magic, real);
    }
    std::cout << "turn" << '\t' << "magic" << '\t' << "real" << '\t' << "ratio" << std::endl;
    for (int i = 0; i < turn; i++)
    {
        std::cout << i + 1 << '\t' << magic.at(i) << '\t' << real.at(i) << '\t' << double(magic.at(i)) / real.at(i) << std::endl;
    }
    return 0;
}