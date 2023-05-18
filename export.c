/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjaddad <zjaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:46:40 by zjaddad           #+#    #+#             */
/*   Updated: 2023/05/18 02:04:07 by zjaddad          ###   ########.fr       */
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
			{
				free(tmp->value);
				tmp->value = NULL;
				return (1);
			}
			else
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
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
	else
		elt->value = NULL;
	elt->key = ft_strdup(key);
	elt->next = NULL;
	return (elt);
}

void ft_export(t_args *cmd, int outf)
{
    int		len;
    int		i;
    t_env	*tmp;
    t_args	*nxt_cmd;

    len = ft_lstsizes(cmd);
    i = 0;
	nxt_cmd = cmd->next;
    if (len != 1)
    {
        while (++i < len)
        {
            tmp = key_value(nxt_cmd->args);
            if (!foreign_letter(tmp->key))
                return ;
            else if (update_value(tmp->key, tmp->value, glob.env_p) == 0)
                ft_lstadd_back_s(&glob.env_p, ft_lstnew_s(tmp->key, tmp->value));
			nxt_cmd = nxt_cmd->next;
			ft_free(tmp);
        }
    }
    else
        get_export(glob.env_p, outf);
}
