/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:07:18 by hamaarou          #+#    #+#             */
/*   Updated: 2023/01/22 14:53:02 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
