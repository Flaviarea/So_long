#include "so_long.h"

int fill_grid(int fd, t_map *map, int line_count);
int	check_map_elements(t_map *map);

/*
    init_map or load map
    open the fd to read the map file, count lines, close the fd
    reopen the fd, read and fill the grid, close the fd. 
    check if the map has the mandatory elements.
    check if the map has the mandatory format.
    check if the map has the mandatory path.
    return 1 on success, 0 on failure
*/

int init_map(char *file, t_map *map)
{
    int fd;
    int lines;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return error_message("Failed to open map file", -1);
    lines = count_lines(fd)
    close(fd);
    if (lines == 0)
        return error_message("Map file is empty", 0);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return error_message("Cannot reopen file", 0);
    if (!fill_grid(fd, map, lines))
        return (0); // oppure return (free(map->grid), 0);
    close(fd);
    if (!check_map_elements(map, lines))
        return (free_map(map), error_message("Map validation failed", 0)); // return free(map)
    if (!check_map_format(map))
        return (free_map(map), error_message("Map format is invalid", 0)); // return free(map))
    If (!check_map_path(map))
        return (free_map(map), error_message("Map path is invalid", 0));
    return 1; // success
}

/*
    fill_grid:
    allocate memory for a char *array, ones for every lines read,
    read every line from the file, without newline
    null-terminate the array
    set the height and width of the map 
    return 1 on success, 0 on failure
*/

int fill_grid(int fd, t_map *map, int line_count)
{
    char *line;
    int i;

    map->grid = malloc(sizeof(char *) * (line_count + 1));
    if (!map->grid)
        return (error_message("Failed to allocate memory for map grid", 0));
    line = get_next_line(fd);
    i = 0;
    while ((line) && i < line_count)
    {
        map->grid[i] = ft_strtrim(line, "\n"); // trim newline characters
        free(line);
        if (!map->grid[i])
            return (free_map(map), error_message("Failed to load the map", 0))// ma ritornare free_map o zero con error_message è uguale?
        //line = NULL; // free the line after copying
        i++;
        //line = get_next_line(fd); // read the next line
    }
    map->grid[i] = NULL;
    map->height = line_count;
    if (map->grid[0]) // uguale a scrivere map->width = (map->grid[0]) ? ft_strlen(map->grid[0]) : 0;
        map->width = ft_strlen(map->grid[0]);
    else
        map->width = 0; // null-terminate the grid
    return 1; // success
}

/* 
    check_map_elements:

*/

int	check_map_elements(t_map *map)
{
	scan_map_elements(map);
	if (map->invalid)
		return (error_message("Map contains invalid characters", 0));
	if (map->p_count != 1)
		return (error_message("Map must contain exactly one 'P'", 0));
	if (map->c_count < 1)
		return (error_message("Map must contain at least one 'C'", 0));
	if (map->e_count < 1)
		return (error_message("Map must contain at least one 'E'", 0));
	return (1);
}

int check_map_path(t_map *map)
{
    char  **cp;
    int    cnt[2];
    int    i, j, sx, sy;

    cp = copy_map_grid(map);
    if (!cp)
        return 0;
    cnt[0] = 0;
    cnt[1] = 0;
    sx = -1;
    for (i = 0; i < map->height; i++)
        for (j = 0; j < map->width; j++)
            if (map->grid[i][j] == 'P')
            {
                sx = j;
                sy = i;
            }
    flood_fill_mark(cp, sx, sy, cnt);
    free_map_grid(cp, map->height);
    if (cnt[0] != map->c_count)
        return error_message("Not all collectibles reachable", 0);
    if (cnt[1] < 1)
        return error_message("Exit not reachable", 0);
    return 1;
}

static char	**copy_map(char **grid, int height)
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