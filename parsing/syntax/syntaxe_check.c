/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/21 17:24:17 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	reinitialize_parser(t_parser *parser)
{
	free(parser->current_token);
	free(parser->previous_token);
	parser->lexer->i = 0;
	parser->lexer->c = parser->lexer->src[parser->lexer->i];
	parser->previous_token = parser->current_token;
	parser->current_token = get_next_token(parser->lexer);
}

/* Check PIPE syntax */
int	pipe_syntax(t_parser *parser)
{
	while (parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type == t_PIPE)
		{
			g_gob.nb_cmd++;
			if (parser->previous_token == NULL)
				return (reinitialize_parser(parser), 1);
			else if (parser->previous_token->type == t_PIPE
					|| type_is_rederec(parser->previous_token) == 0)
				return (reinitialize_parser(parser), 1);
		}
		parser->previous_token = parser->current_token;
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token->type == t_EOF
			&& parser->previous_token->type == t_PIPE)
			return (reinitialize_parser(parser), 1);
	}
	return (reinitialize_parser(parser), 0);
}

/* Check redirection syntax */
int	redirect_syntax(t_parser *parser)
{
	while (parser->current_token->type != t_EOF)
	{
		if (parser->current_token->type == t_GREAT_THAN
			|| parser->current_token->type == t_LESS_THAN)
		{
			if (parser->previous_token
				&& (parser->previous_token->type == t_GREAT_THAN
					|| parser->previous_token->type == t_LESS_THAN))
				return (reinitialize_parser(parser), 1);
		}
		else if (parser->current_token->type == t_HEREDOC
				|| parser->current_token->type == t_APPEND)
		{
			if (!parser->previous_token
				|| parser->previous_token->type == t_GREAT_THAN
				|| parser->previous_token->type == t_LESS_THAN)
				return (reinitialize_parser(parser), 1);
		}
		parser->previous_token = parser->current_token;
		parser->current_token = get_next_token(parser->lexer);
		if (parser->current_token->type == t_EOF
			&& type_is_rederec(parser->previous_token) == 0)
			return (reinitialize_parser(parser), 1);
	}
	return (reinitialize_parser(parser), 0);
}

int	iterate_over_tokens_check_syntaxe(t_parser *parser)
{
	if ((pipe_syntax(parser) == 1) || (redirect_syntax(parser) == 1))
		return (err_msg("Bash : syntax error"));
	return (0);
}