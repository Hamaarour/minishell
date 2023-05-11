/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:06:13 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/11 01:32:00 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "../libft/libft.h"


int	foreign_letter(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] >= '!' && cmd[i] <= '/')
			|| (cmd[i] >= ':' && cmd[i] <= '@')
			|| (cmd[i] >= '[' && cmd[i] <= '^')
			|| (cmd[i] == '`')
			|| (cmd[i] >= '}' && cmd[i] <= '~')
			|| (cmd[0] >= '0' && cmd[0] <= '9'))
		{
			printf("%s: not a valid\n", cmd);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free(t_env *evr)
{
	free((evr)->key);
	free((evr)->value);
	free(evr);
}

void	unset(char **cmd, t_env *evr)
{
	int	i;
	t_env	*tmp;
	t_env	*prev;

	tmp = evr;
	i = 0;
	// PS: check if program get env_value(mean those are after '=' in env)
	//it must display nothing. Become functional just if get it env_key
	if (cmd[0] && !cmd[1])
		return ;
	while (cmd[++i])
	{
		if (!(foreign_letter(cmd[i])))
			return ;
		while (tmp)
		{
			if (!ft_strcmp(cmd[i], tmp->key))
			{
				prev->next = tmp->next;
				ft_free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;	
		}
		tmp = evr;
	}
}

