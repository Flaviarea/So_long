#include "so_long.h"

/*
**	check_map_file:
**	filename is passed as an argument
**	we compute the length of the name w ft_strlen**	check if it has at least 5 char: 1 char for the name + .ber
**	return 0 (error) if:
**		the name if shorter then 4 char (.ber),
**		the result of comparison of the name + len - 4 with .ber is not zero!
**	return 1 if the file extension is .ber / if the name is valid
*/

int	check_map_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
	{
		//ft_printf("Invalid file extension\n"); error_message 
		return (0);
	}
	return (1);
}

/*
**	init_map or load map
**	open the fd to read the map file, count lines, close the fd
**	reopen the fd, read and fill the grid, close the fd.
**	check if the map has the mandatory elements.
**	check if the map has the mandatory format.
**	check if the map has the mandatory path.
**	return 1 on success, 0 on failure
*/

int	init_map(char *file, t_map *map)
{
	int	fd;
	int	lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_message("Permission denied or no existing map", 0));
	lines = count_lines(fd);
	if (lines == 0)
		return (close(fd), error_message("Map file is empty", 0));
	if (lseek(fd, 0, SEEK_SET) < 0)
		return (close(fd), error_message("Failed to rewind file", 0));
	if (!fill_grid(fd, map, lines))
		return (close(fd), error_message("Failed to fill grid", 0));
	close(fd);
	if (!check_map_elements(map))
		return (free_map(map), error_message("Map elements invalid", 0));
	if (!check_map_format(map, lines))
		return (free_map(map), error_message("Map format is invalid", 0));
	if (!check_map_path(map))
		return (free_map(map), error_message("Map path is invalid", 0));
	return (1);
}

/*
**	fill_grid:
**	allocate memory for a char *array, ones for every lines read,
**	read every line from the file, without newline
**	null-terminate the array
**	set the height and width of the map
**	return 1 on success, 0 on failure
*/

int	fill_grid(int fd, t_map *map, int line_count)
{
	char	*line;
	int		i;

	map->grid = malloc(sizeof(char *) * (line_count + 1));
	if (!map->grid)
		return (error_message("Failed to allocate memory for map grid", 0));
	line = get_next_line(fd);
	i = 0;
	while (line && i < line_count)
	{
		map->grid[i] = ft_strtrim(line, "\r\n");
		free(line);
		if (!map->grid[i])
			return (free_map(map), error_message("Failed to load the map", 0));
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	map->height = line_count;
	map->width = (map->grid[0]) ? ft_strlen(map->grid[0]) : 0;
	return (1);
}

/*
**	check_map_elements:
*/

int	check_map_elements(t_map *map)
{
	scan_map_elements(map);
	map->total_collect = map->c_count;
	if (map->invalid)
		return (error_message("elem: Map contains invalid characters", 0));
	if (map->p_count != 1)
		return (error_message("elem: Map must contain exactly one 'P'", 0));
	if (map->c_count < 1)
		return (error_message("elem: Map must contain at least one 'C'", 0));
	if (map->e_count != 1)
		return (error_message("elem: Map must contain at least one 'E'", 0));
	return (1);
}

int	check_map_path(t_map *map)
{
	t_path	path;

	if (!init_path_struct(&path, map))
	{
		ft_printf("Errore: Player non trovato nella mappa\n"); // erorr_message
		return (0);
	}
	flood_fill_mark(path.cp, path.sx, path.sy, path.cnt);
	free(path.cp);
	return (check_path_result(&path, map));
}

int	check_map_format(t_map *map, int count)
{
	int	i;

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
