NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I/usr/include -Imlx

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a

MLXFLAGS = -L$(MLX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

REMOVE = rm -f

SRC_DIR = srcs

SRC = main.c \
	map_parsing.c \
	utils.c \
	load_image.c \
	frees_n_errors.c \
	game_loop.c \

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(MLX_LIB) $(NAME)
	@echo "Compilation successfully done!!"

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) 
	@echo "Compiling MiniLibX"
	$(MAKE) -C $(MLX_DIR)
	@echo "Compiling so_long...""
	cc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLXFLAGS)
	@echo "$so_long executable created successfully!"

%.o: %.c
	@echo "Compiling $<..."
	cc $(CFLAGS) -I . -I $(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(MLX_LIB):
	@echo "Compiling MiniLibX..."
	$(MAKE) -C $(MLX_DIR)

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean	
	@echo "Cleaning all..."
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re