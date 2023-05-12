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

void	invalid_arg()
{
	write(2, "numeric argument required\n", 26);
	glob.ex_status = 255;
	exit(glob.ex_status);
}

void	arg_one(char *arg)
{
	int			a;

	if (!arg)
		return ;
	a = ft_atoi(arg);
	if (a)
	{
		glob.ex_status = a;
		write(2, "exit\n", sizeof("exit"));
		exit(glob.ex_status % 256);
	}
	else
		invalid_arg();
}

void    ft_exit(char **cmd)
{
	int	args_nb;

	args_nb = args_len(cmd);
	if (args_nb == 1)
	{
		write(1, "exit\n", sizeof("exit"));
		exit(glob.ex_status);
	}
	else if (args_nb == 2)
		arg_one(cmd[1]);
	else
	{
		if (!ft_atoi(cmd[1]))
			invalid_arg();
		write(1, "too many arguments\n", 19);
	}
}