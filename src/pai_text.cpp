int kind(int pai_num) {
    int res = pai_num / 4;
    for (int color = 0; color < 3; color++) {
        if (pai_num > 36 * color + 16) {
            res++;
        }
    }
    return res;
}
