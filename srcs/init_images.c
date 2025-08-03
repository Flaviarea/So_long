#include "so_long.h"

/*
**	init_images:
**	load all XPM image files using MLX
**	store image pointers in data structure
**	images include: person, donut, grass, tree, exit
**	width and height parameters are required by MLX but not used
*/
void	init_images(t_data *data)
{
	int	w;
	int	h;

	data->person.image = mlx_xpm_file_to_image(data->ptr,
			"assets/person.xpm", &w, &h);
	data->donut.image = mlx_xpm_file_to_image(data->ptr,
			"assets/donut.xpm", &w, &h);
	data->grass.image = mlx_xpm_file_to_image(data->ptr,
			"assets/grass.xpm", &w, &h);
	data->tree.image = mlx_xpm_file_to_image(data->ptr,
			"assets/tree.xpm", &w, &h);
	data->exit.image = mlx_xpm_file_to_image(data->ptr,
			"assets/exit.xpm", &w, &h);
}

/*
**	render_map:
**	iterate through all positions in the map grid
**	render each tile at its corresponding screen position
**	uses nested loops to cover entire map area
**	calls render_tile for each individual position
*/
void	render_map(t_data *data)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->map.height)
	{
		col = 0;
		while (col < data->map.width)
		{
			render_tile(data, row, col);
			col++;
		}
		row++;
	}
}

/*
**	render_tile:
**	render a single tile at specified grid position
**	calculate screen coordinates from grid position
**	always draw grass background first
**	draw appropriate sprite based on tile character
**	handles: walls(1), exit(E), player(P), collectibles(C)
*/
void	render_tile(t_data *data, int row, int col)
{
	int		x;
	int		y;
	char	tile;

	x = col * TILE;
	y = row * TILE;
	tile = data->map.grid[row][col];
	mlx_put_image_to_window(data->ptr, data->win, data->grass.image, x, y);
	if (tile == '1')
		mlx_put_image_to_window(data->ptr, data->win, data->tree.image, x, y);
	else if (tile == 'E')
		mlx_put_image_to_window(data->ptr, data->win, data->exit.image, x, y);
	else if (tile == 'P')
		mlx_put_image_to_window(data->ptr, data->win,
			data->person.image, x, y);
	else if (tile == 'C')
		mlx_put_image_to_window(data->ptr, data->win,
			data->donut.image, x, y);
}