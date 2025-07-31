#include "so_long.h"

int	init_path_struct(t_path *path, t_map *map)
{
	int	y;
	int	x;

	path->cp = copy_map_grid(map->grid, map->height);
	if (!path->cp)
		return (0);
	path->cnt[0] = 0;
	path->cnt[1] = 0;
	path->sx = -1;
	path->sy = -1;
	path->i = 0;
	path->j = 0;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'P')
			{
				path->sx = x;
				path->sy = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0); // player non trovato
}

char	**copy_map_grid(char **grid, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
			{
				free(copy[i]);
				copy[i] = NULL;
			}
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void flood_fill_mark(char **g, int x, int y, int *cnt)
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

int	check_path_result(t_path *path, t_map *map)
{
	if (path->cnt[0] != map->c_count)
		return (error_message("Not all collectibles reachable", 0));
	if (path->cnt[1] < 1)
		return (error_message("Exit not reachable", 0));
	return (1);
}

void	find_player_position(t_path *path, t_map *map)
{
	while (path->i < map->height)
	{
		path->j = 0;
		while (path->j < map->width)
		{
			if (map->grid[path->i][path->j] == 'P')
			{
				path->sx = path->j;
				path->sy = path->i;
			}
			path->j++;
		}
		path->i++;
	}
}

int count_lines(int fd)
{
    char *line;
    int count;

    count = 0;
	line = get_next_line(fd);
    while((line != NULL))
    {
        line = get_next_line(fd);
        free(line); // free the line after processing
        count++;
    }
    return count;
}