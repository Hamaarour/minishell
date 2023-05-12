/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamaarou <hamaarou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:09:08 by hamaarou          #+#    #+#             */
/*   Updated: 2023/05/12 18:59:35 by hamaarou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int type_is_char(t_token *token)
{
	if (token)
	{
		if (token->type == t_CHAR)
			return (0);
	}
	return (1);
}

t_tokens_type	type_is_rederec(t_token *token)
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
			return (0);
	}
	return (1);
}

/* Check PIPE syntax */
int	pipe_syntax(t_parser *parser)
{
	t_parser *tmp;
	
	tmp = parser;
	while (tmp->current_token->type != t_EOF)
	{
		if (tmp->current_token->type == t_PIPE)
		{
			if (tmp->previous_token == NULL)
				return (1);
			else if (tmp->previous_token->type == t_PIPE)
				return (1);
		}
		tmp->previous_token = tmp->current_token;
		tmp->current_token = get_next_token(tmp->lexer);
		if (tmp->current_token->type == t_EOF && tmp->previous_token->type == t_PIPE)
			return (1);	
	}
	return (0);
}

/* Check redirection syntax */
int	redirect_syntax(t_parser *parser)
{
	t_parser *tmp;
	
	tmp = parser;
	while (tmp->current_token->type != t_EOF)
	{
		if (type_is_rederec(tmp->current_token) != 10)
		{
			if (tmp->previous_token->type == type_is_rederec(tmp->current_token))
				return (1);
		}
		tmp->previous_token = tmp->current_token;
		tmp->current_token = get_next_token(tmp->lexer);
	}
	return (0);
}

int iterate_over_tokens_check_syntaxe(t_parser *parser)
{
	if ((pipe_syntax(parser) == 1) || (redirect_syntax(parser) == 1))
		return (err_msg("Bash : syntax error"));
	
	// printf("current_token : %u\n", parser->current_token->type);
	// printf("previous_token : %u\n", parser->previous_token->type);
	return (0);
}