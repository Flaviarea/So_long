

int main(int ac, char **av)
{
    t_data data;

    if (ac != 2)
        return error_message("Invalid argument. Please add a valid map path");
    if (!check_map_file(av[1]))
        return error_message("Invalid map format or content");
    if(!init_map(av[i], &data.map))
        return 1;
    data.ptr = mlx_init();
    if (!data.ptr)
        return (free_map(&data.map), error_message("Failed to initialize MLX")); // free the map, where?
    // qui marina fa il controllo su load map e ha uan funzione specifica
    data.win = mlx_new_window(data.ptr, data.width * TILE, data.height * TILE, "So Long"); // data.height *tile?
    if (!data.win)
        return (cleanup(&data), error_message("Failed to create a new window")); // free the map, where? oppure return (free(data.mlx), 1)
    load_images(&data);
    mlx_key_hook(data.ptr, handle_input, &data);
    mlk_hook(data.ptr, 17, exit_success, &data);
    mlx_loop(data.mlx);
    cleanup(&data);
    return 0;
}