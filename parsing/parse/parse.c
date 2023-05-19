/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/19 19:23:49 by hamaarou         ###   ########.fr       */
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
void error_opennig_file(int fd)
{
	if (fd == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		g_gob.ex_status = 1;
	}
}
/*
void	openning_redirection(t_data_cmd **cmd_data)
{
	t_data_cmd	*tmp;

	tmp = *cmd_data;
	while (tmp->next != NULL)
	{
		if (tmp->args->args[0] == '>')
		{
			tmp->fd_out = open(tmp->args->next->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			error_opennig_file(tmp->fd_out);
			tmp->args = tmp->args->next;
		}
		if (tmp->args->args[0] == '<')
		{
			tmp->fd_in = open(tmp->args->next->args, O_RDONLY, 0644);
			error_opennig_file(tmp->fd_in);
			tmp->args = tmp->args->next;
		}
		if (tmp->args->args[0] == '>' && tmp->args->next->args[1] == '>')
		{
			tmp->fd_in = open(tmp->args->next->next->args, O_RDONLY, 0644);
			error_opennig_file(tmp->fd_in);
			tmp->args = tmp->args->next->next;
		}
		tmp = tmp->next;
	}
}
*/
t_args	*create_node(t_parser *parser, int *fd_in, int *fd_out)
{
	t_parser	*tmp;
	t_args		*arg;

	arg = NULL;
	tmp = parser;
	(void)fd_in;
	(void)fd_out;
	while (tmp->current_token->type != t_PIPE && tmp->current_token->type != t_EOF)
	{
		if (tmp->current_token->type == t_GREAT_THAN)
		{
			
		}
		if (tmp->current_token->type == t_LESS_THAN)
		{
			
		}
		ft_add_back_arg(&arg, ft_new_arg(tmp->current_token->val));
		tmp->current_token = get_next_token(tmp->lexer);
	}
	return (arg);
}

void	divid_cmd(t_parser *parser, t_data_cmd **cmd_data)
{
	t_args	*arg;
	int		in;
	int		out;
	
	arg = NULL;
	in = 0;
	out = 1;
	while (parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type != t_PIPE)
		{
			arg = create_node(parser, &in, &out);
			ft_add_back_cmd(cmd_data, ft_new_cmd(arg, in, out));
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
		//openning_redirection(cmd_data);
	}
	// if suyntaxe error return NULL and free all the memory 
	return ;
}


