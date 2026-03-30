NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror
CFLAGS = -I/usr/local/opt/readline/include
LIBS = -lreadline

SRC = \
built-in/builtin.c \
built-in/env_utils.c \
built-in/ft_cd.c \
built-in/ft_echo.c \
built-in/ft_env.c \
built-in/ft_exit.c \
built-in/ft_export.c \
built-in/ft_pwd.c \
built-in/ft_unset.c \
built-in/env_init.c \
built-in/export_utils/exp_add.c\
built-in/export_utils/exp_env.c\
built-in/export_utils/exp_parse.c\
built-in/export_utils/exp_print.c\
built-in/export_utils/exp_utils.c\
built-in/export_utils/exp_vars.c\
builtin_utils/cd_utils.c \
builtin_utils/env_init_utils.c \
builtin_utils/env_helper.c \
builtin_utils/mem_utils.c \
main_utils/utils1.c \
main_utils/utils2.c \
execution/exec.c \
execution/command_utils.c \
execution/exec_simple.c \
execution/pipeline.c \
execution/pipeline_utils.c \
execution/redirections.c \
execution/redir_utils.c \
execution/paths.c \
execution/childs.c \
execution/exec_handling.c \
expand/expand.c \
expand/expand_var.c \
expand/expand_utils.c \
expand/expand_dollar.c \
heredoc/handle_heredoc.c \
heredoc/heredoc_utils.c \
libft/ft_atoi.c \
libft/ft_isalpha.c \
libft/ft_isalnum.c \
libft/ft_isdigit.c \
libft/ft_itoa.c \
libft/ft_memcpy.c \
libft/ft_split.c \
libft/ft_strchr.c \
libft/ft_strrchr.c\
libft/ft_strcmp.c \
libft/ft_strdup.c \
libft/ft_strjoin.c \
libft/ft_strjoin_free.c \
libft/ft_strlen.c \
libft/ft_strlcpy.c \
libft/ft_strncmp.c \
libft/ft_strnstr.c \
libft/ft_substr.c \
libft/ft_memset.c \
libft/ft_isspace.c \
libft/ft_strlcat.c \
parse/check_syntax.c \
parse/error.c \
parse/parse_token/free_utils.c \
parse/parse_token/handle_redirection.c \
parse/parse_token/parse_tokens.c \
parse/parse_token/parse_utils.c \
parse/parse_token/utils2.c \
parse/tokenize/token_utils.c \
parse/tokenize/tokenize.c \
parse/tokenize/tokenize_word.c \
parse/tokenize/utils.c \
signals/signals.c \
main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c mini.h
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
