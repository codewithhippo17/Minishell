# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
READLINE_FLAGS = -lreadline

# Source directories
LEXER_DIR = ./lexer
CHECKER_DIR = ./checker
HEREDOC_DIR = ./heredoc
EXPAND_DIR = ./expander
AST_DIR = ./ast
BULTINS_DIR = ./builtins
KILL_DIR = ./kill
EXEC_DIR = ./executor
PIPE_DIR = ./pipex
UTILS_DIR = ./utils

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

AST_SRCS =		$(AST_DIR)/red.c \
				$(AST_DIR)/join.c \
				$(AST_DIR)/tokens.c \
				$(AST_DIR)/syntax_tree.c

BULTINS_SRC =	$(BULTINS_DIR)/cd.c \
				$(BULTINS_DIR)/echo.c \
				$(BULTINS_DIR)/env.c \
				$(BULTINS_DIR)/exit.c \
				$(BULTINS_DIR)/export.c \
				$(BULTINS_DIR)/pwd.c \
				$(BULTINS_DIR)/unset.c

PIPE_SRC =		$(PIPE_DIR)/pipex.c \
				$(PIPE_DIR)/pipex_utils.c

EXEC_SRC =		$(EXEC_DIR)/build_in_cmd.c \
				$(EXEC_DIR)/external_cmd.c \
				$(EXEC_DIR)/redirection.c \
				$(EXEC_DIR)/token_to_arr.c \
				$(EXEC_DIR)/executor.c

KILL_SRC =		$(KILL_DIR)/free_exit.c

UTILS_SRC =		$(UTILS_DIR)/minishell_helpers.c \
				$(UTILS_DIR)/minishell_set_env.c \
				$(UTILS_DIR)/minishell_utils.c \
				$(UTILS_DIR)/export_utils.c

TEST = 			./test/test.c

MAIN_SRCS = minishell.c

# All source files
SRCS =		$(LEXER_SRCS) $(CHECKER_SRCS) $(HEREDOC_SRCS) $(MINI) $(EXPAND_SRC) $(AST_SRCS) \
				$(BULTINS_SRC) $(PIPE_SRC) $(EXEC_SRC) $(KILL_SRC) $(UTILS_SRC) $(TEST) \
				$(MAIN_SRCS)

PSRCS =		$(LEXER_SRCS) $(CHECKER_SRCS) $(HEREDOC_SRCS) $(MINI) $(EXPAND_SRC) $(AST_SRCS) \
			$(UTILS_SRC) \
			$(MAIN_SRCS)


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

valgrind: all clean
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --gen-suppressions=all  --track-fds=all ./minishell

.PHONY: all clean fclean re lexer checker heredoc
