#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE 32

#define PATH_CAT "image/person.xpm"
#define PATH_C "image/apple.xpm"
#define PATH_W "image/tree.xpm"
#define PATH_G "image/grass.xpm"
#define PATH_H "image/house.xpm"

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "libft/include/libft.h"

typedef struct s_player
{
    int collected;
    int moves;
    int x;
    int y;
} t_player;

typedef struct s_map
{
    char **grid;
    int height;
    int width;
    int p_count;
    int c_count;
    int e_count;
    int invalid;
    int total_collect;
    t_player player;
} t_map;

typedef struct s_image
{
	void	*image;
	int		width;
	int		height;
}	t_image;

typedef struct s_data
{
    void    *ptr;
    void    *win;
    t_map   map;    
    t_image person;
    t_image house;
    t_image grass;
    t_image apple;
    t_image tree;
} t_data;

typedef struct s_path
{
    char  **cp;
    int    cnt[2];
    int    i;
    int    j;
    int    sx;
    int    sy;
}   t_path;


// map_parsing

int init_map(char *file, t_map *map); // load map + fill the grid 
int fill_grid(int fd, t_map *map, int line_count);
int	check_map_elements(t_map *map); // if the map has P, E, C
int check_map_path(t_map *map); // fload fill, player 
int check_map_format(t_map *map, int count); // if the map if rectangular and has walls

// map_parsing_utils
void scan_map_elements(t_map *map);
void count_map_element(t_map *map, char ch);
int count_lines(int fd);
int check_map_file(char *filename);  // if the file is a .ber
void init_map_counters(t_map *map);

// utils
char	**copy_map_grid(char **grid, int height);
void	redraw_map(t_data *data);
void flood_fill_mark(char **g, int x, int y, int *cnt);
int	check_path_result(t_path *path, t_map *map);
int init_path_struct(t_path *path, t_map *map);
int count_lines(int fd);

// game_logic
void	handle_tile_effects(t_data *data, int x, int y);
void	update_player_position(t_data *data, int x, int y);
void	try_move(t_data *data, int dx, int dy);
int	keypress(int keycode, t_data *data);
int	is_valid_move(t_data *data, int x, int y);

// frees_n_errors
void	error_handler(const char *message, t_map *map);
void	free_map(t_map *map);
void	free_images(t_data *data);
int	destroy_win(t_data *data);
int	error_message(const char *message, int exit_code);

// init_image
void	render_map(t_data *data);
void	render_tile(t_data *data, int row, int col);
void	init_images(t_data *data);


#endif