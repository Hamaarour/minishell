NAME=minishell
CC=cc #-fsanitize=address
#CFLAGS=-Wall -Wextra -Werror 

SRC=test.c unset.c epur_str.c ft_strcmp.c get_env.c LIBFT/ft_split.c \
LIBFT/ft_substr.c LIBFT/ft_strlen.c LIBFT/ft_strdup.c LIBFT/ft_putstr_fd.c echo.c\
pwd.c LIBFT/ft_lstdelone.c env.c exit.c LIBFT/ft_bzero.c LIBFT/ft_calloc.c\
LIBFT/ft_atoi.c CD.c

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