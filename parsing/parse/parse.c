/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/20 16:27:17 by hamaarou         ###   ########.fr       */
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

int	is_redirection(t_tokens_type type)
{
	
	if (type == t_GREAT_THAN || type == t_LESS_THAN || type == t_APPEND)
		return (1);
	return (0);
}

t_args	*create_node(t_parser *parser, int *fd_in, int *fd_out)
{
	t_parser	*tmp;
	t_args		*arg;
	int 		flag;
	
	flag = 0;
	arg = NULL;
	tmp = parser;
	while (tmp->current_token->type != t_PIPE && tmp->current_token->type != t_EOF)
	{
		if (tmp->previous_token != NULL && is_redirection(tmp->previous_token->type) == 1 && tmp->current_token->type == t_CHAR)
		{
			if (tmp->previous_token->type == t_GREAT_THAN)
			{
				*fd_out = open(tmp->current_token->val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				error_opennig_file(*fd_out);
			}
			if (tmp->previous_token->type == t_LESS_THAN)
			{
				*fd_in = open(tmp->current_token->val, O_RDONLY, 0644);
				error_opennig_file(*fd_in);
			}
			if (tmp->previous_token->type == t_APPEND)
			{
				*fd_out = open(tmp->current_token->val, O_WRONLY | O_CREAT | O_APPEND, 0644);
				error_opennig_file(*fd_out);
			}
			flag = 1;
		}
		if (flag != 1 && !is_redirection(tmp->current_token->type))
			ft_add_back_arg(&arg, ft_new_arg(tmp->current_token->val));
		flag = 0;
		tmp->previous_token = tmp->current_token;
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
	}
}


