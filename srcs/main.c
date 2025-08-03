#include "so_long.h"

/*
**	main:
**	Check for two arguments (program and map path/file.ber).
**	Check that av[1] is a .ber file.
**	Initialize the map with the required elements.
**	Load the images(init) and draw the map(render)
*/

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_message("Wrong number of arguments", 1);
	if (!check_map_file(av[1]))
		error_message("Invalid map format or content", 1);
	if (!init_map(av[1], &data.map))
	{
		destroy_win(&data);
		error_handler("Map loading failed", &data.map); // cambiato 
	}
	data.ptr = mlx_init();
	if (!data.ptr)
		free_map(&data.map), error_message("Failed to initialize MLX", 1);
	data.win = mlx_new_window(data.ptr, data.map.width * TILE,
			data.map.height * TILE, "So Long");
	if (!data.win)
		free_map(&data.map), error_message("main: Failed to create a new window", 1);
	init_images(&data);
	init_player(&data);
	render_map(&data);
	mlx_hook(data.win, 2, 1L << 0, keypress, &data);
	mlx_hook(data.win, 17, 0, destroy_win, &data);
	mlx_loop(data.ptr);
}