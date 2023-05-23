/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:47:29 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/23 11:28:14 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

char	*get_line_env(char *s)
{
	t_data_cmd	*cmd;
	t_env		*tmp;

	tmp = glob.env_p;
	while (tmp)
	{
		if (!ft_strcmp(s, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	**path;
	char	*comd;
	int		i;

	i = 0;
	path = ft_split(get_line_env("PATH"), ':');
	while (path[i] && cmd)
	{
		comd = ft_strjoin(path[i], "/");
		comd = ft_strjoin(comd, cmd);
		if (!access(comd, X_OK))
			return (comd);
		i++;
		free(comd);
	}
	return (cmd);
}

char	**to_double_pointer(t_args *cmd)
{
	int		i;
	int		node_num;
	char	**char_cmds;
	t_args	*tmp;

	i = 0;
	tmp = cmd;
	node_num = ft_lstsizes(cmd);
	char_cmds = malloc((node_num + 1) * sizeof(char *));
	while (tmp)
	{
		char_cmds[i] = tmp->args;
		i++;
		tmp = tmp->next;
	}
	char_cmds[i] = NULL;
	return (char_cmds);
}
