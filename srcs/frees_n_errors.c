#include "so_long.h"

int	error_message(const char *message, int exit_code)
{
	if (message)
		ft_printf("Error\n%s\n", message);
	exit(exit_code);
}

void	error_handler(const char *message, t_map *map)
{
	if (map)
		free_map(map);
	if (message)
		ft_printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

void	free_images(t_data *data)
{
	if (data->grass.image)
		mlx_destroy_image(data->ptr, data->grass.image);
	if (data->apple.image)
		mlx_destroy_image(data->ptr, data->apple.image);
	if (data->tree.image)
		mlx_destroy_image(data->ptr, data->tree.image);
	if (data->person.image)
		mlx_destroy_image(data->ptr, data->person.image);
	if (data->house.image)
		mlx_destroy_image(data->ptr, data->house.image);
}

int	destroy_win(t_data *data)
{
	free_images(data);
	free_map(&data->map);
	mlx_destroy_window(data->ptr, data->win);
	mlx_destroy_display(data->ptr);
	free(data->ptr);
	data->ptr = NULL;
	exit(0);
	return (0);
}