#include "so_long.h"

int fill_grid(int fd, t_map *map, int line_count);
int	check_map_elements(t_map *map);
int check_map_path(t_map *map);

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
    lines = count_lines(fd);
    close(fd);
    if (lines == 0)
        return error_message("Map file is empty", 0);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return error_message("Cannot reopen file", 0);
    if (!fill_grid(fd, map, lines))
        return (0); // oppure return (free(map->grid), 0);
    close(fd);
    if (!check_map_elements(map))
        return (free_map(map), error_message("Map validation failed", 0)); // return free(map)
    if (!check_map_format(map, lines))
        return (free_map(map), error_message("Map format is invalid", 0)); // return free(map))
    if (!check_map_path(map))
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
    while ((line = get_next_line(fd)) && i < line_count)
    {
        map->grid[i] = ft_strtrim(line, "\n"); // trim newline characters
        free(line);
        if (!map->grid[i])
            return (free_map(map), error_message("Failed to load the map", 0)); // ma ritornare free_map o zero con error_message è uguale?
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

int	check_map_path(t_map *map)
{
	t_path	path;

	if (!init_path_struct(&path, map))
	{
		ft_printf("Errore: Player non trovato nella mappa\n");
		return (0);
	}
	flood_fill_mark(path.cp, path.sx, path.sy, path.cnt);
	free(path.cp);
	return (check_path_result(&path, map));
}



int check_map_format(t_map *map, int count)
{
    int i;

    i = -1;
    if (count < 3 || map->width < 3)
        error_handler("Map is too small", map);
    while (++i < count)
        if ((int)ft_strlen(map->grid[i]) != map->width)
            error_handler("Map is not rectangular", map);
    i = -1;
    while (++i < map->width)
		if (map->grid[0][i] != '1' || map->grid[count - 1][i] != '1')
			error_handler("Map borders are not valid", map);
	i = -1;
	while (++i < count)
		if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
			error_handler("Map borders are not valid", map);
	return (1);
}

