#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE 32

# include <mlx.h> // include minilibX header
# include <stdlib.h> // include standard library header
# include <X11/X.h> // include X11 header for X11 events
# include <X11/keysym.h> // include X11 keysym header for key events
# include "../libft/libft.h"
# include "../libft/ft_printf/inc/ft_printf.h"

// map_parsing
int init_map(char *file, t_map *map); // load map + fill the grid 
int fill_grid(int fd, t_map *map, int line_count);
int	check_map_elements(t_map *map); // if the map has P, E, C
int check_map_path(t_map *map); // fload fill, player 
static char	**copy_map(char **grid, int height)

// map_parsing_utils
static void flood_fill_mark(char **g, int x, int y, int *cnt)


// utils
void scan_map_elements(t_map *map);
void count_map_element(t_map *map, char ch);
int count_lines(int fd);
int check_map_file(char *filename); // if the file is a .ber
void init_map_counters(t_map *map);


check_map_format // if the map if rectangular and has walls

typedef struct s_map
{
    char **grid;
    int height;
    int width;
    int p_count;
    int c_count;
    int e_count;
    int invalid;
}   t_map;


typedef struct s_data
{
    void    *ptr;
    void    *win;
    t_image ............
}