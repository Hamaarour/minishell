#include "../libft/libft.h"
#include "minishell.h"
#include "builtins.h"

int	args_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void    ft_exit(char **cmd)
{
	int	args_nb;

	args_nb = args_len(cmd);
	if (args_nb == 1)
	{
		printf("exit\n");
		exit(glob.ex_status);
	}
	else if (args_nb == 2)
	{
		
	}
}