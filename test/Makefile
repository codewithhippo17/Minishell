# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
READLINE_FLAGS = -lreadline

# Source directories
LEXER_DIR = ../lexer
CHECKER_DIR = ../checker
HEREDOC_DIR = ../heredoc
EXPAND_DIR = ../expander
AST_DIR = ../ast

# Source files
LEXER_SRCS =	$(LEXER_DIR)/lexer.c \
	        	$(LEXER_DIR)/lexer_utils.c \
	        	$(LEXER_DIR)/lexer_helpers.c

CHECKER_SRCS =	$(CHECKER_DIR)/checker.c \
	        	$(CHECKER_DIR)/checker_helpers.c \
	        	$(CHECKER_DIR)/rules.c

HEREDOC_SRCS =	$(HEREDOC_DIR)/heredoc.c \
	        	$(HEREDOC_DIR)/heredoc_helpers.c \
	        	$(HEREDOC_DIR)/random.c \
	        	$(HEREDOC_DIR)/ft_heredoc.c
EXPAND_SRC =	$(EXPAND_DIR)/expand_helpers.c \
				$(EXPAND_DIR)/ft_expander.c \
				$(EXPAND_DIR)/expand_utils.c \
				$(EXPAND_DIR)/ft_spliter.c \
				$(EXPAND_DIR)/helpers.c \
				$(EXPAND_DIR)/utils.c

AST_SRCS =	$(AST_DIR)/red.c \
			$(AST_DIR)/join.c \
			$(AST_DIR)/tokens.c

MINI = 	../kill/free_exit.c \
		../utils/minishell_helpers.c ../utils/minishell_set_env.c  ../utils/minishell_utils.c ../builtins/unset.c

MAIN_SRCS = main.c

# All source files
SRCS = $(LEXER_SRCS) $(CHECKER_SRCS) $(HEREDOC_SRCS) $(MINI) $(EXPAND_SRC) $(AST_SRCS) $(MAIN_SRCS)

# Object files
OBJS = $(SRCS:.c=.o)

# Header dependencies
INCLUDES = -I ../includes -I $(LIBFT_DIR)

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

# Individual module rules (optional)
lexer: $(LEXER_SRCS:.c=.o)
	$(CC) $(CFLAGS) $(INCLUDES) $(LEXER_SRCS:.c=.o) -o test_lexer

checker: $(CHECKER_SRCS:.c=.o)
	$(CC) $(CFLAGS) $(INCLUDES) $(CHECKER_SRCS:.c=.o) -o test_checker

heredoc: $(HEREDOC_SRCS:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(HEREDOC_SRCS:.c=.o) $(LIBFT) $(READLINE_FLAGS) -o test_heredoc

.PHONY: all clean fclean re lexer checker heredoc
