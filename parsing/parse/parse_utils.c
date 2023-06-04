/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:48:11 by hamaarou          #+#    #+#             */
/*   Updated: 2023/06/04 19:41:30 by hamaarou         ###   ########.fr       */
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

int	is_redirection_token(t_parser *parser)
{
	return (parser->previous_token != NULL
		&& is_redirection(parser->previous_token->type) == 1
		&& parser->current_token->type == t_CHAR);
}

int	handle_redirection(t_parser *parser, int *fd_in, int *fd_out, int *flag)
{
	if (parser->previous_token->type == t_GREAT_THAN)
		out_file(parser->current_token->val, fd_out);
	else if (parser->previous_token->type == t_LESS_THAN)
		in_file(parser->current_token->val, fd_in);
	else if (parser->previous_token->type == t_APPEND)
		append_file(parser->current_token->val, fd_out);
	else if (parser->previous_token->type == t_HEREDOC)
	{
		if (heredoc_file(parser->current_token->val, fd_in) == 1)
			return (1);
	}
	*flag = 1;
	return (0);
}

void	update_current_token(t_parser *parser)
{
	if (parser->previous_token->type == t_HEREDOC)
		parser->current_token = get_next_token(parser->lexer, 1);
	else
		parser->current_token = get_next_token(parser->lexer, 0);
}
