/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:06:13 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/22 03:05:19 by zjaddad          ###   ########.fr       */
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
			glob.ex_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void unset(t_args *cmd)
{
    int i;
    t_env *tmp;
    t_env *prev;

    i = 0;
    if (cmd == NULL || cmd->next == NULL)
        return;
    while (cmd->next != NULL)
    {
        if (!(foreign_letter(cmd->next->args)))
            return;
    	tmp = glob.env_p;
        while (tmp)
        {
            if (!ft_strcmp(cmd->next->args, tmp->key))
            {
                if (tmp == glob.env_p)
                    glob.env_p = glob.env_p->next;
                else
                    prev->next = tmp->next;
                ft_free(tmp);
                break ;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        cmd = cmd->next;
    }
}
