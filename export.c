/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:46:40 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/16 22:59:35 by zjaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "../libft/libft.h"

void	get_export(t_env *exp, int fd)
{
	t_env	*tmp;

	tmp = exp;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->key, fd);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
}

t_env	*key_value(char *s)
{
	t_env	*new_node;
	char	*eq;

	eq = ft_strchr(s, '=');
	if (eq)
		*eq = '\0';
	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(s);
	if (eq)
		new_node->value = ft_strdup(eq + 1);
	else
		new_node->value = NULL;
	return (new_node);
}

int	update_value(char *key, char *value, t_env *evr)
{
	t_env	*tmp;

	tmp = evr;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (!value)
				return (1);
			else
				tmp->value = value;
			return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_lstadd_back_s(t_env **head, t_env *new)
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

t_env	*ft_lstnew_s(char *key, char *value)
{
	t_env	*elt;

	elt = (t_env *)malloc(sizeof(*elt));
	if (elt == NULL)
		return (NULL);
	if (value != NULL)
		elt->value = ft_strdup(value);
	elt->key = ft_strdup(key);
	elt->next = NULL;
	return (elt);
}

void	ft_export(char **cmd, int outf)
{
	int		len;
	int		i;
	t_env	*exprt;
	t_env	*tmp;

	exprt = glob.env_p;
	len = args_len(cmd);
	tmp = malloc(sizeof(t_env));
	i = 0;
	if (len != 1)
	{
		while (++i < len)
		{
			tmp = key_value(cmd[i]);
			if (!foreign_letter(tmp->key))
				return ;
			else if (update_value(tmp->key, tmp->value, exprt) == 0)
				ft_lstadd_back_s(&exprt, ft_lstnew_s(tmp->key, tmp->value));
		}
	}
	else
		get_export(exprt, outf);
	free(tmp);
}
