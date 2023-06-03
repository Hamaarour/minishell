/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:39:20 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/03 21:10:20 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parser_cmd(t_parser **parser, t_data_cmd **data_cmd)
{
	t_data_cmd	*current;
	t_data_cmd	*next;
	t_args		*args_next;

	current = *data_cmd;
	while (current != NULL)
	{
		next = current->next;
		while (current->args != NULL)
		{
			args_next = current->args->next;
			free(current->args->args);
			free(current->args);
			current->args = args_next;
		}
		free(current);
		current = next;
	}
	*data_cmd = NULL;
	free((*parser)->current_token->val);
	free((*parser)->current_token);
	free((*parser)->previous_token->val);
	free((*parser)->previous_token);
	free((*parser)->lexer);
	free(*parser);
}
