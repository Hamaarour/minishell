/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/16 23:13:28 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

//divide the cmd into tokens and add them to the linked list
void	divid_cmd(t_parser *parser, t_data_cmd **cmd_data)
{
	t_args *args = NULL;
	while (parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type != t_PIPE)
		{
			(*cmd_data)->args = ft_new_arg(parser->current_token->value);
		}
		else if (parser->current_token->type == t_PIPE)
		{
			ft_add_back_cmd(cmd_data, ft_new_cmd());
		}
		
		parser->current_token = get_next_token(parser->lexer);
	}
}  

void	start_parsing(t_parser *parser, char *cmd, t_data_cmd **cmd_data)
{
	g_gob.ex_status = iterate_over_tokens_check_syntaxe(parser, cmd);
											
	if (g_gob.ex_status != 258)
	{
		parser = initialize_parser(cmd);
		divid_cmd(parser, cmd_data);
	}
	// if suyntaxe error return NULL and free all the memory 
	return ;
}

/*
void iterate_cmd_data_args(t_data_cmd **cmd_data) {
    t_data_cmd *current_cmd = *cmd_data;
    while (current_cmd != NULL) {
        t_args *current_args = current_cmd->args;
        while (current_args != NULL) {
            printf("%s\n", current_args->arg);
            current_args = current_args->next;
        }
        current_cmd = current_cmd->next;
    }
}
*/

