# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 01:19:26 by zjaddad           #+#    #+#              #
#    Updated: 2023/05/22 01:19:26 by zjaddad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=cc #-fsanitize=address -g3
LIBREADLINE		= -L /goinfre/$(USER)/homebrew/opt/readline/lib -lreadline
INCREADLINE		= -I /goinfre/$(USER)/homebrew/opt/readline/include
CFLAGS= -Wall -Wextra -Werror 

SRC= main.c FREE/free.c LIBFT/ft_strncmp.c LIBFT/ft_isalpha.c LIBFT/ft_strtrim.c LIBFT/ft_strcmp.c LIBFT/ft_split.c  LIBFT/ft_isprint.c EXEC/BUILTINS/unset.c\
	LIBFT/ft_substr.c LIBFT/ft_strlen.c LIBFT/ft_strdup.c LIBFT/ft_putstr_fd.c EXEC/BUILTINS/echo.c\
	EXEC/BUILTINS/pwd.c LIBFT/ft_lstdelone.c EXEC/BUILTINS/env.c EXEC/BUILTINS/exit.c LIBFT/ft_bzero.c LIBFT/ft_calloc.c\
	LIBFT/ft_isspace.c LIBFT/ft_atoi.c EXEC/BUILTINS/CD.c EXEC/BUILTINS/export.c LIBFT/ft_strchr.c LIBFT/ft_lstadd_back.c LIBFT/ft_lstnew.c\
	LIBFT/ft_lstlast.c EXEC/BUILTINS/buitins_exec.c LIBFT/ft_calloc_p.c LIBFT/ft_isalnum.c LIBFT/ft_itoa.c\
	LIBFT/ft_putendl_fd.c LIBFT/ft_split_p.c LIBFT/ft_strjoin.c LIBFT/ft_strstr.c LIBFT/ft_substr_p.c EXEC/BUILTINS/export_utlis.c\
	parsing/GNL/get_next_line_utils.c parsing/GNL/get_next_line.c \
	parsing/token/tokens.c  parsing/parse/here_doc_utils.c\
	parsing/lexer/lexer.c parsing/lexer/error_func.c parsing/lexer/dollar_lexer.c parsing/lexer/init_lexer.c  parsing/lexer/rm_extra_spaces.c parsing/lexer/lexer_utils.c\
	parsing/lexer/dollar_lexer_utils.c \
	parsing/parse/parse_utils.c \
	parsing/lexer/get_envairment_var.c parsing/lexer/get_char.c parsing/lexer/get_env.c  parsing/lexer/free_lexer.c\
	parsing/parse/init_parse.c parsing/parse/parse.c parsing/parse/parse_free.c parsing/parse/err_msg.c parsing/parse/check_types.c\
	parsing/parse/here_doc_utils_2.c \
	parsing/syntax/check_quote.c parsing/syntax/syntaxe_check.c parsing/parse/opennig_files.c parsing/parse/max_heredoc.c\
	parsing/parse/linked_list_args.c parsing/parse/linked_list_cmd.c parsing/syntax/syntax_utils.c\
	EXEC/EXECUTION/execution.c EXEC/EXECUTION/exec_get_path.c free_parser.c parsing/parse/prints_errs.c\
	EXEC/EXECUTION/exec_get_pipe.c EXEC/ERRORS/error.c EXEC/SIGNALS/signals.c EXEC/BUILTINS/CD_utils.c

OBJ= $(SRC:.c=.o)

all:$(NAME)

.PHONY= all clean fclean re

$(NAME):$(OBJ)
	@echo "compiling..."
	@$(CC) $(CFLAGS) $(INCREADLINE) $(OBJ) $(LIBREADLINE) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all