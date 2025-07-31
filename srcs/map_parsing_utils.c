#include "so_long.h"

void scan_map_elements(t_map *map)
{
    int y;
    int x;

    y = 0;
    init_map_counters(map);
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            count_map_element(map, map->grid[y][x]);
            x++;
        }
        y++;
    }
}

void init_map_counters(t_map *map)
{
    map->p_count = 0;
    map->c_count = 0;
    map->e_count = 0;
    map->invalid = 0;
}

void count_map_element(t_map *map, char ch)
{
    if (ch == 'P')
        map->p_count++;
    else if (ch == 'C')
        map->c_count++;
    else if (ch == 'E')
        map->e_count++;
    else if (ch != '0' && ch != '1')
        map->invalid = 1;
}