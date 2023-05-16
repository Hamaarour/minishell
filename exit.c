/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:46:56 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/12 14:46:56 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void ft_exit(t_args *cmd)
{
    int 	args_nb;
	t_args	*tmp;

	args_nb = ft_lstsizes(cmd);
	tmp = cmd->next;
    if (args_nb == 1)
    {
        write(1, "exit\n", sizeof("exit"));
        exit(glob.ex_status);
    }
    else if (args_nb == 2)
        arg_one(tmp->args);
    else
    {
        if (!ft_atoi(tmp->args))
            invalid_arg();
		printf("exit\n");
        write(1, "too many arguments\n", 19);
    }
}