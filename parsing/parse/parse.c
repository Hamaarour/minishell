/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 17:24:52 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	error_opennig_file(int fd)
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
	t_args	*arg;
	int		flag;

	flag = 0;
	arg = NULL;
	while (parser->current_token->type != t_PIPE
		&& parser->current_token->type != t_EOF)
	{
		if (parser->previous_token != NULL
			&& is_redirection(parser->previous_token->type) == 1
			&& parser->current_token->type == t_CHAR)
		{
			if (parser->previous_token->type == t_GREAT_THAN)
			{
				*fd_out = open(parser->current_token->val,
								O_WRONLY | O_CREAT | O_TRUNC,
								0644);
				error_opennig_file(*fd_out);
			}
			if (parser->previous_token->type == t_LESS_THAN)
			{
				*fd_in = open(parser->current_token->val, O_RDONLY, 0644);
				error_opennig_file(*fd_in);
			}
			if (parser->previous_token->type == t_APPEND)
			{
				*fd_out = open(parser->current_token->val,
								O_WRONLY | O_CREAT | O_APPEND,
								0644);
				error_opennig_file(*fd_out);
			}
			flag = 1;
		}
		if (flag != 1 && !is_redirection(parser->current_token->type))
			ft_add_back_arg(&arg, ft_new_arg(parser->current_token->val));
		flag = 0;
		parser->previous_token = parser->current_token;
		parser->current_token = get_next_token(parser->lexer);
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

void	start_parsing(t_parser *parser, t_data_cmd **cmd_data)
{
	g_gob.ex_status = iterate_over_tokens_check_syntaxe(parser);
	if (g_gob.ex_status != 258)
	{
		divid_cmd(parser, cmd_data);
	}
}
