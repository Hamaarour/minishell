/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/19 17:38:16 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
/*
if (tmp->next->args->args[0] == '<' || tmp->next->args->args[0] == '>')
{
	if (tmp->next->args->args[0] == '<')
		tmp->next->fd_in = open(tmp->next->args->next->args, O_RDONLY);
	else
		tmp->next->fd_out = open(tmp->next->args->next->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	tmp->next->args = tmp->next->args->next->next;
}
*/
void	out_file(char *file_name, t_data_cmd *tmp)
{
	
}


void 	in_file(t_data_cmd **cmd_data)
{

}

void	openning_redirection(t_data_cmd **cmd_data)
{
	t_data_cmd	*tmp;

	tmp = *cmd_data;
	while (tmp->next != NULL)
	{
		if (tmp->args->args[0] == '>')
		{
			tmp->fd_out = open(tmp->args->next->args, O_WRONLY | O_CREAT | O_TRUNC);
			tmp->args = tmp->args->next;
		}
		if (tmp->args->args[0] == '<')
		{
			tmp->fd_in = open(tmp->args->next->args, O_RDONLY);
			tmp->args = tmp->args->next;
		}
		tmp = tmp->next;
	}
}

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
}

void	start_parsing(t_parser *parser, char *cmd, t_data_cmd **cmd_data)
{
	g_gob.ex_status = iterate_over_tokens_check_syntaxe(parser, cmd);
	
	if (g_gob.ex_status != 258)
	{
		parser = initialize_parser(cmd);
		divid_cmd(parser, cmd_data);
		openning_redirection(cmd_data);
	}
	// if suyntaxe error return NULL and free all the memory 
	return ;
}


