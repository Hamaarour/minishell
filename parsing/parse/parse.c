/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/18 16:50:00 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

//this function print the linked list of the tokens
void print_cmd_data(t_data_cmd **cmd_data) 
{
	while ((*cmd_data) != NULL)
	{
		t_args *arg = (*cmd_data)->args;
		while (arg != NULL)
		{
			printf("%s\n", arg->args);
			arg = arg->next;
		}
		printf("|*-*-*-*-* new_node *-*-*-*-*|\n");
		(*cmd_data) = (*cmd_data)->next;
	}
}

// this function create a new node of the linked list of the tokens and return the head
t_args	*create_node(t_parser *parser)
{
	t_parser	*tmp;
	t_args		*arg;

	arg = NULL;
	tmp = parser;
	while (tmp->current_token->type != t_PIPE && tmp->current_token->type != t_EOF)
	{
		ft_add_back_arg(&arg, ft_new_arg(tmp->current_token->val));
		tmp->current_token = get_next_token(tmp->lexer);
	}
	return (arg);
}

//divide the cmd into tokens and add them to the linked list
void	divid_cmd(t_parser *parser, t_data_cmd **cmd_data)
{
	t_args	*arg;

	arg = NULL;
	while (parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type != t_PIPE)
		{
			arg = create_node(parser);
			ft_add_back_cmd(cmd_data, ft_new_cmd(arg));
			arg = NULL;
		}
		parser->current_token = get_next_token(parser->lexer);
	}
	//print_cmd_data(cmd_data);
}

void	start_parsing(t_parser *parser, char *cmd, t_data_cmd **cmd_data)
{
	g_gob.ex_status = iterate_over_tokens_check_syntaxe(parser, cmd);
	(void)cmd_data;					
	if (g_gob.ex_status != 258)
	{
		parser = initialize_parser(cmd);

		//free_pars(parser);

		//divid_cmd(parser, cmd_data);
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

