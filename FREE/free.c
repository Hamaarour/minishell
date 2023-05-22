/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:03:04 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/22 03:05:02 by zjaddad          ###   ########.fr       */
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
