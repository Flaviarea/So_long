#include "so_long.h"

/*
height e width Devono essere assegnati dal contenuto di map.
*/

int main(int ac, char **av)
{
    t_data data;

    if (ac != 2)
        error_message("Invalid argument. Please add a valid map path", 1);
    if (!check_map_file(av[1]))
        error_message("Invalid map format or content", 1);
    if(!init_map(av[1], &data.map))
        error_message("Failed to initialize map", 1);
    data.ptr = mlx_init();
    if (!data.ptr)
    {
        free_map(&data.map);
        error_message("Failed to initialize MLX", 1);
    }
    // qui marina fa il controllo su load map e ha uan funzione specifica
    data.win = mlx_new_window(data.ptr, data.map.width * TILE, data.map.height * TILE, "So Long"); // data.height *tile?
    if (!data.win)
    {
        free_map(&data.map);
        error_message("Failed to create a new window", 1);
    }
    init_images(&data);
    render_map(&data);
    mlx_key_hook(data.win, keypress, &data);
    mlx_hook(data.win, 17, 0, destroy_win, &data);
    mlx_loop(data.ptr);
    return 0;
}