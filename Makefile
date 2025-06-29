NAME = minishell

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I/usr/include/readline -I./libft

LIBFT = ./libft/libft.a

SRC = minishell.c \
			build_in_cmd.c \
			external_cmd.c \
			minishell_utils.c \
			free_exit.c\
			pipex.c \
			$(wildcard ./build_in_cmd_utils/*.c)

OBJ = $(SRC:.c=.o)

m: fclean all
	rm -f $(OBJ)
	make -C ./libft clean
	rm -f ./build_in_cmd/*.o

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lreadline

$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OBJ)
	make -C ./libft clean
	rm -f ./build_in_cmd/*.o

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
