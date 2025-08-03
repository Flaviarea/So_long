#include "so_long.h"

/*
**	init_path_struct:
**	create a copy of the map grid for pathfinding
**	initialize path values to default state
**	find player position in the map
**	return 1 on success, 0 on failure
*/
int	init_path_struct(t_path *path, t_map *map)
{
	path->cp = copy_map_grid(map->grid, map->height);
	if (!path->cp)
		return (0);
	init_path_values(path);
	return (find_player_in_map(path, map));
}

/*
**	init_path_values:
**	initialize all path structure values to default
**	set counters to zero
**	set player coordinates to invalid (-1)
**	reset iteration variables
*/
void	init_path_values(t_path *path)
{
	path->cnt[0] = 0;
	path->cnt[1] = 0;
	path->sx = -1;
	path->sy = -1;
	path->i = 0;
	path->j = 0;
}

/*
**	find_player_in_map:
**	search through the entire map grid
**	look for player character 'P'
**	store player coordinates when found
**	return 1 if player found, 0 otherwise
*/
int	find_player_in_map(t_path *path, t_map *map)
{
	int	y;
	int	x;

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
	return (0);
}

/*
**	copy_map_grid:
**	allocate memory for a copy of the map grid
**	duplicate each string in the grid
**	handle memory allocation failures properly
**	return pointer to copied grid or NULL on failure
*/
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

/*
**	flood_fill_mark:
**	recursive flood fill algorithm to mark reachable areas
**	count collectibles and exits that can be reached
**	mark visited cells with 'F' to avoid infinite recursion
**	stop at walls ('1') and already visited cells ('F')
*/
void	flood_fill_mark(char **g, int x, int y, int *cnt)
{
	size_t	w;

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

/*
**	check_path_result:
**	verify that all collectibles are reachable
**	verify that at least one exit is reachable
**	return 1 if path is valid, 0 with error message otherwise
*/
int	check_path_result(t_path *path, t_map *map)
{
	if (path->cnt[0] != map->c_count)
		return (error_message("Not all collectibles reachable", 0));
	if (path->cnt[1] < 1)
		return (error_message("Exit not reachable", 0));
	return (1);
}

/*
**	find_player_position:
**	alternative method to find player position
**	uses path structure iteration variables
**	stores player coordinates in path structure
**	scans entire map systematically
*/
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

/*
**	count_lines:
**	count the number of lines in a file
**	check for empty lines and reject them
**	handle both Unix and Windows line endings
**	return number of lines or -1 on error
*/
int	count_lines(int fd)
{
	char	*line;
	int		count;
	char	*trimmed;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, "\r\n");
		if (trimmed && ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			free(line);
			error_handler("Map contains empty line", NULL);
			return (-1);
		}
		if (trimmed)
			free(trimmed);
		free(line);
		count++;
		line = get_next_line(fd);
	}
	return (count);
}