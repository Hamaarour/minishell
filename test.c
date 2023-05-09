
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}

void	check_max_heredoc(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			count++;
		i++;
	}
	if (count > 16)
	{
		ft_putendl_fd("bash: maximum here-document count exceeded: 16", 2);
		exit(EXIT_FAILURE);
	}
}
int main ()
{
	check_max_heredoc("a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<a <<");
	return (0);
}