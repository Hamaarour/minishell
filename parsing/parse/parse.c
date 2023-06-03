/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/03 20:40:10 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

int	is_redirection(t_tokens_type type)
{
	if (type == t_GREAT_THAN || type == t_LESS_THAN || type == t_APPEND
		|| type == t_HEREDOC)
		return (1);
	return (0);
}

void	in_out(int *in, int *out)
{
	*in = 0;
	*out = 1;
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
				out_file(parser->current_token->val, fd_out);
			else if (parser->previous_token->type == t_LESS_THAN)
				in_file(parser->current_token->val, fd_in);
			else if (parser->previous_token->type == t_APPEND)
				append_file(parser->current_token->val, fd_out);
			else if (parser->previous_token->type == t_HEREDOC)
				heredoc_file(parser->current_token->val, fd_in);
			flag = 1;
		}
		if (flag != 1 && !is_redirection(parser->current_token->type))
			ft_add_back_arg(&arg, ft_new_arg(parser->current_token->val));
		flag = 0;
		free_prev(parser);
		parser->previous_token = parser->current_token;
		if (parser->previous_token->type == t_HEREDOC)
			parser->current_token = get_next_token(parser->lexer, 1);
		else
			parser->current_token = get_next_token(parser->lexer, 0);
		if (parser->current_token == NULL)
			return (free(parser->current_token), NULL);
	}
	return (arg);
}

int	divid_cmd(t_parser *parser, t_data_cmd **cmd_data)
{
	t_args	*arg;
	int		in;
	int		out;

	arg = NULL;
	in_out(&in, &out);
	while (parser->current_token != NULL
		&& parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type != t_PIPE)
		{
			arg = create_node(parser, &in, &out);
			if (arg != NULL)
				ft_add_back_cmd(cmd_data, ft_new_cmd(arg, in, out));
		}
		in_out(&in, &out);
		if (parser->current_token != NULL)
			free(parser->current_token->val);
		free(parser->current_token);
		parser->current_token = get_next_token(parser->lexer, 0);
		if (parser->current_token == NULL)
			return (reinitialize_parser(parser), 1);
	}
	return (0);
}

int	start_parsing(t_parser *parser, t_data_cmd **cmd_data)
{
	iterate_over_tokens_check_syntaxe(parser);
	if (g_glob.ex_status != 258)
	{
		if (divid_cmd(parser, cmd_data) == 1)
		{
			cleanup_parser(parser);
			return (1);
		}
		return (0);
	}
	return (1);
}
