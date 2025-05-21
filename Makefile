NAME = minishell

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I/usr/include/readline -I./libft

LIBFT = ./libft/libft.a

#SRC = minishell.c mini_build-in_cmd.c minishel_utils.c free_exit.c minishell_expost.c $(wildcard ./build_in_cmd/*.c)

SRC = minishell.c \
			build_in_cmd.c \
			external_cmd.c \
			minishell_utils.c \
			free_exit.c\
			$(wildcard ./build_in_cmd_utils/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lreadline

$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OBJ)
	rm -f ./libft/*.o
	rm -f ./build_in_cmd/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
