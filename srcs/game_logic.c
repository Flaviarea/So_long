#include "so_long.h"

int	keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		destroy_win(data);
	else if (keycode == XK_Up || keycode == 65362)
		try_move(data, 0, -1);
	else if (keycode == XK_Down || keycode == 65364)
		try_move(data, 0, 1);
	else if (keycode == XK_Left || keycode == 65361)
		try_move(data, -1, 0);
	else if (keycode == XK_Right || keycode == 65363)
		try_move(data, 1, 0);
	return (0);
}

void	try_move(t_data *data, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = data->map.player.x + dx;
	new_y = data->map.player.y + dy;
	if (!is_valid_move(data, new_x, new_y))
	{
		ft_printf(" → blocked by wall/border\n");
		return ;
	}
	handle_tile_effects(data, new_x, new_y);
	if (data->map.grid[new_y][new_x] == 'E'
		&& data->map.player.collected == data->map.total_collect)
	{
		ft_printf("DEBUG: VICTORY CONDITION MET!\n");
		update_player_position(data, new_x, new_y);
		render_map(data);
		ft_printf("\rYou won in %d moves!\n", data->map.player.moves);
		destroy_win(data);
		return ;
	}
	update_player_position(data, new_x, new_y);
}

void	init_player(t_data *data)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->map.height)
	{
		col = 0;
		while (col < data->map.width)
		{
			if (data->map.grid[row][col] == 'P')
			{
				data->map.player.x = col;
				data->map.player.y = row;
				data->map.player.collected = 0;
				data->map.player.moves = 0;
				data->map.player.orig_pos = '0';
				// ft_printf("DEBUG: Player initialized at (%d,%d), 
                //     total_collect=%d\n", col, row, data->map.total_collect);
				return;
			}
			col++;
		}
		row++;
	}
}

int	is_valid_move(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
		return (0);
	if (data->map.grid[y][x] == '1')
		return (0);
	return (1);
}

void	handle_tile_effects(t_data *data, int x, int y)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == 'C')
	{
		data->map.player.collected++;
		data->map.grid[y][x] = '0';
	}
}

void	update_player_position(t_data *data, int x, int y)
{
	int	old_x;
	int	old_y;

	old_x = data->map.player.x;
	old_y = data->map.player.y;
	data->map.grid[old_y][old_x] = data->map.player.orig_pos;
	render_tile(data, old_y, old_x);
	data->map.player.orig_pos = data->map.grid[y][x];
	data->map.player.x = x;
	data->map.player.y = y;
	data->map.grid[y][x] = 'P';
	data->map.player.moves++;
	ft_printf("\rMoves: %d", data->map.player.moves);
	render_tile(data, y, x);
}

