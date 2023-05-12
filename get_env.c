/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:11:22 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/12 00:15:03 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/libft.h"

t_env	*ft_lstnews(char *key, char *value)
{
	t_env	*elt;

	elt = (t_env *)malloc(sizeof(*elt));
	if (elt == NULL)
		return (NULL);
	elt->value = ft_strdup(value);
	elt->key = ft_strdup(key);
	elt->next = NULL;
	return (elt);
}

void	ft_lstadd_backs(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!head || !*head)
	{
		(*head) = new;
		return ;
	}
	if (!new)
		return ;
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

void	get_env(t_env **env, char **envp)
{
	int		i;
	char	**tmp;
	t_env	*new_node;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (tmp && tmp[0] && tmp[1])
		{
			new_node = ft_lstnews(tmp[0], tmp[1]);
			ft_lstadd_backs(env, new_node);
			free(tmp[0]);
			free(tmp[1]);
			free(tmp);
		}
		i++;
	}
}