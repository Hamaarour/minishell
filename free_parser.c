/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 08:39:20 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/02 22:47:08 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parser_cmd(t_parser **parser, t_data_cmd **data_cmd)
{
	t_data_cmd *current;
	
	current = *data_cmd;
	while (current != NULL)
	{
		t_data_cmd *next = current->next;
		while (current->args != NULL)
		{
			t_args *args_next = current->args->next;
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
	*parser = NULL;
}
