/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:45 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/27 21:52:56 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../LIBFT/libft.h"
#include "../../minishell.h"

void	error_opening_file(int fd)
{
	if (fd == -1)
	{
		ft_putendl_fd("Bash Error: No such file or directory", 2);
		glob.ex_status = 1;
	}
}

int	is_redirection(t_tokens_type type)
{
	if (type == t_GREAT_THAN || type == t_LESS_THAN || type == t_APPEND
		|| type == t_HEREDOC)
		return (1);
	return (0);
}

void	cleanup_parser(t_parser *parser)
{
	if (parser->lexer != NULL)
	{
		free(parser->lexer->src);
		free(parser->lexer);
		parser->lexer = NULL;
	}
	if (parser->current_token != NULL)
	{
		free(parser->current_token->val);
		free(parser->current_token);
		parser->current_token = NULL;
	}
	if (parser->previous_token != NULL)
	{
		free(parser->previous_token->val);
		free(parser->previous_token);
		parser->previous_token = NULL;
	}
	free(parser);
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
				if (out_file(parser->current_token->val, fd_out) == 1)
				{
					free(arg->args);
					free(arg);
					return (NULL);
				}
			}
			else if (parser->previous_token->type == t_LESS_THAN)
			{
				if (in_file(parser->current_token->val, fd_in) == 1)
				{
					free(arg->args);
					free(arg);
					return (NULL);
				}
			}
			else if (parser->previous_token->type == t_APPEND)
			{
				if (append_file(parser->current_token->val, fd_out) == 1)
				{
					free(arg->args);
					free(arg);
					return (NULL);
				}
			}
			flag = 1;
		}
		if (flag != 1 && !is_redirection(parser->current_token->type))
			ft_add_back_arg(&arg, ft_new_arg(parser->current_token->val));
		flag = 0;
		if (parser->previous_token)
		{
			free(parser->previous_token->val);
			free(parser->previous_token);
			parser->previous_token = NULL;
		}
		parser->previous_token = parser->current_token;
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token == NULL)
		{
			free(parser->current_token);
			return (NULL);
		}
	}
	return (arg);
}

int	divid_cmd(t_parser *parser, t_data_cmd **cmd_data)
{
	t_args	*arg;
	int		in;
	int		out;

	arg = NULL;
	in = 0;
	out = 1;
	while (parser->current_token != NULL
		&& parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type != t_PIPE)
		{
			arg = create_node(parser, &in, &out);
			if (arg != NULL)
				ft_add_back_cmd(cmd_data, ft_new_cmd(arg, in, out));
			else
			{
				return (1);
			}
		}
		if (parser->current_token != NULL)
			free(parser->current_token->val);
		free(parser->current_token);
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token == NULL)
			return (reinitialize_parser(parser), 1);
	}
	return (0);
}

int	start_parsing(t_parser *parser, t_data_cmd **cmd_data)
{
	int	st;

	st = iterate_over_tokens_check_syntaxe(parser);
	glob.ex_status = st;
	while (parser->lexer->ambg_redir > 0)
	{
		glob.ex_status = 1;
		ft_putendl_fd("Error: Ambiguous redirect", 2);
		parser->lexer->ambg_redir--;
	}
	if (glob.ex_status != 258)
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
