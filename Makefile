NAME = minishell

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I/usr/include/readline -I./libft

LIBFT = ./libft/libft.a



SRC = builtins/cd.c builtins/echo.c builtins/env.c \
			builtins/exit.c builtins/export.c builtins/pwd.c \
			builtins/unset.c \
			executor/build_in_cmd.c executor/external_cmd.c \
			kill/free_exit.c \
			pipex/pipex.c \
			pipex/pipex_utils.c \
			utils/minishell_helpers.c utils/minishell_set_env.c  utils/minishell_utils.c \
			minishell.c



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lreadline

$(LIBFT):
	make -C ./libft

m: fclean all
	rm -f $(OBJ)
	make -C ./libft clean
	rm -f ./build_in_cmd/*.o
	rm -f libft/libft.a

clean:
	rm -f $(OBJ)
	make -C ./libft clean
	rm -f ./build_in_cmd/*.o

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

valgrind: all clean
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --gen-suppressions=all  --track-fds=all ./minishell

.PHONY: all clean fclean re
