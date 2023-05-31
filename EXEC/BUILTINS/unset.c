/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:06:13 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/31 16:43:04 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

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
			g_glob.ex_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	unset_env(const char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_glob.env_p;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			if (tmp == g_glob.env_p)
				g_glob.env_p = g_glob.env_p->next;
			else
				prev->next = tmp->next;
			ft_free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset(t_args *cmd)
{
	if (cmd == NULL || cmd->next == NULL)
		return ;
	while (cmd->next != NULL)
	{
		if (!(foreign_letter(cmd->next->args)))
			return ;
		unset_env(cmd->next->args);
		cmd = cmd->next;
	}
}
