NAME = minishell

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I/usr/include/readline -I./libft

#./libft/ft_strlen.c \
#			./libft/ft_putchar_fd.c \
#			./libft/ft_strncmp.c \


LIBFT = ./libft/libft.a

SRC = ./minishell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lreadline

$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
