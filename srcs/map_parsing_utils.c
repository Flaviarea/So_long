#include "so_long.h"

/*
**	scan_map_elements:
**	iterate through all positions in the map grid
**	count each type of element (P, C, E)
**	check for invalid characters
**	initialize counters before scanning
*/
void	scan_map_elements(t_map *map)
{
	int	y;
	int	x;

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
**	init_map_counters:
**	initialize all element counters to zero
**	reset invalid flag to zero
**	prepare map structure for element counting
*/
void	init_map_counters(t_map *map)
{
	map->p_count = 0;
	map->c_count = 0;
	map->e_count = 0;
	map->invalid = 0;
}

/*
**	count_map_element:
**	analyze a single character from the map
**	increment appropriate counter for valid elements (P, C, E)
**	check for null character (should not happen in valid map)
**	verify that character is valid (P, C, E, 0, 1)
**	call error handler for invalid characters
*/
void	count_map_element(t_map *map, char ch)
{
	if (ch == '\0')
		error_handler("Error", map);
	if (ch == 'P')
		map->p_count++;
	else if (ch == 'C')
		map->c_count++;
	else if (ch == 'E')
		map->e_count++;
	else if (ch != '0' && ch != '1')
		error_handler("Map with invalid character", map);
}

