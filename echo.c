/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:25:00 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/03 17:23:53 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(int ac, char **arg)
{
	int	i = 2;

	if (ac == 2)
	{
		printf("\n");
		return ;
	}
	if (!ft_strcmp(arg[2], "-n"))
	{
		i = 3;
		while(arg[i])
		{
			if (!arg[i + 1])
			{
				printf("%s", arg[i]);
				return ;
			}
			printf("%s ", arg[i++]);
		}
	}
	else
	{
		while(arg[i])
		{
			if (!arg[i + 1])
			{
				printf("%s\n", arg[i]);
				return ;
			}
			printf("%s ", arg[i++]);
		}
	}
}

int	main(int ac, char **av)
{
	if (ac > 1)
		echo(ac, av);
	return (0);
}