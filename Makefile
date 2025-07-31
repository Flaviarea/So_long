NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Ilibft/include

INCLUDES = -I/usr/include -Imlx

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

MLXFLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

REMOVE = rm -rf

SRC_DIR = srcs

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/map_parsing.c \
      $(SRC_DIR)/map_parsing_utils.c \
      $(SRC_DIR)/utils.c \
      $(SRC_DIR)/init_images.c \
      $(SRC_DIR)/frees_n_errors.c \
      $(SRC_DIR)/game_logic.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(MLX) $(NAME)
	@echo "Compilation successfully done"

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "Compiling mlx..."
	@make -C $(MLX_DIR)

$(NAME): $(OBJ) 
	@echo "Compiling MiniLibX"
	$(MAKE) -C $(MLX_DIR)
	@echo "Compiling so_long..."
	cc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLXFLAGS)
	@echo "$(NAME) executable created successfully"

%.o: %.c
	@echo "Compiling $<..."
	cc $(CFLAGS) -I . -I $(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@


clean:
	@echo "Cleaning object files..."
	$(REMOVE) $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean	
	@echo "Cleaning all..."
	$(REMOVE) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re