NAME = pipex

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c pipex_utils.c pipex_exit.c $(wildcard libft/*.c)
OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[$<] Building OBJS..."


all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;92mpipex compiled sucsessfully...\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "OBJS removed..."

fclean: clean
	@rm -f $(NAME)
	@echo "PROG removed..."


re:	fclean all

.PHONY: all clean fclean re
