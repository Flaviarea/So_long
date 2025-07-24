static void flood_fill_mark(char **g, int x, int y, int *cnt)
{
    size_t w;

    if (y < 0 || x < 0)
        return ;
    if (!g[y])
        return ;
    w = ft_strlen(g[y]);
    if (x >= (int)w || g[y][x] == '1' || g[y][x] == 'F')
        return ;
    if (g[y][x] == 'C')
        cnt[0]++;
    else if (g[y][x] == 'E')
        cnt[1]++;
    g[y][x] = 'F';
    flood_fill_mark(g, x + 1, y, cnt);
    flood_fill_mark(g, x - 1, y, cnt);
    flood_fill_mark(g, x, y + 1, cnt);
    flood_fill_mark(g, x, y - 1, cnt);
}

