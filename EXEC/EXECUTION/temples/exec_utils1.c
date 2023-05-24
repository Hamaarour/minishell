/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:13:46 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/24 01:14:01 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*get_env(char **env)
{
	int		i;
	char	**all;
	t_env	*temp_var;
	t_list	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i] != NULL)
	{
		temp_var = s_malloc(sizeof(t_env));
		all = ft_split(env[i], '=');
		temp_var->key = all[0];
		temp_var->value = all[1];
		ft_lstadd_back(&env_list, ft_lstnew(temp_var));
		free(all);
		i++;
	}
	return (env_list);
}

char	**env_to_tab(t_list *list)
{
	int		size;
	char	**t;
	char	*tmp;
	t_env	*curr;
	int		i;

	i = 0;
	size = ft_lstsize(list);
	t = (char **)s_malloc(sizeof(char *) * (size + 1));
	t[size] = NULL;
	while (list)
	{
		curr = (t_env *)list->content;
		tmp = ft_strjoin(curr->key, "=");
		t[i] = ft_strjoin(tmp, curr->value);
		i++;
		list = list->next;
		free(tmp);
	}
	return (t);
}

void	*s_malloc(int size)
{
	void	*s;

	s = malloc(size);
	g_data.to_free[g_data.index] = s;
	g_data.index++;
	return (s);
}

size_t	get_env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

char	*add_path(char *cmd)
{
	char	**path;
	char	*command;
	int		i;

	i = 0;
	path = ft_split(get_new_env("PATH"), ':');
	while (cmd && path[i])
	{
		command = ft_strjoin(path[i], "/");
		command = ft_strjoin(command, cmd);
		if (!access(command, R_OK))
			return (command);
		i++;
		free(command);
	}
	return (cmd);
}