#include "so_long.h"

void scan_map_elements(t_map *map);
void count_map_element(t_map *map, char ch);
int count_lines(int fd);
int check_map_file(char *filename);

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

/*
    for get_next_line
*/

int count_lines(int fd)
{
    char *line;
    int count;

    count = 0;
    while((line != NULL))
    {
        line = get_next_line(fd)
        free(line); // free the line after processing
        count++;
    }
    return count;
}

/*
    chack_map_file:
    filename is passed as an argument
    we compute the lenght of the name w strlen
    check if it has at least 5 char: 1 char for the name + .ber
    return 0 (error) if:
        the name if shorter then 4 char (.ber),
        the result of comparison of the name + len - 4 with .ber is not zero!
    return 1 if the file extention is .ber
*/

int check_map_file(char *filename)
{
    int len;

    len = ft_strlen(filename);
    if (len < 5)
        return (0);
    if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
        return 0;
	return (1);
}