# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 16:07:00 by hamaarou          #+#    #+#              #
#    Updated: 2023/05/10 18:32:25 by hamaarou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror #-fsanitize=address

SRC=parsing/Utils/lib_utils/ft_strstr.c parsing/Utils/lib_utils/ft_strcmp.c parsing/Utils/lib_utils/ft_isalnum.c parsing/Utils/lib_utils/ft_putendl_fd.c\
	parsing/Utils/lib_utils/ft_calloc.c parsing/Utils/lib_utils/ft_strchr.c parsing/Utils/lib_utils/ft_split.c parsing/Utils/lib_utils/ft_strdup.c \
	parsing/Utils/lib_utils/ft_strlen.c parsing/Utils/lib_utils/ft_substr.c parsing/Utils/lib_utils/ft_strjoin.c parsing/Utils/lib_utils/ft_itoa.c\
	parsing/syntax/check_quote.c parsing/syntax/syntaxe_check.c\
	parsing/token/tokens.c \
	parsing/lexer/lexer.c parsing/lexer/error_func.c parsing/lexer/dollar_lexer.c parsing/lexer/rm_extra_spaces.c \
	parsing/lexer/get_envairment_var.c parsing/lexer/get_char.c parsing/lexer/get_env.c  parsing/lexer/free_lexer.c\
	parsing/parse/init_parse.c parsing/parse/parse.c \
	minishell.c

OBJ= $(SRC:.c=.o)

all:$(NAME)

.PHONY= all clean fclean re

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lreadline
	@clear

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all


#.___  ___.  __  .__   __.  __       _______. __    __   _______  __       __      
#|   \/   | |  | |  \ |  | |  |     /       ||  |  |  | |   ____||  |     |  |     
#|  \  /  | |  | |   \|  | |  |    |   (----`|  |__|  | |  |__   |  |     |  |     
#|  |\/|  | |  | |  . `  | |  |     \   \    |   __   | |   __|  |  |     |  |     
#|  |  |  | |  | |  |\   | |  | .----)   |   |  |  |  | |  |____ |  `----.|  `----.
#|__|  |__| |__| |__| \__| |__| |_______/    |__|  |__| |_______||_______||_______|
                                                                                  