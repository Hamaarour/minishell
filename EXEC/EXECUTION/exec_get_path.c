/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:47:29 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/23 01:28:48 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../LIBFT/libft.h"

char	*get_line_env(char *s)
{
	t_data_cmd	*cmd;
	t_env		*tmp;

	tmp = glob.env_p;
	while (tmp)
	{
		if (!ft_strcmp(s, tmp->key))
			return (tmp->key);
		tmp = tmp->next
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	**path;
	char	*comd;
	int		i;

	i = 0;
	path = ft_split(get_line_env("PATH=", ':'));
}
