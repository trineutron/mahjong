#include <iostream>
#include <vector>

constexpr int kind = 34, tile = 4 * kind, turn = 18, iter = 100000000;

uint32_t xrand()
{
    static uint64_t x = 1;
    x ^= x << 9;
    x ^= x >> 7;
    return (x * 0x123456789abcdef) >> 32;
}

bool contain_4triples(const std::vector<int> &hand)
{
    int count_triples = 0, count_pairs = 0;
    for (int i = 0; i < kind; i++)
    {
        if (hand.at(i) >= 3)
        {
            count_triples++;
        }
        if (hand.at(i) >= 2)
        {
            count_pairs++;
        }
    }
    return count_triples >= 4 and count_pairs >= 5;
}

void simulate(std::vector<int> &magic, std::vector<int> &real)
{
    std::vector<int> seen(kind), hand(kind);
    std::vector<bool> draw(tile);
    bool win_seen = false, win_real = false;
    for (int i = 0; i < 13; i++)
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
        if (contain_4triples(seen))
        {
            win_seen = true;
        }
        if (contain_4triples(hand))
        {
            win_real = true;
        }
        int discard = k / 4;
        for (int j = 0; j < kind; j++)
        {
            if (hand.at(j) >= 4)
            {
                discard = j;
                break;
            }
            if (hand.at(j) >= 1 and hand.at(j) < hand.at(discard))
            {
                discard = j;
            }
        }
        hand.at(discard)--;
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
