/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:03:04 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/24 05:08:46 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../LIBFT/libft.h"

void	ft_free_node(t_args *cmd)
{
	t_args	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		// free(cmd->args);
		free(cmd);
		cmd = tmp;
	}
}

void	ft_free(t_env *evr)
{
	free((evr)->key);
	if (evr->value)
		free((evr)->value);
	free(evr);
}

void	ft_free_cmd_p(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}
