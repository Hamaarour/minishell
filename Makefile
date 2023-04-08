NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address

SRC= Utils/lib_utils/ft_strcmp.c Utils/lib_utils/ft_isalnum.c Utils/lib_utils/ft_calloc.c Utils/lib_utils/ft_strchr.c Utils/lib_utils/ft_split.c Utils/lib_utils/ft_strdup.c \
	Utils/lib_utils/ft_strlen.c Utils/lib_utils/ft_substr.c \
	syntax/check_pipe.c syntax/check_quote.c syntax/check_tokens.c \
	parsing/get_env.c parsing/spliting.c parsing/expanding_var.c \
	minishell.c

OBJ= $(SRC:.c=.o)

all:$(NAME)

.PHONY= all clean fclean re

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lreadline

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all
