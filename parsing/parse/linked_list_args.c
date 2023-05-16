/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:42:43 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/16 14:11:30 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

//creat new node of t_args type and return it
t_args *ft_new_arg(char *arg)
{
	t_args	*new_arg_node;

	new_arg_node = (t_args *)malloc(sizeof(*new_arg_node));
	if (new_arg_node == NULL)
		return (NULL);
	new_arg_node->args = ft_strdup(arg);
	new_arg_node->next = NULL;
	return (new_arg_node);
}

// add back the new node to the linked list
void	ft_add_back_arg(t_args **head, t_args *new)
{
	t_args	*tmp;
	
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