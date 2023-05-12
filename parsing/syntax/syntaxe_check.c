/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/12 12:38:24 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	type_is_rederec(t_token *token)
{
	if (token)
	{
		if (token->type == t_GREAT_THAN || token->type == t_LESS_THAN 
			|| token->type == t_HEREDOC|| token->type == t_APPEND)
			return (0);
	}
	return (1);
}

int	type_is_pipe(t_token *token)
{
	if (token)
	{
		if (token->type == t_PIPE)
			return (1);
	}
	return (0);
}
int type_is_char(t_token *token)
{
	if (token)
	{
		if (token->type == t_CHAR)
			return (1);
	}
	return (0);
}

int syntaxe_check(t_parser *parser)
{
	if(parser->current_token != NULL)
	{
		if(parser->current_token->type == t_PIPE || parser->current_token->type == t_EOF)
		{
			if (type_is_char(parser->previous_token) == 0 || type_is_rederec(parser->previous_token) == 0)
				return (err_msg("Bash : syntax error"));
		}
		else if (type_is_rederec(parser->current_token) == 0)
		{
			if (type_is_char(parser->previous_token) == 0)
				return (err_msg("Bash : syntax error"));
		}
	}
	return (0);
}

int iterate_over_tokens_check_syntaxe(t_parser *parser)
{
	while (parser->current_token->type != t_EOF)
	{
		if (syntaxe_check(parser) == 258)
			return (258);
		parser->previous_token = parser->current_token;
		parser->current_token = get_next_token(parser->lexer);
	}
	return (0);
}