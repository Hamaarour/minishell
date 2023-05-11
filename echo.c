/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:25:00 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/11 02:58:00 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "../libft/libft.h"

int	check_newline(char *s)
{
	int	i;

	i = 2;
	if (s[0] != '-' || (s[0] == '-' && s[1] != 'n'))
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] && s[i] != 'n')
		return (0);
	return (1);
}

void	echo(char **input, int outf)
{
	int	i;
	int	flag;

	glob.ex_status = 0;
	flag = 1;
	i = 1;
	while (input[i] && check_newline(input[i]))
	{
		flag = 0;
		while (input[i] && check_newline(input[i]))
			i++;
	}
	while (input[i])
	{
		ft_putstr_fd(input[i++], outf);
		if (input[i])
			ft_putstr_fd(" ", outf);
	}
	if (flag)
		ft_putstr_fd("\n", outf);
}
