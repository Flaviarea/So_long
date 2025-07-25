#include "so_long.h"

void	render_map(t_data *data);
void	render_tile(t_data *data, int row, int col);

void	init_images(t_data *data)
{
	int	w;
	int	h;

	data->person.image = mlx_xpm_file_to_image(data->ptr, PATH_CAT, &w, &h);
	data->apple.image = mlx_xpm_file_to_image(data->ptr, PATH_W, &w, &h);
	data->grass.image = mlx_xpm_file_to_image(data->ptr, PATH_G, &w, &h);
	data->house.image = mlx_xpm_file_to_image(data->ptr, PATH_H, &w, &h);
	data->tree.image = mlx_xpm_file_to_image(data->ptr, PATH_H, &w, &h);
}

void	render_tile(t_data *data, int row, int col)
{
	int	x;
	int	y;
	char	tile;

	x = col * TILE;
	y = row * TILE;
	tile = data->map.grid[row][col];
	mlx_put_image_to_window(data->ptr, data->win, data->grass.image, x, y);
	if (tile == '1')
		mlx_put_image_to_window(data->ptr, data->win, data->house.image, x, y);
	else if (tile == 'E')
		mlx_put_image_to_window(data->ptr, data->win, data->tree.image, x, y);
	else if (tile == 'P')
		mlx_put_image_to_window(data->ptr, data->win, data->person.image, x, y);
	else if (tile == 'C')
		mlx_put_image_to_window(data->ptr, data->win, data->apple.image, x, y);
}

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

