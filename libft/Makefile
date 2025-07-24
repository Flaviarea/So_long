NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I ft_printf/include -I get_next_line/include

SRC = \
	srcs/ft_atoi.c \
	srcs/ft_bzero.c \
	srcs/ft_calloc.c \
	srcs/ft_isalnum.c \
	srcs/ft_isalpha.c \
	srcs/ft_isascii.c \
	srcs/ft_isdigit.c \
	srcs/ft_isprint.c \
	srcs/ft_itoa.c \
	srcs/ft_memchr.c \
	srcs/ft_memcmp.c \
	srcs/ft_memcpy.c \
	srcs/ft_memmove.c \
	srcs/ft_memset.c \
	srcs/ft_putchar_fd.c \
	srcs/ft_putendl_fd.c \
	srcs/ft_putnbr_fd.c \
	srcs/ft_putstr_fd.c \
	srcs/ft_split.c \
	srcs/ft_strchr.c \
	srcs/ft_strdup.c \
	srcs/ft_striteri.c \
	srcs/ft_strjoin.c \
	srcs/ft_strlcat.c \
	srcs/ft_strlcpy.c \
	srcs/ft_strlen.c \
	srcs/ft_strmapi.c \
	srcs/ft_strncmp.c \
	srcs/ft_strnstr.c \
	srcs/ft_strrchr.c \
	srcs/ft_strtrim.c \
	srcs/ft_substr.c \
	srcs/ft_tolower.c \
	srcs/ft_toupper.c \
	get_next_line/srcs/get_next_line.c \
	get_next_line/srcs/get_next_line_utils.c \
	ft_printf/srcs/ft_printf.c \
	ft_printf/srcs/ft_put.c \
	ft_printf/srcs/ft_puthexlow.c \
	ft_printf/srcs/ft_putnbr.c \
	ft_printf/srcs/ft_putstr.c \
	ft_printf/srcs/ft_puthexupper.c \
	ft_printf/srcs/ft_putpointer.c \
	ft_printf/srcs/ft_putuns.c \
	ft_printf/srcs/ft_putchar.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
