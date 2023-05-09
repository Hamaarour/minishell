/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:26:25 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/07 22:29:37 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_env	*ft_lstnew(char *key, char *value)
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

void	ft_lstadd_back(t_env **head, t_env *new)
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
			new_node = ft_lstnew(tmp[0], tmp[1]);
			ft_lstadd_back(env, new_node);
			free(tmp[0]);
			free(tmp[1]);
			free(tmp);
		}
		i++;
	}
}
