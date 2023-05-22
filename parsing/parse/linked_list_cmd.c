/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:42:46 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/19 19:11:35 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

//creat new node of t_data_cmd type and return it
t_data_cmd	*ft_new_cmd(t_args *arg, int fd_in, int fd_out)
{
	t_data_cmd	*new_cmd_node;

	new_cmd_node = (t_data_cmd *)malloc(sizeof(*new_cmd_node));
	if (new_cmd_node == NULL)
		return (NULL);
	new_cmd_node->args = arg;
	new_cmd_node->fd_in = fd_in;
	new_cmd_node->fd_out = fd_out;
	new_cmd_node->next = NULL;
	return (new_cmd_node);
}

// add back the new node to the linked list
void	ft_add_back_cmd(t_data_cmd **head, t_data_cmd *new)
{
	t_data_cmd	*tmp;
	
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