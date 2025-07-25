#include "so_long.h"

static void	handle_tile_effects(t_data *data, int x, int y);
static void	update_player_position(t_data *data, int x, int y);
void	try_move(t_data *data, int dx, int dy);
int	keypress(int keycode, t_data *data);

static int	is_valid_move(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
		return (0);
	if (data->map.grid[y][x] == '1')
		return (0);
	return (1);
}

static void	handle_tile_effects(t_data *data, int x, int y)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == 'C')
	{
		data->map.player.collected++;
		data->map.grid[y][x] = '0';
	}
	else if (tile == 'E' && data->map.player.collected == data->map.total_collect)
	{
		ft_printf("\rYou won in %d moves!\n", ++data->map.player.moves);
		destroy_win(data);
	}
}

static void	update_player_position(t_data *data, int x, int y)
{
	int	old_x = data->map.player.x;
	int	old_y = data->map.player.y;

	data->map.grid[old_y][old_x] = '0';
	draw_tile(data, old_y, old_x);

	data->map.player.x = x;
	data->map.player.y = y;
	data->map.grid[y][x] = 'P';
	data->map.player.moves++;

	ft_printf("\rMoves: %d", data->map.player.moves);
	draw_tile(data, y, x);
}

void	try_move(t_data *data, int dx, int dy)
{
	int	new_x = data->map.player.x + dx;
	int	new_y = data->map.player.y + dy;

	if (!is_valid_move(data, new_x, new_y))
		return ;
	handle_tile_effects(data, new_x, new_y);
	// Exit tile ends the game, so prevent update if exited
	if (data->map.grid[new_y][new_x] == 'E'
		&& data->map.player.collected == data->map.total_collect)
		return ;
	update_player_position(data, new_x, new_y);
	redraw_map(data);
}

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
