
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>

int main ()
{
	char	*line;
	line = readline("\e[0;35m minishell~$  \e[0;35m");
	return (0);
}