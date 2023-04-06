/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:26:25 by hamaarou          #+#    #+#             */
/*   Updated: 2023/04/05 03:19:08 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*elt;

	elt = (t_env *)malloc(sizeof(*elt));
	if (elt == NULL)
		return (NULL);
	elt->value = value;
	elt->key = key;
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
}

void	get_env(t_env **env, char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		ft_lstadd_back(env, ft_lstnew(tmp[0], tmp[1]));
		i++;
	}
	free(tmp);

}


